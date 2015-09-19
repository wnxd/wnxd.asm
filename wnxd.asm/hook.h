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
			/// hook一个方法,使其被调用时会转跳到目标方法
			/// </summary>
			/// <param name="source">被hook的方法</param>
			/// <param name="destination">转跳的目标方法</param>
			static void Register(Delegate^ source, Delegate^ destination);
			/// <summary>
			/// hook一个方法,使其被调用时会转跳到目标方法
			/// </summary>
			/// <param name="source">被hook的方法</param>
			/// <param name="destination">转跳的目标方法</param>
			/// <param name="forcibly">是否强制hook,当普通hook失效时</param>
			static void Register(Delegate^ source, Delegate^ destination, bool forcibly);
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
			static void Register(IntPtr source, int sourcetoken, Delegate^ destination, bool forcibly, int methodhandle, bool il, bool external);
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
			static void Register(void* source, int sourcetoken, Delegate^ destination, bool forcibly, int methodhandle, bool il, bool external);
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
			static void Register(int source, int sourcetoken, Delegate^ destination, bool forcibly, int methodhandle, bool il, bool external);
			/// <summary>
			/// hook一个方法,使其被调用时会转跳到目标方法
			/// </summary>
			/// <param name="source">被hook的方法</param>
			/// <param name="destination">转跳的目标方法</param>
			static void Register(MethodBase^ source, MethodBase^ destination);
			/// <summary>
			/// hook一个方法,使其被调用时会转跳到目标方法
			/// </summary>
			/// <param name="source">被hook的方法</param>
			/// <param name="destination">转跳的目标方法</param>
			/// <param name="forcibly">是否强制hook,当普通hook失效时</param>
			static void Register(MethodBase^ source, MethodBase^ destination, bool forcibly);
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
			static void Register(IntPtr source, int sourcetoken, MethodBase^ destination, bool forcibly, int methodhandle, bool il, bool external);
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
			static void Register(void* source, int sourcetoken, MethodBase^ destination, bool forcibly, int methodhandle, bool il, bool external);
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
			static void Register(int source, int sourcetoken, MethodBase^ destination, bool forcibly, int methodhandle, bool il, bool external);
			/// <summary>
			/// 取消此方法的hook
			/// </summary>
			/// <param name="source">被hook的方法</param>
			static void Unregister(Delegate^ source);
			/// <summary>
			/// 取消此方法的hook
			/// </summary>
			/// <param name="source">被hook的方法</param>
			static void Unregister(MethodBase^ source);
			/// <summary>
			/// 取消此方法的hook
			/// </summary>
			/// <param name="sourcetoken">被hook的方法标识</param>
			static void Unregister(int sourcetoken);
			/// <summary>
			/// 从该对象中寻找指定方法
			/// </summary>
			/// <param name="target">包含此方法的对象</param>
			/// <param name="methodname">方法名</param>
			/// <returns></returns>
			static MethodBase^ GetMethod(Object^ target, String^ methodname);
			/// <summary>
			/// 从该类型中寻找指定方法
			/// </summary>
			/// <param name="type">包含此方法的类型</param>
			/// <param name="methodname">方法名</param>
			/// <returns></returns>
			static MethodBase^ GetMethod(Type^ type, String^ methodname);
			/// <summary>
			/// 强制转换对象类型
			/// </summary>
			/// <typeparam name="T">目标类型</typeparam>
			/// <param name="target">需要转换类型的对象</param>
			/// <returns>转换类型后的对象</returns>
			generic <typename T> static T Change(Object^ target);
			/// <summary>
			/// 切换hook对象的开关
			/// </summary>
			void Switch();
			/// <summary>
			/// 改变hook对象的开关状态
			/// </summary>
			/// <param name="ishook">是否开启hook</param>
			void Switch(bool ishook);
			/// <summary>
			/// 调用被hook对象的原方法
			/// </summary>
			/// <typeparam name="TResult">返回类型</typeparam>
			/// <param name="args">参数列表</param>
			/// <returns>返回值</returns>
			generic <typename TResult> TResult Run(...array<Object^>^ args);
			/// <summary>
			/// 调用被hook对象的原方法
			/// </summary>
			/// <param name="args">参数列表</param>
			void Run(...array<Object^>^ args);
			/// <summary>
			/// 如果当前方法为转跳目标方法,则获取以此为目标的第一个hook对象,否则为null
			/// </summary>
			static property Hook^ Source
			{
				Hook^ get();
			}
			/// <summary>
			/// 获取指定方法的hook对象,如果传入方法未被当前方法hook则返回null
			/// </summary>
			/// <param name="method">被hook的方法</param>
			/// <returns></returns>
			static Hook^ GetSource(Delegate^ method);
			/// <summary>
			/// 获取指定方法的hook对象,如果传入方法未被当前方法hook则返回null
			/// </summary>
			/// <param name="method">被hook的方法</param>
			/// <returns></returns>
			static Hook^ GetSource(MethodBase^ method);
			/// <summary>
			/// 获取指定方法的hook对象,如果传入方法未被当前方法hook则返回null
			/// </summary>
			/// <param name="methodtoken">被hook的方法标识</param>
			/// <returns></returns>
			static Hook^ GetSource(int methodtoken);
		};
	}
}