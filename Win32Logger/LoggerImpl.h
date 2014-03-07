/*Concrete logger implementations*/
namespace MK{
	
	class LoggerImpl{
	public:
		virtual void Debug(const LPCTSTR message);
		virtual void Trace(const LPCTSTR message);

		/*Constants*/
		const LPCTSTR _formatString = TEXT("%d - %s %s: %s\r\n");
		const LPCTSTR _trace = TEXT("TRACE");
		const LPCTSTR _debug = TEXT("DEBUG");
		const unsigned int MAX_BUFFER = 2048;

	protected:
		LPCTSTR FormatLogMessage(LPCTSTR logLevel, LPCTSTR message);
		LPCTSTR CurrentTime();
		void CleanUp(LPCTSTR message);
		virtual void WriteInternal(LPCTSTR message) = 0; //pure abstract method
	};
}