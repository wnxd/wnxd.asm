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
			generic <typename TResult> static TResult _PtrRun_Func(int p, array<Object^>^ a, array<bool>^ i);
			generic <typename TResult> static TResult PtrToObj_Func(int p);
			generic <typename TResult> static TResult _PtrRun(int ptr, array<Byte>^ code, array<Object^>^ args);
		internal:
			static bool IsExternal(MethodBase^ method);
			static void VirtualProtectExecute(IntPtr address, int size);
			static void VirtualProtectExecute(void* address, int size);
		public:
			/// <summary>
			/// 执行一个方法地址
			/// </summary>
			/// <param name="ptr">方法地址</param>
			/// <param name="args">参数列表</param>
			static void PtrRun(IntPtr ptr, ...array<Object^>^ args);
			/// <summary>
			/// 执行一个方法地址
			/// </summary>
			/// <param name="ptr">方法地址</param>
			/// <param name="args">参数列表</param>
			static void PtrRun(void* ptr, ...array<Object^>^ args);
			/// <summary>
			/// 执行一个方法地址
			/// </summary>
			/// <param name="ptr">方法地址</param>
			/// <param name="args">参数列表</param>
			static void PtrRun(int ptr, ...array<Object^>^ args);
			/// <summary>
			/// 执行一个方法地址
			/// </summary>
			/// <typeparam name="TResult">返回值类型</typeparam>
			/// <param name="ptr">方法地址</param>
			/// <param name="args">参数列表</param>
			/// <returns>执行结果</returns>
			generic <typename TResult> static TResult PtrRun(IntPtr ptr, ...array<Object^>^ args);
			/// <summary>
			/// 执行一个方法地址
			/// </summary>
			/// <typeparam name="TResult">返回值类型</typeparam>
			/// <param name="ptr">方法地址</param>
			/// <param name="args">参数列表</param>
			/// <returns>执行结果</returns>
			generic <typename TResult> static TResult PtrRun(void* ptr, ...array<Object^>^ args);
			/// <summary>
			/// 执行一个方法地址
			/// </summary>
			/// <typeparam name="TResult">返回值类型</typeparam>
			/// <param name="ptr">方法地址</param>
			/// <param name="args">参数列表</param>
			/// <returns>执行结果</returns>
			generic <typename TResult> static TResult PtrRun(int ptr, ...array<Object^>^ args);
			/// <summary>
			/// 执行一个非IL方法地址
			/// </summary>
			/// <param name="ptr">方法地址</param>
			/// <param name="args">参数列表</param>
			static void PtrRun_Impl(IntPtr ptr, ...array<Object^>^ args);
			/// <summary>
			/// 执行一个非IL方法地址
			/// </summary>
			/// <param name="ptr">方法地址</param>
			/// <param name="args">参数列表</param>
			static void PtrRun_Impl(void* ptr, ...array<Object^>^ args);
			/// <summary>
			/// 执行一个非IL方法地址
			/// </summary>
			/// <param name="ptr">方法地址</param>
			/// <param name="args">参数列表</param>
			static void PtrRun_Impl(int ptr, ...array<Object^>^ args);
			/// <summary>
			/// 执行一个非IL方法地址
			/// </summary>
			/// <typeparam name="TResult">返回值类型</typeparam>
			/// <param name="ptr">方法地址</param>
			/// <param name="args">参数列表</param>
			/// <returns>执行结果</returns>
			generic <typename TResult> static TResult PtrRun_Impl(IntPtr ptr, ...array<Object^>^ args);
			/// <summary>
			/// 执行一个非IL方法地址
			/// </summary>
			/// <typeparam name="TResult">返回值类型</typeparam>
			/// <param name="ptr">方法地址</param>
			/// <param name="args">参数列表</param>
			/// <returns>执行结果</returns>
			generic <typename TResult> static TResult PtrRun_Impl(void* ptr, ...array<Object^>^ args);
			/// <summary>
			/// 执行一个非IL方法地址
			/// </summary>
			/// <typeparam name="TResult">返回值类型</typeparam>
			/// <param name="ptr">方法地址</param>
			/// <param name="args">参数列表</param>
			/// <returns>执行结果</returns>
			generic <typename TResult> static TResult PtrRun_Impl(int ptr, ...array<Object^>^ args);
			/// <summary>
			/// 从数据地址中读取指定长度的字节码
			/// </summary>
			/// <param name="ptr">数据地址</param>
			/// <param name="len">读取长度</param>
			/// <returns>字节码</returns>
			static array<Byte>^ PtrToBin(IntPtr ptr, int len);
			/// <summary>
			/// 从数据地址中读取指定长度的字节码
			/// </summary>
			/// <param name="ptr">数据地址</param>
			/// <param name="len">读取长度</param>
			/// <returns>字节码</returns>
			static array<Byte>^ PtrToBin(int ptr, int len);
			/// <summary>
			/// 从数据地址中读取指定长度的字节码
			/// </summary>
			/// <param name="ptr">数据地址</param>
			/// <param name="len">读取长度</param>
			/// <returns>字节码</returns>
			static array<Byte>^ PtrToBin(void* ptr, int len);
			/// <summary>
			/// 数据地址转化为对象
			/// </summary>
			/// <typeparam name="T">对象类型</typeparam>
			/// <param name="ptr">数据地址</param>
			/// <returns>对象</returns>
			generic <typename T> static T PtrToObj(IntPtr ptr);
			/// <summary>
			/// 数据地址转化为对象
			/// </summary>
			/// <typeparam name="T">对象类型</typeparam>
			/// <param name="ptr">数据地址</param>
			/// <returns>对象</returns>
			generic <typename T> static T PtrToObj(void* ptr);
			/// <summary>
			/// 数据地址转化为对象
			/// </summary>
			/// <typeparam name="T">对象类型</typeparam>
			/// <param name="ptr">数据地址</param>
			/// <returns>对象</returns>
			generic <typename T> static T PtrToObj(int ptr);
			/// <summary>
			/// 获取方法地址
			/// </summary>
			/// <param name="method"></param>
			/// <returns>方法地址</returns>
			static IntPtr GetPtr(Delegate^ method);
			/// <summary>
			/// 获取方法地址
			/// </summary>
			/// <param name="method"></param>
			/// <returns>方法地址</returns>
			static IntPtr GetPtr(Delegate^ method, bool forcibly);
			/// <summary>
			/// 获取方法地址
			/// </summary>
			/// <param name="method"></param>
			/// <returns>方法地址</returns>
			static IntPtr GetPtr(MethodBase^ method);
			/// <summary>
			/// 获取方法地址
			/// </summary>
			/// <param name="method"></param>
			/// <returns>方法地址</returns>
			static IntPtr GetPtr(MethodBase^ method, bool forcibly);
		};
	}
}