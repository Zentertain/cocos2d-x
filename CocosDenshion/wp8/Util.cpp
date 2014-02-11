#include "Util.h"
#include <Windows.h>

namespace CocosDenshion
{

std::wstring CCUtf8ToUnicode(const char * pszUtf8Str)
{
	std::wstring ret;
	do
	{
		if (! pszUtf8Str) break;
		size_t len = strlen(pszUtf8Str);
		if (len <= 0) break;
		++len;
		wchar_t * pwszStr = new wchar_t[len];
		if (! pwszStr) break;
		pwszStr[len - 1] = 0;
		MultiByteToWideChar(CP_UTF8, 0, pszUtf8Str, len, pwszStr, len);
		ret = pwszStr;

		if(pwszStr) { 
			delete[] (pwszStr); 
			(pwszStr) = 0; 
		}


	} while (0);
	return ret;
}

std::string CCUnicodeToUtf8(const wchar_t* pwszStr)
{
	std::string ret;
	do
	{
		if(! pwszStr) break;
		size_t len = wcslen(pwszStr);
		if (len <= 0) break;

		char * pszUtf8Str = new char[len*3 + 1];
		WideCharToMultiByte(CP_UTF8, 0, pwszStr, len+1, pszUtf8Str, len*3 + 1, 0, 0);
		ret = pszUtf8Str;

		if(pszUtf8Str) { 
			delete[] (pszUtf8Str); 
			(pszUtf8Str) = 0; 
		}
	}while(0);

	return ret;
}

std::string GetFileSuffix(const char *filePath)
{
	std::string suffix(filePath);
	size_t dotIndex = suffix.find_last_of('.');
	if (dotIndex != std::string::npos)
		return suffix.substr(dotIndex + 1);
	return "";
}

}
