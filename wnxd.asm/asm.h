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
		private:
			generic <typename TResult> static TResult _PtrRun_Func(int p, array<Object^>^ a, array<bool>^ i)
			{
				return (TResult)gcnew Object();
			}
			generic <typename TResult> static TResult PtrToObj_Func(int p)
			{
				return (TResult)gcnew Object();
			}
			generic <typename TResult> static TResult _PtrRun(int ptr, array<Byte>^ code, array<Object^>^ args)
			{
				array<bool>^ _isValue = gcnew array<bool>(args->Length);
				for (int i = 0; i < args->Length; i++) _isValue[i] = args[i]->GetType()->IsValueType;
				IntPtr _ptr = Marshal::AllocHGlobal(code->Length);
				Marshal::Copy(code, 0, _ptr, code->Length);
				VirtualProtectExecute(_ptr, code->Length);
				Func<int, array<Object^>^, array<bool>^, TResult>^ _func = gcnew Func<int, array<Object^>^, array<bool>^, TResult>(_PtrRun_Func<TResult>);
				FieldInfo^ _methodPtr = _func->GetType()->GetField("_methodPtr", BindingFlags::NonPublic | BindingFlags::Instance);
				IntPtr _old = (IntPtr)_methodPtr->GetValue(_func);
				_methodPtr->SetValue(_func, _ptr);
				TResult ret = _func(ptr, args, _isValue);
				try
				{
					_methodPtr->SetValue(_func, _old);
				}
				catch (...)
				{
					_methodPtr->SetValue(_func, IntPtr::Zero);
				}
				Marshal::FreeHGlobal(_ptr);
				return ret;
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
			/// <summary>
			/// 执行一个方法地址
			/// </summary>
			/// <param name="ptr">方法地址</param>
			/// <param name="args">参数列表</param>
			static void PtrRun(IntPtr ptr, array<Object^>^ args)
			{
				PtrRun<int>((int)ptr, args);
			}
			/// <summary>
			/// 执行一个方法地址
			/// </summary>
			/// <param name="ptr">方法地址</param>
			/// <param name="args">参数列表</param>
			static void PtrRun(void* ptr, array<Object^>^ args)
			{
				PtrRun<int>((int)ptr, args);
			}
			/// <summary>
			/// 执行一个方法地址
			/// </summary>
			/// <param name="ptr">方法地址</param>
			/// <param name="args">参数列表</param>
			static void PtrRun(int ptr, array<Object^>^ args)
			{
				PtrRun<int>(ptr, args);
			}
			/// <summary>
			/// 执行一个方法地址
			/// </summary>
			/// <typeparam name="TResult">返回值类型</typeparam>
			/// <param name="ptr">方法地址</param>
			/// <param name="args">参数列表</param>
			/// <returns>执行结果</returns>
			generic <typename TResult> static TResult PtrRun(IntPtr ptr, array<Object^>^ args)
			{
				return PtrRun<TResult>((int)ptr, args);
			}
			/// <summary>
			/// 执行一个方法地址
			/// </summary>
			/// <typeparam name="TResult">返回值类型</typeparam>
			/// <param name="ptr">方法地址</param>
			/// <param name="args">参数列表</param>
			/// <returns>执行结果</returns>
			generic <typename TResult> static TResult PtrRun(void* ptr, array<Object^>^ args)
			{
				return PtrRun<TResult>((int)ptr, args);
			}
			/// <summary>
			/// 执行一个方法地址
			/// </summary>
			/// <typeparam name="TResult">返回值类型</typeparam>
			/// <param name="ptr">方法地址</param>
			/// <param name="args">参数列表</param>
			/// <returns>执行结果</returns>
			generic <typename TResult> static TResult PtrRun(int ptr, array<Object^>^ args)
			{
				const array<Byte>^ code = { 85, 137, 229, 81, 82, 83, 139, 69, 12, 139, 72, 4, 133, 201, 116, 85, 131, 192, 12, 139, 85, 8, 131, 194, 8, 138, 26, 132, 219, 139, 24, 116, 3, 139, 91, 4, 137, 223, 131, 249, 1, 116, 56, 131, 192, 4, 131, 194, 1, 138, 26, 132, 219, 139, 24, 116, 3, 139, 91, 4, 137, 222, 131, 249, 2, 116, 30, 131, 233, 2, 107, 217, 4, 1, 216, 1, 202, 138, 26, 132, 219, 139, 24, 116, 3, 139, 91, 4, 83, 131, 232, 4, 131, 234, 1, 226, 236, 137, 242, 137, 249, 139, 69, 248, 255, 208, 91, 201, 194, 4, 0 };
				return _PtrRun<TResult>(ptr, code, args);
			}
			/// <summary>
			/// 执行一个非IL方法地址
			/// </summary>
			/// <param name="ptr">方法地址</param>
			/// <param name="args">参数列表</param>
			static void PtrRun_Impl(IntPtr ptr, array<Object^>^ args)
			{
				PtrRun_Impl<int>((int)ptr, args);
			}
			/// <summary>
			/// 执行一个非IL方法地址
			/// </summary>
			/// <param name="ptr">方法地址</param>
			/// <param name="args">参数列表</param>
			static void PtrRun_Impl(void* ptr, array<Object^>^ args)
			{
				PtrRun_Impl<int>((int)ptr, args);
			}
			/// <summary>
			/// 执行一个非IL方法地址
			/// </summary>
			/// <param name="ptr">方法地址</param>
			/// <param name="args">参数列表</param>
			static void PtrRun_Impl(int ptr, array<Object^>^ args)
			{
				PtrRun_Impl<int>(ptr, args);
			}
			/// <summary>
			/// 执行一个非IL方法地址
			/// </summary>
			/// <typeparam name="TResult">返回值类型</typeparam>
			/// <param name="ptr">方法地址</param>
			/// <param name="args">参数列表</param>
			/// <returns>执行结果</returns>
			generic <typename TResult> static TResult PtrRun_Impl(IntPtr ptr, array<Object^>^ args)
			{
				return PtrRun_Impl<TResult>((int)ptr, args);
			}
			/// <summary>
			/// 执行一个非IL方法地址
			/// </summary>
			/// <typeparam name="TResult">返回值类型</typeparam>
			/// <param name="ptr">方法地址</param>
			/// <param name="args">参数列表</param>
			/// <returns>执行结果</returns>
			generic <typename TResult> static TResult PtrRun_Impl(void* ptr, array<Object^>^ args)
			{
				return PtrRun_Impl<TResult>((int)ptr, args);
			}
			/// <summary>
			/// 执行一个非IL方法地址
			/// </summary>
			/// <typeparam name="TResult">返回值类型</typeparam>
			/// <param name="ptr">方法地址</param>
			/// <param name="args">参数列表</param>
			/// <returns>执行结果</returns>
			generic <typename TResult> static TResult PtrRun_Impl(int ptr, array<Object^>^ args)
			{
				const array<Byte>^ code = { 85, 137, 229, 81, 82, 83, 139, 69, 12, 139, 72, 4, 133, 201, 116, 84, 131, 192, 12, 139, 85, 8, 131, 194, 8, 138, 26, 132, 219, 139, 24, 116, 3, 139, 91, 4, 137, 223, 131, 249, 1, 116, 55, 131, 192, 4, 131, 194, 1, 138, 26, 132, 219, 139, 24, 116, 3, 139, 91, 4, 137, 222, 131, 249, 2, 116, 29, 131, 192, 4, 131, 194, 1, 131, 233, 2, 138, 26, 132, 219, 139, 24, 116, 3, 139, 91, 4, 83, 131, 192, 4, 131, 194, 1, 226, 236, 137, 242, 137, 249, 139, 69, 248, 255, 208, 91, 201, 194, 4, 0 };
				return _PtrRun<TResult>(ptr, code, args);
			}
			/// <summary>
			/// 从数据地址中读取指定长度的字节码
			/// </summary>
			/// <param name="ptr">数据地址</param>
			/// <param name="len">读取长度</param>
			/// <returns>字节码</returns>
			static array<Byte>^ PtrToBin(IntPtr ptr, int len)
			{
				if (ptr == IntPtr::Zero) return nullptr;
				array<Byte>^ b = gcnew array<Byte>(len);
				for (int i = 0; i < len; i++) b[i] = Marshal::ReadByte(ptr, i);
				return b;
			}
			/// <summary>
			/// 从数据地址中读取指定长度的字节码
			/// </summary>
			/// <param name="ptr">数据地址</param>
			/// <param name="len">读取长度</param>
			/// <returns>字节码</returns>
			static array<Byte>^ PtrToBin(int ptr, int len)
			{
				return PtrToBin((IntPtr)ptr, len);
			}
			/// <summary>
			/// 从数据地址中读取指定长度的字节码
			/// </summary>
			/// <param name="ptr">数据地址</param>
			/// <param name="len">读取长度</param>
			/// <returns>字节码</returns>
			static array<Byte>^ PtrToBin(void* ptr, int len)
			{
				return PtrToBin((IntPtr)ptr, len);
			}
			/// <summary>
			/// 数据地址转化为对象
			/// </summary>
			/// <typeparam name="T">对象类型</typeparam>
			/// <param name="ptr">数据地址</param>
			/// <returns>对象</returns>
			generic <typename T> static T PtrToObj(IntPtr ptr)
			{
				return PtrToObj<T>((int)ptr);
			}
			/// <summary>
			/// 数据地址转化为对象
			/// </summary>
			/// <typeparam name="T">对象类型</typeparam>
			/// <param name="ptr">数据地址</param>
			/// <returns>对象</returns>
			generic <typename T> static T PtrToObj(void* ptr)
			{
				return PtrToObj<T>((int)ptr);
			}
			/// <summary>
			/// 数据地址转化为对象
			/// </summary>
			/// <typeparam name="T">对象类型</typeparam>
			/// <param name="ptr">数据地址</param>
			/// <returns>对象</returns>
			generic <typename T> static T PtrToObj(int ptr)
			{
				array<Byte>^ _code = { 137, 208, 195 };
				IntPtr _ptr = Marshal::AllocHGlobal(_code->Length);
				Marshal::Copy(_code, 0, _ptr, _code->Length);
				VirtualProtectExecute(_ptr, _code->Length);
				Func<int, T>^ _func = gcnew Func<int, T>(PtrToObj_Func<T>);
				FieldInfo^ _methodPtr = _func->GetType()->GetField("_methodPtr", BindingFlags::NonPublic | BindingFlags::Instance);
				IntPtr _old = (IntPtr)_methodPtr->GetValue(_func);
				_methodPtr->SetValue(_func, _ptr);
				T ret = _func(ptr);
				try
				{
					_methodPtr->SetValue(_func, _old);
				}
				catch (...)
				{
					_methodPtr->SetValue(_func, IntPtr::Zero);
				}
				Marshal::FreeHGlobal(_ptr);
				return ret;
			}
			/// <summary>
			/// 获取方法地址
			/// </summary>
			/// <param name="method"></param>
			/// <returns>方法地址</returns>
			static IntPtr GetPtr(Delegate^ method)
			{
				return GetPtr(method, false);
			}
			/// <summary>
			/// 获取方法地址
			/// </summary>
			/// <param name="method"></param>
			/// <returns>方法地址</returns>
			static IntPtr GetPtr(Delegate^ method, bool forcibly)
			{
				return GetPtr(method->Method, forcibly);
			}
			/// <summary>
			/// 获取方法地址
			/// </summary>
			/// <param name="method"></param>
			/// <returns>方法地址</returns>
			static IntPtr GetPtr(MethodBase^ method)
			{
				return GetPtr(method, false);
			}
			/// <summary>
			/// 获取方法地址
			/// </summary>
			/// <param name="method"></param>
			/// <returns>方法地址</returns>
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