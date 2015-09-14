#include "asm.h";

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Diagnostics;
using namespace System::Reflection;
using namespace System::Runtime::InteropServices;

namespace wnxd
{
	namespace Asm
	{
		public ref class Hook
		{
		private:
			ref struct Info
			{
				bool Jmp;
				int Source;
				int DestinationToken;
				array<Byte>^ SourceData;
				bool Forcibly;
				int MethodHandle;
				bool IL;
				bool External;
			};
			static Dictionary<int, Info^>^ _hooklist = gcnew Dictionary<int, Info^>();
			int _sourcetoken;
			MethodBase^ _destination;
			bool _ishook = true;
			Info^ _info;
			static Hook^ _GetSource(int methodtoken, MethodBase^ method)
			{
				return _hooklist->ContainsKey(methodtoken) && _hooklist[methodtoken]->DestinationToken == method->MetadataToken ? gcnew Hook(methodtoken, method) : nullptr;
			}
		internal:
			Hook(int sourcetoken, MethodBase^ destination)
			{
				this->_sourcetoken = sourcetoken;
				this->_info = _hooklist[sourcetoken];
				this->_destination = destination;
			}
		public:
			/// <summary>
			/// hook一个方法,使其被调用时会转跳到目标方法
			/// </summary>
			/// <param name="source">被hook的方法</param>
			/// <param name="destination">转跳的目标方法</param>
			static void Register(Delegate^ source, Delegate^ destination)
			{
				Register(source, destination, false);
			}
			/// <summary>
			/// hook一个方法,使其被调用时会转跳到目标方法
			/// </summary>
			/// <param name="source">被hook的方法</param>
			/// <param name="destination">转跳的目标方法</param>
			/// <param name="forcibly">是否强制hook,当普通hook失效时</param>
			static void Register(Delegate^ source, Delegate^ destination, bool forcibly)
			{
				Register(source->Method, destination->Method, forcibly);
			}
			/// <summary>
			/// hook一个方法,使其被调用时会转跳到目标方法
			/// </summary>
			/// <param name="source">被hook的方法地址</param>
			/// <param name="sourcetoken">被hook的方法标识</param>
			/// <param name="destination">转跳的目标方法</param>
			/// <param name="forcibly">是否强制hook,当普通hook失效时</param>
			/// <param name="methodhandle">被hook的方法句柄</param>
			/// <param name="il"></param>
			/// <param name="external"></param>
			static void Register(IntPtr source, int sourcetoken, Delegate^ destination, bool forcibly, int methodhandle, bool il, bool external)
			{
				Register((int)source, sourcetoken, destination->Method, forcibly, methodhandle, il, external);
			}
			/// <summary>
			/// hook一个方法,使其被调用时会转跳到目标方法
			/// </summary>
			/// <param name="source">被hook的方法地址</param>
			/// <param name="sourcetoken">被hook的方法标识</param>
			/// <param name="destination">转跳的目标方法</param>
			/// <param name="forcibly">是否强制hook,当普通hook失效时</param>
			/// <param name="methodhandle">被hook的方法句柄</param>
			/// <param name="il"></param>
			/// <param name="external"></param>
			static void Register(void* source, int sourcetoken, Delegate^ destination, bool forcibly, int methodhandle, bool il, bool external)
			{
				Register((int)source, sourcetoken, destination->Method, forcibly, methodhandle, il, external);
			}
			/// <summary>
			/// hook一个方法,使其被调用时会转跳到目标方法
			/// </summary>
			/// <param name="source">被hook的方法地址</param>
			/// <param name="sourcetoken">被hook的方法标识</param>
			/// <param name="destination">转跳的目标方法</param>
			/// <param name="forcibly">是否强制hook,当普通hook失效时</param>
			/// <param name="methodhandle">被hook的方法句柄</param>
			/// <param name="il"></param>
			/// <param name="external"></param>
			static void Register(int source, int sourcetoken, Delegate^ destination, bool forcibly, int methodhandle, bool il, bool external)
			{
				Register(source, sourcetoken, destination->Method, forcibly, methodhandle, il, external);
			}
			/// <summary>
			/// hook一个方法,使其被调用时会转跳到目标方法
			/// </summary>
			/// <param name="source">被hook的方法</param>
			/// <param name="destination">转跳的目标方法</param>
			static void Register(MethodBase^ source, MethodBase^ destination)
			{
				Register(source, destination, false);
			}
			/// <summary>
			/// hook一个方法,使其被调用时会转跳到目标方法
			/// </summary>
			/// <param name="source">被hook的方法</param>
			/// <param name="destination">转跳的目标方法</param>
			/// <param name="forcibly">是否强制hook,当普通hook失效时</param>
			static void Register(MethodBase^ source, MethodBase^ destination, bool forcibly)
			{
				Register(Asm::GetPtr(source, forcibly), source->MetadataToken, destination, forcibly, (int)source->MethodHandle.Value, source->GetMethodBody() != nullptr, Asm::IsExternal(source));
			}
			/// <summary>
			/// hook一个方法,使其被调用时会转跳到目标方法
			/// </summary>
			/// <param name="source">被hook的方法地址</param>
			/// <param name="sourcetoken">被hook的方法标识</param>
			/// <param name="destination">转跳的目标方法</param>
			/// <param name="forcibly">是否强制hook,当普通hook失效时</param>
			/// <param name="methodhandle">被hook的方法句柄</param>
			/// <param name="il"></param>
			/// <param name="external"></param>
			static void Register(IntPtr source, int sourcetoken, MethodBase^ destination, bool forcibly, int methodhandle, bool il, bool external)
			{
				Register((int)source, sourcetoken, destination, forcibly, methodhandle, il, external);
			}
			/// <summary>
			/// hook一个方法,使其被调用时会转跳到目标方法
			/// </summary>
			/// <param name="source">被hook的方法地址</param>
			/// <param name="sourcetoken">被hook的方法标识</param>
			/// <param name="destination">转跳的目标方法</param>
			/// <param name="forcibly">是否强制hook,当普通hook失效时</param>
			/// <param name="methodhandle">被hook的方法句柄</param>
			/// <param name="il"></param>
			/// <param name="external"></param>
			static void Register(void* source, int sourcetoken, MethodBase^ destination, bool forcibly, int methodhandle, bool il, bool external)
			{
				Register((int)source, sourcetoken, destination, forcibly, methodhandle, il, external);
			}
			/// <summary>
			/// hook一个方法,使其被调用时会转跳到目标方法
			/// </summary>
			/// <param name="source">被hook的方法地址</param>
			/// <param name="sourcetoken">被hook的方法标识</param>
			/// <param name="destination">转跳的目标方法</param>
			/// <param name="forcibly">是否强制hook,当普通hook失效时</param>
			/// <param name="methodhandle">被hook的方法句柄</param>
			/// <param name="il"></param>
			/// <param name="external"></param>
			static void Register(int source, int sourcetoken, MethodBase^ destination, bool forcibly, int methodhandle, bool il, bool external)
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
			/// <summary>
			/// 取消此方法的hook
			/// </summary>
			/// <param name="source">被hook的方法</param>
			static void Unregister(Delegate^ source)
			{
				Unregister(source->Method->MetadataToken);
			}
			/// <summary>
			/// 取消此方法的hook
			/// </summary>
			/// <param name="source">被hook的方法</param>
			static void Unregister(MethodBase^ source)
			{
				Unregister(source->MetadataToken);
			}
			/// <summary>
			/// 取消此方法的hook
			/// </summary>
			/// <param name="sourcetoken">被hook的方法标识</param>
			static void Unregister(int sourcetoken)
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
			/// <summary>
			/// 从该对象中寻找指定方法
			/// </summary>
			/// <param name="target">包含此方法的对象</param>
			/// <param name="methodname">方法名</param>
			/// <returns></returns>
			static MethodBase^ GetMethod(Object^ target, String^ methodname)
			{
				return GetMethod(target->GetType(), methodname);
			}
			/// <summary>
			/// 从该类型中寻找指定方法
			/// </summary>
			/// <param name="type">包含此方法的类型</param>
			/// <param name="methodname">方法名</param>
			/// <returns></returns>
			static MethodBase^ GetMethod(Type^ type, String^ methodname)
			{
				return type->GetMethod(methodname, BindingFlags::Instance | BindingFlags::Static | BindingFlags::Public | BindingFlags::NonPublic);
			}
			/// <summary>
			/// 强制转换对象类型
			/// </summary>
			/// <typeparam name="T">目标类型</typeparam>
			/// <param name="target">需要转换类型的对象</param>
			/// <returns>转换类型后的对象</returns>
			generic <typename T> static T Change(Object^ target)
			{
				return (T)target;
			}
			/// <summary>
			/// 切换hook对象的开关
			/// </summary>
			void Switch()
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
			/// <summary>
			/// 改变hook对象的开关状态
			/// </summary>
			/// <param name="ishook">是否开启hook</param>
			void Switch(bool ishook)
			{
				this->_ishook = !ishook;
				this->Switch();
			}
			/// <summary>
			/// 调用被hook对象的原方法
			/// </summary>
			/// <typeparam name="TResult">返回类型</typeparam>
			/// <param name="args">参数列表</param>
			/// <returns>返回值</returns>
			generic <typename TResult> TResult Run(array<Object^>^ args)
			{
				this->Switch();
				TResult ret = this->_info->IL ? Asm::PtrRun<TResult>(this->_info->Source, args) : Asm::PtrRun_Impl<TResult>(this->_info->Source, args);
				this->Switch();
				return ret;
			}
			/// <summary>
			/// 调用被hook对象的原方法
			/// </summary>
			/// <param name="args">参数列表</param>
			void Run(array<Object^>^ args)
			{
				this->Switch();
				if (this->_info->IL) Asm::PtrRun(this->_info->Source, args);
				else Asm::PtrRun_Impl(this->_info->Source, args);
				this->Switch();
			}
			/// <summary>
			/// 如果当前方法为转跳目标方法,则获取以此为目标的第一个hook对象,否则为null
			/// </summary>
			static property Hook^ Source
			{
				Hook^ get(){
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
			}
			/// <summary>
			/// 获取指定方法的hook对象,如果传入方法未被当前方法hook则返回null
			/// </summary>
			/// <param name="method">被hook的方法</param>
			/// <returns></returns>
			static Hook^ GetSource(Delegate^ method)
			{
				return _GetSource(method->Method->MetadataToken, (gcnew StackFrame(1))->GetMethod());
			}
			/// <summary>
			/// 获取指定方法的hook对象,如果传入方法未被当前方法hook则返回null
			/// </summary>
			/// <param name="method">被hook的方法</param>
			/// <returns></returns>
			static Hook^ GetSource(MethodBase^ method)
			{
				return _GetSource(method->MetadataToken, (gcnew StackFrame(1))->GetMethod());
			}
			/// <summary>
			/// 获取指定方法的hook对象,如果传入方法未被当前方法hook则返回null
			/// </summary>
			/// <param name="methodtoken">被hook的方法标识</param>
			/// <returns></returns>
			static Hook^ GetSource(int methodtoken)
			{
				return _GetSource(methodtoken, (gcnew StackFrame(1))->GetMethod());
			}
		};
	}
}