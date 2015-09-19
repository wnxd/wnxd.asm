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
			/// ִ��һ��������ַ
			/// </summary>
			/// <param name="ptr">������ַ</param>
			/// <param name="args">�����б�</param>
			static void PtrRun(IntPtr ptr, ...array<Object^>^ args);
			/// <summary>
			/// ִ��һ��������ַ
			/// </summary>
			/// <param name="ptr">������ַ</param>
			/// <param name="args">�����б�</param>
			static void PtrRun(void* ptr, ...array<Object^>^ args);
			/// <summary>
			/// ִ��һ��������ַ
			/// </summary>
			/// <param name="ptr">������ַ</param>
			/// <param name="args">�����б�</param>
			static void PtrRun(int ptr, ...array<Object^>^ args);
			/// <summary>
			/// ִ��һ��������ַ
			/// </summary>
			/// <typeparam name="TResult">����ֵ����</typeparam>
			/// <param name="ptr">������ַ</param>
			/// <param name="args">�����б�</param>
			/// <returns>ִ�н��</returns>
			generic <typename TResult> static TResult PtrRun(IntPtr ptr, ...array<Object^>^ args);
			/// <summary>
			/// ִ��һ��������ַ
			/// </summary>
			/// <typeparam name="TResult">����ֵ����</typeparam>
			/// <param name="ptr">������ַ</param>
			/// <param name="args">�����б�</param>
			/// <returns>ִ�н��</returns>
			generic <typename TResult> static TResult PtrRun(void* ptr, ...array<Object^>^ args);
			/// <summary>
			/// ִ��һ��������ַ
			/// </summary>
			/// <typeparam name="TResult">����ֵ����</typeparam>
			/// <param name="ptr">������ַ</param>
			/// <param name="args">�����б�</param>
			/// <returns>ִ�н��</returns>
			generic <typename TResult> static TResult PtrRun(int ptr, ...array<Object^>^ args);
			/// <summary>
			/// ִ��һ����IL������ַ
			/// </summary>
			/// <param name="ptr">������ַ</param>
			/// <param name="args">�����б�</param>
			static void PtrRun_Impl(IntPtr ptr, ...array<Object^>^ args);
			/// <summary>
			/// ִ��һ����IL������ַ
			/// </summary>
			/// <param name="ptr">������ַ</param>
			/// <param name="args">�����б�</param>
			static void PtrRun_Impl(void* ptr, ...array<Object^>^ args);
			/// <summary>
			/// ִ��һ����IL������ַ
			/// </summary>
			/// <param name="ptr">������ַ</param>
			/// <param name="args">�����б�</param>
			static void PtrRun_Impl(int ptr, ...array<Object^>^ args);
			/// <summary>
			/// ִ��һ����IL������ַ
			/// </summary>
			/// <typeparam name="TResult">����ֵ����</typeparam>
			/// <param name="ptr">������ַ</param>
			/// <param name="args">�����б�</param>
			/// <returns>ִ�н��</returns>
			generic <typename TResult> static TResult PtrRun_Impl(IntPtr ptr, ...array<Object^>^ args);
			/// <summary>
			/// ִ��һ����IL������ַ
			/// </summary>
			/// <typeparam name="TResult">����ֵ����</typeparam>
			/// <param name="ptr">������ַ</param>
			/// <param name="args">�����б�</param>
			/// <returns>ִ�н��</returns>
			generic <typename TResult> static TResult PtrRun_Impl(void* ptr, ...array<Object^>^ args);
			/// <summary>
			/// ִ��һ����IL������ַ
			/// </summary>
			/// <typeparam name="TResult">����ֵ����</typeparam>
			/// <param name="ptr">������ַ</param>
			/// <param name="args">�����б�</param>
			/// <returns>ִ�н��</returns>
			generic <typename TResult> static TResult PtrRun_Impl(int ptr, ...array<Object^>^ args);
			/// <summary>
			/// �����ݵ�ַ�ж�ȡָ�����ȵ��ֽ���
			/// </summary>
			/// <param name="ptr">���ݵ�ַ</param>
			/// <param name="len">��ȡ����</param>
			/// <returns>�ֽ���</returns>
			static array<Byte>^ PtrToBin(IntPtr ptr, int len);
			/// <summary>
			/// �����ݵ�ַ�ж�ȡָ�����ȵ��ֽ���
			/// </summary>
			/// <param name="ptr">���ݵ�ַ</param>
			/// <param name="len">��ȡ����</param>
			/// <returns>�ֽ���</returns>
			static array<Byte>^ PtrToBin(int ptr, int len);
			/// <summary>
			/// �����ݵ�ַ�ж�ȡָ�����ȵ��ֽ���
			/// </summary>
			/// <param name="ptr">���ݵ�ַ</param>
			/// <param name="len">��ȡ����</param>
			/// <returns>�ֽ���</returns>
			static array<Byte>^ PtrToBin(void* ptr, int len);
			/// <summary>
			/// ���ݵ�ַת��Ϊ����
			/// </summary>
			/// <typeparam name="T">��������</typeparam>
			/// <param name="ptr">���ݵ�ַ</param>
			/// <returns>����</returns>
			generic <typename T> static T PtrToObj(IntPtr ptr);
			/// <summary>
			/// ���ݵ�ַת��Ϊ����
			/// </summary>
			/// <typeparam name="T">��������</typeparam>
			/// <param name="ptr">���ݵ�ַ</param>
			/// <returns>����</returns>
			generic <typename T> static T PtrToObj(void* ptr);
			/// <summary>
			/// ���ݵ�ַת��Ϊ����
			/// </summary>
			/// <typeparam name="T">��������</typeparam>
			/// <param name="ptr">���ݵ�ַ</param>
			/// <returns>����</returns>
			generic <typename T> static T PtrToObj(int ptr);
			/// <summary>
			/// ��ȡ������ַ
			/// </summary>
			/// <param name="method"></param>
			/// <returns>������ַ</returns>
			static IntPtr GetPtr(Delegate^ method);
			/// <summary>
			/// ��ȡ������ַ
			/// </summary>
			/// <param name="method"></param>
			/// <returns>������ַ</returns>
			static IntPtr GetPtr(Delegate^ method, bool forcibly);
			/// <summary>
			/// ��ȡ������ַ
			/// </summary>
			/// <param name="method"></param>
			/// <returns>������ַ</returns>
			static IntPtr GetPtr(MethodBase^ method);
			/// <summary>
			/// ��ȡ������ַ
			/// </summary>
			/// <param name="method"></param>
			/// <returns>������ַ</returns>
			static IntPtr GetPtr(MethodBase^ method, bool forcibly);
		};
	}
}