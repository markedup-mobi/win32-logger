// Win32Logger.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	MK::Logger::Instance()->Trace(TEXT("Hello!"));
	MK::Logger::Instance()->Debug(TEXT("How are you?"));
	int stop = scanf_s("Hit enter\r\n");
	return 0;
}

