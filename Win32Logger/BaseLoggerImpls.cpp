#include "stdafx.h"

namespace MK{
	//Writes logger output directly to console
	class ConsoleLoggerImpl : public LoggerImpl{
		void WriteInternal(LPCTSTR message){
			wprintf(message);
		}
	};

	//Does nothing - allocates no memory and makes no function calls
	class NoOpLoggerImpl : public LoggerImpl{

		virtual void Debug(const LPCTSTR message){

		}

		virtual void Trace(const LPCTSTR message){

		}

		void WriteInternal(LPCTSTR message){

		}
	};

	//Writes logger output to file
	class FileSysLoggerImpl : public LoggerImpl{
		/* File Name */
		const LPCTSTR _logFileName = TEXT("markedup-win32debug.log");

		void WriteInternal(LPCTSTR message){
			HANDLE hLogFile;
			DWORD dwBytesWritten;
			try{
				hLogFile = CreateFile(_logFileName, FILE_GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
				if (hLogFile == INVALID_HANDLE_VALUE){
					char error_msg[128];
					wprintf(L"Could not create/open file %s - error: %d", _logFileName, GetLastError());
					return;
				}
				
				DWORD dwWritten = SetFilePointer(hLogFile, 0, NULL, FILE_END);
				BOOL write = WriteFile(hLogFile, message, lstrlenW(message) * 2, &dwBytesWritten, NULL);
				BOOL close = CloseHandle(hLogFile);
				if (write == FALSE || close == FALSE)
				{
					PrintError();
				}
				
			}
			catch (...){
				
			}
		}

		void PrintError(){
			DWORD dLastError = GetLastError();
			LPCTSTR strErrorMessage = NULL;

			FormatMessage(
				FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS |
				FORMAT_MESSAGE_ARGUMENT_ARRAY | FORMAT_MESSAGE_ALLOCATE_BUFFER,
				NULL,
				dLastError,
				0,
				(LPWSTR) &strErrorMessage,
				0,
				NULL);

			wprintf(strErrorMessage);
		}

	};

	LoggerImpl* Logger::SelectImpl(){
		return new FileSysLoggerImpl();
	}

}

