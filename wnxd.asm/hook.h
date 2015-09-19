using namespace System;
using namespace System::Collections::Generic;
using namespace System::Reflection;

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
			static Hook^ _GetSource(int methodtoken, MethodBase^ method);
		internal:
			Hook(int sourcetoken, MethodBase^ destination);
		public:
			/// <summary>
			/// hookһ������,ʹ�䱻����ʱ��ת����Ŀ�귽��
			/// </summary>
			/// <param name="source">��hook�ķ���</param>
			/// <param name="destination">ת����Ŀ�귽��</param>
			static void Register(Delegate^ source, Delegate^ destination);
			/// <summary>
			/// hookһ������,ʹ�䱻����ʱ��ת����Ŀ�귽��
			/// </summary>
			/// <param name="source">��hook�ķ���</param>
			/// <param name="destination">ת����Ŀ�귽��</param>
			/// <param name="forcibly">�Ƿ�ǿ��hook,����ͨhookʧЧʱ</param>
			static void Register(Delegate^ source, Delegate^ destination, bool forcibly);
			/// <summary>
			/// hookһ������,ʹ�䱻����ʱ��ת����Ŀ�귽��
			/// </summary>
			/// <param name="source">��hook�ķ�����ַ</param>
			/// <param name="sourcetoken">��hook�ķ�����ʶ</param>
			/// <param name="destination">ת����Ŀ�귽��</param>
			/// <param name="forcibly">�Ƿ�ǿ��hook,����ͨhookʧЧʱ</param>
			/// <param name="methodhandle">��hook�ķ������</param>
			/// <param name="il"></param>
			/// <param name="external"></param>
			static void Register(IntPtr source, int sourcetoken, Delegate^ destination, bool forcibly, int methodhandle, bool il, bool external);
			/// <summary>
			/// hookһ������,ʹ�䱻����ʱ��ת����Ŀ�귽��
			/// </summary>
			/// <param name="source">��hook�ķ�����ַ</param>
			/// <param name="sourcetoken">��hook�ķ�����ʶ</param>
			/// <param name="destination">ת����Ŀ�귽��</param>
			/// <param name="forcibly">�Ƿ�ǿ��hook,����ͨhookʧЧʱ</param>
			/// <param name="methodhandle">��hook�ķ������</param>
			/// <param name="il"></param>
			/// <param name="external"></param>
			static void Register(void* source, int sourcetoken, Delegate^ destination, bool forcibly, int methodhandle, bool il, bool external);
			/// <summary>
			/// hookһ������,ʹ�䱻����ʱ��ת����Ŀ�귽��
			/// </summary>
			/// <param name="source">��hook�ķ�����ַ</param>
			/// <param name="sourcetoken">��hook�ķ�����ʶ</param>
			/// <param name="destination">ת����Ŀ�귽��</param>
			/// <param name="forcibly">�Ƿ�ǿ��hook,����ͨhookʧЧʱ</param>
			/// <param name="methodhandle">��hook�ķ������</param>
			/// <param name="il"></param>
			/// <param name="external"></param>
			static void Register(int source, int sourcetoken, Delegate^ destination, bool forcibly, int methodhandle, bool il, bool external);
			/// <summary>
			/// hookһ������,ʹ�䱻����ʱ��ת����Ŀ�귽��
			/// </summary>
			/// <param name="source">��hook�ķ���</param>
			/// <param name="destination">ת����Ŀ�귽��</param>
			static void Register(MethodBase^ source, MethodBase^ destination);
			/// <summary>
			/// hookһ������,ʹ�䱻����ʱ��ת����Ŀ�귽��
			/// </summary>
			/// <param name="source">��hook�ķ���</param>
			/// <param name="destination">ת����Ŀ�귽��</param>
			/// <param name="forcibly">�Ƿ�ǿ��hook,����ͨhookʧЧʱ</param>
			static void Register(MethodBase^ source, MethodBase^ destination, bool forcibly);
			/// <summary>
			/// hookһ������,ʹ�䱻����ʱ��ת����Ŀ�귽��
			/// </summary>
			/// <param name="source">��hook�ķ�����ַ</param>
			/// <param name="sourcetoken">��hook�ķ�����ʶ</param>
			/// <param name="destination">ת����Ŀ�귽��</param>
			/// <param name="forcibly">�Ƿ�ǿ��hook,����ͨhookʧЧʱ</param>
			/// <param name="methodhandle">��hook�ķ������</param>
			/// <param name="il"></param>
			/// <param name="external"></param>
			static void Register(IntPtr source, int sourcetoken, MethodBase^ destination, bool forcibly, int methodhandle, bool il, bool external);
			/// <summary>
			/// hookһ������,ʹ�䱻����ʱ��ת����Ŀ�귽��
			/// </summary>
			/// <param name="source">��hook�ķ�����ַ</param>
			/// <param name="sourcetoken">��hook�ķ�����ʶ</param>
			/// <param name="destination">ת����Ŀ�귽��</param>
			/// <param name="forcibly">�Ƿ�ǿ��hook,����ͨhookʧЧʱ</param>
			/// <param name="methodhandle">��hook�ķ������</param>
			/// <param name="il"></param>
			/// <param name="external"></param>
			static void Register(void* source, int sourcetoken, MethodBase^ destination, bool forcibly, int methodhandle, bool il, bool external);
			/// <summary>
			/// hookһ������,ʹ�䱻����ʱ��ת����Ŀ�귽��
			/// </summary>
			/// <param name="source">��hook�ķ�����ַ</param>
			/// <param name="sourcetoken">��hook�ķ�����ʶ</param>
			/// <param name="destination">ת����Ŀ�귽��</param>
			/// <param name="forcibly">�Ƿ�ǿ��hook,����ͨhookʧЧʱ</param>
			/// <param name="methodhandle">��hook�ķ������</param>
			/// <param name="il"></param>
			/// <param name="external"></param>
			static void Register(int source, int sourcetoken, MethodBase^ destination, bool forcibly, int methodhandle, bool il, bool external);
			/// <summary>
			/// ȡ���˷�����hook
			/// </summary>
			/// <param name="source">��hook�ķ���</param>
			static void Unregister(Delegate^ source);
			/// <summary>
			/// ȡ���˷�����hook
			/// </summary>
			/// <param name="source">��hook�ķ���</param>
			static void Unregister(MethodBase^ source);
			/// <summary>
			/// ȡ���˷�����hook
			/// </summary>
			/// <param name="sourcetoken">��hook�ķ�����ʶ</param>
			static void Unregister(int sourcetoken);
			/// <summary>
			/// �Ӹö�����Ѱ��ָ������
			/// </summary>
			/// <param name="target">�����˷����Ķ���</param>
			/// <param name="methodname">������</param>
			/// <returns></returns>
			static MethodBase^ GetMethod(Object^ target, String^ methodname);
			/// <summary>
			/// �Ӹ�������Ѱ��ָ������
			/// </summary>
			/// <param name="type">�����˷���������</param>
			/// <param name="methodname">������</param>
			/// <returns></returns>
			static MethodBase^ GetMethod(Type^ type, String^ methodname);
			/// <summary>
			/// ǿ��ת����������
			/// </summary>
			/// <typeparam name="T">Ŀ������</typeparam>
			/// <param name="target">��Ҫת�����͵Ķ���</param>
			/// <returns>ת�����ͺ�Ķ���</returns>
			generic <typename T> static T Change(Object^ target);
			/// <summary>
			/// �л�hook����Ŀ���
			/// </summary>
			void Switch();
			/// <summary>
			/// �ı�hook����Ŀ���״̬
			/// </summary>
			/// <param name="ishook">�Ƿ���hook</param>
			void Switch(bool ishook);
			/// <summary>
			/// ���ñ�hook�����ԭ����
			/// </summary>
			/// <typeparam name="TResult">��������</typeparam>
			/// <param name="args">�����б�</param>
			/// <returns>����ֵ</returns>
			generic <typename TResult> TResult Run(...array<Object^>^ args);
			/// <summary>
			/// ���ñ�hook�����ԭ����
			/// </summary>
			/// <param name="args">�����б�</param>
			void Run(...array<Object^>^ args);
			/// <summary>
			/// �����ǰ����Ϊת��Ŀ�귽��,���ȡ�Դ�ΪĿ��ĵ�һ��hook����,����Ϊnull
			/// </summary>
			static property Hook^ Source
			{
				Hook^ get();
			}
			/// <summary>
			/// ��ȡָ��������hook����,������뷽��δ����ǰ����hook�򷵻�null
			/// </summary>
			/// <param name="method">��hook�ķ���</param>
			/// <returns></returns>
			static Hook^ GetSource(Delegate^ method);
			/// <summary>
			/// ��ȡָ��������hook����,������뷽��δ����ǰ����hook�򷵻�null
			/// </summary>
			/// <param name="method">��hook�ķ���</param>
			/// <returns></returns>
			static Hook^ GetSource(MethodBase^ method);
			/// <summary>
			/// ��ȡָ��������hook����,������뷽��δ����ǰ����hook�򷵻�null
			/// </summary>
			/// <param name="methodtoken">��hook�ķ�����ʶ</param>
			/// <returns></returns>
			static Hook^ GetSource(int methodtoken);
		};
	}
}