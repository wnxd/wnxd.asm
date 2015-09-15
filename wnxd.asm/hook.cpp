#include "asm.h"
#include "hook.h"

using namespace wnxd::Asm;
//private
Hook^ Hook::_GetSource(int methodtoken, MethodBase^ method)
{
	return _hooklist->ContainsKey(methodtoken) && _hooklist[methodtoken]->DestinationToken == method->MetadataToken ? gcnew Hook(methodtoken, method) : nullptr;
}
//internal
Hook::Hook(int sourcetoken, MethodBase^ destination)
{
	this->_sourcetoken = sourcetoken;
	this->_info = _hooklist[sourcetoken];
	this->_destination = destination;
}
//public
void Hook::Register(Delegate^ source, Delegate^ destination)
{
	Register(source, destination, false);
}
void Hook::Register(Delegate^ source, Delegate^ destination, bool forcibly)
{
	Register(source->Method, destination->Method, forcibly);
}
void Hook::Register(IntPtr source, int sourcetoken, Delegate^ destination, bool forcibly, int methodhandle, bool il, bool external)
{
	Register((int)source, sourcetoken, destination->Method, forcibly, methodhandle, il, external);
}
void Hook::Register(void* source, int sourcetoken, Delegate^ destination, bool forcibly, int methodhandle, bool il, bool external)
{
	Register((int)source, sourcetoken, destination->Method, forcibly, methodhandle, il, external);
}
void Hook::Register(int source, int sourcetoken, Delegate^ destination, bool forcibly, int methodhandle, bool il, bool external)
{
	Register(source, sourcetoken, destination->Method, forcibly, methodhandle, il, external);
}
void Hook::Register(MethodBase^ source, MethodBase^ destination)
{
	Register(source, destination, false);
}
void Hook::Register(MethodBase^ source, MethodBase^ destination, bool forcibly)
{
	Register(Asm::GetPtr(source, forcibly), source->MetadataToken, destination, forcibly, (int)source->MethodHandle.Value, source->GetMethodBody() != nullptr, Asm::IsExternal(source));
}
void Hook::Register(IntPtr source, int sourcetoken, MethodBase^ destination, bool forcibly, int methodhandle, bool il, bool external)
{
	Register((int)source, sourcetoken, destination, forcibly, methodhandle, il, external);
}
void Hook::Register(void* source, int sourcetoken, MethodBase^ destination, bool forcibly, int methodhandle, bool il, bool external)
{
	Register((int)source, sourcetoken, destination, forcibly, methodhandle, il, external);
}
void Hook::Register(int source, int sourcetoken, MethodBase^ destination, bool forcibly, int methodhandle, bool il, bool external)
{
	Info^ info = gcnew Info();
	info->DestinationToken = destination->MetadataToken;
	info->Forcibly = forcibly;
	info->IL = il;
	info->External = external;
	if (_hooklist->ContainsKey(sourcetoken))
	{
		Info^ tmp = _hooklist[sourcetoken];
		if (tmp->Source == source && tmp->DestinationToken == destination->MetadataToken) return;
		Unregister(sourcetoken);
	}
	_hooklist->Add(sourcetoken, info);
	int ldesptr = (int)destination->MethodHandle.GetFunctionPointer();
	if (methodhandle != 0)
	{
		methodhandle += 8;
		if (!(external || forcibly))
		{
			int ns = Marshal::ReadInt32((IntPtr)methodhandle);
			if (ns != 0 && ns != source) source = ns;
			info->Jmp = false;
			info->MethodHandle = methodhandle;
			info->Source = source;
			Marshal::WriteInt32((IntPtr)methodhandle, ldesptr);
			return;
		}
	}
	IntPtr ptr = (IntPtr)source;
	info->Jmp = true;
	if (methodhandle != 0) info->MethodHandle = methodhandle;
	if (info->Source == 0) info->SourceData = Asm::PtrToBin(ptr, 5);
	info->Source = source;
	Asm::VirtualProtectExecute(ptr, 5);
	Marshal::WriteByte(ptr, 233);
	int offset = ldesptr - source - 5;
	Marshal::WriteInt32(ptr, 1, offset);
}
void Hook::Unregister(Delegate^ source)
{
	Unregister(source->Method->MetadataToken);
}
void Hook::Unregister(MethodBase^ source)
{
	Unregister(source->MetadataToken);
}
void Hook::Unregister(int sourcetoken)
{
	if (_hooklist->ContainsKey(sourcetoken))
	{
		Info^ info = _hooklist[sourcetoken];
		if (info->Jmp)
		{
			IntPtr ptr = (IntPtr)info->Source;
			array<Byte>^ b = info->SourceData;
			Marshal::WriteByte(ptr, b[0]);
			Marshal::WriteInt32(ptr, 1, BitConverter::ToInt32(b, 1));
		}
		else
		{
			IntPtr ptr = (IntPtr)info->MethodHandle;
			Marshal::WriteInt32(ptr, info->Source);
		}
		_hooklist->Remove(sourcetoken);
	}

}
MethodBase^ Hook::GetMethod(Object^ target, String^ methodname)
{
	return GetMethod(target->GetType(), methodname);
}
MethodBase^ Hook::GetMethod(Type^ type, String^ methodname)
{
	return type->GetMethod(methodname, BindingFlags::Instance | BindingFlags::Static | BindingFlags::Public | BindingFlags::NonPublic);
}
generic <typename T> T Hook::Change(Object^ target)
{
	return (T)target;
}
void Hook::Switch()
{
	if (this->_ishook) Unregister(this->_sourcetoken);
	else
	{
		int methodhandle = this->_info->MethodHandle;
		if (methodhandle != 0) methodhandle -= 8;
		Register(this->_info->Source, this->_sourcetoken, this->_destination, this->_info->Forcibly, methodhandle, this->_info->IL, this->_info->External);
	}
	this->_ishook = !this->_ishook;
}
void Hook::Switch(bool ishook)
{
	this->_ishook = !ishook;
	this->Switch();
}
generic <typename TResult> TResult Hook::Run(array<Object^>^ args)
{
	this->Switch();
	TResult ret = this->_info->IL ? Asm::PtrRun<TResult>(this->_info->Source, args) : Asm::PtrRun_Impl<TResult>(this->_info->Source, args);
	this->Switch();
	return ret;
}
void Hook::Run(array<Object^>^ args)
{
	this->Switch();
	if (this->_info->IL) Asm::PtrRun(this->_info->Source, args);
	else Asm::PtrRun_Impl(this->_info->Source, args);
	this->Switch();
}
Hook^ Hook::Source::get()
{
	MethodBase^ mb = (gcnew StackFrame(1))->GetMethod();
	for each (KeyValuePair<int, Info^> kv in _hooklist)
	{
		if (kv.Value->DestinationToken == mb->MetadataToken)
		{
			return gcnew Hook(kv.Key, mb);
			break;
		}
	}
	return nullptr;
}
Hook^ Hook::GetSource(Delegate^ method)
{
	return _GetSource(method->Method->MetadataToken, (gcnew StackFrame(1))->GetMethod());
}
Hook^ Hook::GetSource(MethodBase^ method)
{
	return _GetSource(method->MetadataToken, (gcnew StackFrame(1))->GetMethod());
}
Hook^ Hook::GetSource(int methodtoken)
{
	return _GetSource(methodtoken, (gcnew StackFrame(1))->GetMethod());
}