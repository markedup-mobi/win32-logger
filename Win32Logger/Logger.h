/*
 Logging methods
 */
namespace MK{
	class Logger{
	public:
		static Logger* Instance();
		void Debug(const LPCTSTR message);
		void Trace(const LPCTSTR message);
	protected:
		LoggerImpl* Impl;
		Logger(LoggerImpl* impl);
		~Logger();
	private:
		static LoggerImpl* SelectImpl();
	};
}