#pragma once

#include <string>

namespace CocosDenshion
{
std::wstring CCUtf8ToUnicode(const char * pszUtf8Str);
std::string CCUnicodeToUtf8(const wchar_t* pwszStr);
std::string GetFileSuffix(const char *filePath);
}