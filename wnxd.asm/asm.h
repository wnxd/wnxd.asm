#include "unmanaged.h";

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Diagnostics;
using namespace System::IO;
using namespace System::Reflection;
using namespace System::Runtime::InteropServices;
using namespace System::Text;
using namespace System::Text::RegularExpressions;

namespace wnxd
{
	namespace Asm
	{
		public ref class Asm
		{
		private:
			generic <typename TResult> static TResult _PtrRun(int ptr, array<Object^>^ args)
			{
				array<bool>^ _isValue = gcnew array<bool>(args->Length);
				for (int i = 0; i < args->Length; i++) _isValue[i] = args[i]->GetType()->IsValueType;
				return (TResult)IL_PtrRun(ptr, &args, &_isValue);
			}
		internal:
			static bool IsExternal(MethodBase^ method)
			{
				if (method->GetMethodBody() == nullptr) return true;
				String^ dir = AppDomain::CurrentDomain->RelativeSearchPath;
				if (String::IsNullOrEmpty(dir)) dir = AppDomain::CurrentDomain->BaseDirectory;
				else dir += "\\";
				return Path::GetDirectoryName(method->ReflectedType->Assembly->CodeBase)->Replace("file:\\", "") + "\\" != dir;
			}
			static void VirtualProtectExecute(IntPtr address, int size)
			{
				VirtualProtectExecute((void*)address, size);
			}
			static void VirtualProtectExecute(void* address, int size)
			{
				DWORD old = 0;
				VirtualProtectEx((void*)Process::GetCurrentProcess()->Handle, address, size, PAGE_EXECUTE_READWRITE, &old);
			}
		public:
			static void PtrRun(IntPtr ptr, array<Object^>^ args)
			{
				PtrRun<int>((int)ptr, args);
			}
			static void PtrRun(void* ptr, array<Object^>^ args)
			{
				PtrRun<int>((int)ptr, args);
			}
			static void PtrRun(int ptr, array<Object^>^ args)
			{
				PtrRun<int>(ptr, args);
			}
			generic <typename TResult> static TResult PtrRun(IntPtr ptr, array<Object^>^ args)
			{
				return PtrRun<TResult>((int)ptr, args);
			}
			generic <typename TResult> static TResult PtrRun(void* ptr, array<Object^>^ args)
			{
				return PtrRun<TResult>((int)ptr, args);
			}
			generic <typename TResult> static TResult PtrRun(int ptr, array<Object^>^ args)
			{
				return (TResult)_PtrRun<TResult>(ptr, args);
				//return _PtrRun<TResultT>(ptr, new byte[] { 85, 137, 229, 81, 82, 83, 139, 69, 12, 139, 72, 4, 133, 201, 116, 85, 131, 192, 12, 139, 85, 8, 131, 194, 8, 138, 26, 132, 219, 139, 24, 116, 3, 139, 91, 4, 137, 223, 131, 249, 1, 116, 56, 131, 192, 4, 131, 194, 1, 138, 26, 132, 219, 139, 24, 116, 3, 139, 91, 4, 137, 222, 131, 249, 2, 116, 30, 131, 233, 2, 107, 217, 4, 1, 216, 1, 202, 138, 26, 132, 219, 139, 24, 116, 3, 139, 91, 4, 83, 131, 232, 4, 131, 234, 1, 226, 236, 137, 242, 137, 249, 139, 69, 248, 255, 208, 91, 201, 194, 4, 0 }, args);
			}
			static array<Byte>^ PtrToBin(IntPtr ptr, int len)
			{
				if (ptr == IntPtr::Zero) return nullptr;
				array<Byte>^ b = gcnew array<Byte>(len);
				for (int i = 0; i < len; i++) b[i] = Marshal::ReadByte(ptr, i);
				return b;
			}
			static array<Byte>^ PtrToBin(int ptr, int len)
			{
				return PtrToBin((IntPtr)ptr, len);
			}
			static array<Byte>^ PtrToBin(void* ptr, int len)
			{
				return PtrToBin((IntPtr)ptr, len);
			}
			static IntPtr GetPtr(Delegate^ method)
			{
				return GetPtr(method, false);
			}
			static IntPtr GetPtr(Delegate^ method, bool forcibly)
			{
				return GetPtr(method->Method, forcibly);
			}
			static IntPtr GetPtr(MethodBase^ method)
			{
				return GetPtr(method, false);
			}
			static IntPtr GetPtr(MethodBase^ method, bool forcibly)
			{
				IntPtr ptr;
				if (IsExternal(method))
				{
					ptr = method->MethodHandle.GetFunctionPointer();
					if (forcibly && method->GetMethodBody() != nullptr)
					{
						Nullable<int>^ call = nullptr;
						for (int offset = 5; offset < 2000; offset++)
						{
							Byte b = Marshal::ReadByte(ptr, offset);
							if (b == 194)
							{
								b = Marshal::ReadByte(ptr, offset + 3);
								if (b == 204) break;
							}
							else if (b == 195)
							{
								b = Marshal::ReadByte(ptr, offset + 1);
								if (b == 204) break;
							}
							else if (b == 232) call = gcnew Nullable<int>(offset);
						}
						if (call != nullptr)
						{
							int p = Marshal::ReadInt32(ptr, call->Value + 1);
							p += (int)ptr + call->Value + 5;
							ptr = (IntPtr)p;
						}
					}
				}
				else ptr = Marshal::ReadIntPtr(method->MethodHandle.Value, 8);
				return ptr;
			}
		};
	}
}