#pragma once

#include <algorithm>
#include <string>
#include <vector>

// 指定的 std 标准容器 x 是否包含指定的 v 值 (存在则返回 true)
#define STD_EXISTS(x, v) (std::find(x.begin(), x.end(), v) != x.end())
// 指定的 std 标准容器 x 是否不包含指定的 v 值 (不存在则返回 true)
#define STD_NOT_EXISTS(x, v) (std::find(x.begin(), x.end(), v) == x.end())

#ifdef _WIN32
#define PATH_SEPARATOR "\\"
#define WIDE_PATH_SEPARATOR L"\\"
#else
#define PATH_SEPARATOR "/"
#define WIDE_PATH_SEPARATOR L"/"
#endif // _WIN32

bool isRegexMatched(const std::string& content, const std::string& patterns);
void strReplace(std::string& str, const std::string& from, const std::string& to);
void strReplace(std::wstring& str, const std::wstring& from, const std::wstring& to);
void strReplace(char* str, const char* from, const char* to);
bool strContain(std::vector<std::string> needle, const std::string& str);
bool strContain(std::string needle, const std::string& str);
std::vector<std::string> strExplode(std::string const& s, char delim);
std::string formatVersion(std::string ver, bool bPrefix, bool bSuffix, int ver_type);
bool isCommercialVersion();
std::string getPandasVersion(bool bPrefix = true, bool bSuffix = true);
