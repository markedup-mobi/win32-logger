#include "stdafx.h"
namespace MK {

	/* Method implementations */
	LPCTSTR LoggerImpl::FormatLogMessage(LPCTSTR logLevel, LPCTSTR message){
		DWORD processId = GetCurrentProcessId();
		LPCTSTR now = CurrentTime();

		TCHAR *buff = new TCHAR[MAX_BUFFER];
		int length = swprintf_s(buff, MAX_BUFFER, _formatString, processId, logLevel, now, message);
		delete []now;
		return buff;
	}

	LPCTSTR LoggerImpl::CurrentTime(){
		SYSTEMTIME st;
		GetLocalTime(&st);

		TCHAR *buff = new TCHAR[80];
		int length = swprintf_s(buff, 80, L"%02d/%02d/%02d %02d:%02d:%02d", st.wMonth, st.wDay, st.wYear, st.wHour, st.wMinute, st.wSecond);
		return buff;
	}

	void LoggerImpl::Debug(const LPCTSTR message){
		LPCTSTR finalMessage = FormatLogMessage(_debug, message);
		WriteInternal(finalMessage);
		CleanUp(finalMessage);
	}
	void LoggerImpl::Trace(const LPCTSTR message){
		LPCTSTR finalMessage = FormatLogMessage(_trace, message);
		WriteInternal(finalMessage);
		CleanUp(finalMessage);
	}

	void LoggerImpl::CleanUp(LPCTSTR message){
		delete []message;
	}	

	static Logger* _instance;

	Logger* Logger::Instance(){
		if (_instance == NULL){ //lazy instantiation
			_instance = new Logger(SelectImpl());
		}

		return _instance;
	}
	
	Logger::Logger(LoggerImpl* impl){
		Impl = impl;
	}

	void Logger::Debug(const LPCTSTR message){
		Impl->Debug(message);
	}

	void Logger::Trace(const LPCTSTR message){
		Impl->Trace(message);
	}
}