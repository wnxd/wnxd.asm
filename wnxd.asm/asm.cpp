#include <Windows.h>
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
				VirtualProtectEx((void*)Process::GetCurrentProcess()->Handle, address, size, PAGE_EXECUTE_READWRITE, 0);
			}
		public:
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
			static IntPtr GetPtr(Delegate^ method, bool forcibly = false)
			{
				return GetPtr(method->Method, forcibly);
			}
			static IntPtr GetPtr(MethodBase^ method, bool forcibly = false)
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