#include "assistant.hpp"

#include <algorithm>
#include <cctype>
#include <cstring>
#include <regex>
#include <sstream>
#include <utility>
#include <string>

#include <config/pandas.hpp>

#include "showmsg.hpp"

#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

bool isRegexMatched(const std::string& content, const std::string& patterns) {
	try {
		std::regex re(patterns, std::regex::icase);
		std::smatch match_result;
		return std::regex_search(content, match_result, re);
	}
	catch (const std::regex_error& e) {
		ShowWarning("%s throw regex_error : %s\n", __func__, e.what());
		return false;
	}
}

void strReplace(std::string& str, const std::string& from, const std::string& to) {
	if (from.empty())
		return;

	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}

void strReplace(std::wstring& str, const std::wstring& from, const std::wstring& to) {
	if (from.empty())
		return;

	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::wstring::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}

void strReplace(char* str, const char* from, const char* to) {
	size_t len = strlen(str);
	size_t from_len = strlen(from), to_len = strlen(to);
	for (char* p = str; (p = strstr(p, from)); ++p) {
		if (from_len != to_len)
			memmove(p + to_len, p + from_len, len - (p - str) + to_len);
		memcpy(p, to, to_len);
	}
}

bool strContain(std::vector<std::string> needle, const std::string& str) {
	for (const std::string& it : needle) {
		if (strContain(it, str))
			return true;
	}

	return false;
}

bool strContain(std::string needle, const std::string& str) {
	auto it = std::search(
		str.begin(), str.end(),
		needle.begin(), needle.end(),
		[](unsigned char ch1, unsigned char ch2) { return std::toupper(ch1) == std::toupper(ch2); }
	);

	return it != str.end();
}

std::vector<std::string> strExplode(std::string const& s, char delim) {
	std::vector<std::string> result;
	std::istringstream iss(s);

	for (std::string token; std::getline(iss, token, delim); ) {
		result.push_back(std::move(token));
	}

	if (!s.empty() && s.back() == delim)
		result.push_back("");

	return result;
}

std::string formatVersion(std::string ver, bool bPrefix, bool bSuffix, int ver_type) {
	std::vector<std::string> split = strExplode(ver, '.');

	if (split.size() < 3)
		return (bPrefix ? "v" : "") + ver;

	if (split.size() < 4)
		split.resize(4, "0");

	std::string suffix;
	if (ver_type == 0) {
		suffix = split.back() == "1" ? "-dev" : "";
	}
	else {
		suffix = split.back() != "0" ? " Rev." + split.back() : "";
	}

	return std::string(bPrefix ? "v" : "") + split[0] + "." + split[1] + "." + split[2] + (bSuffix ? suffix : "");
}

bool isCommercialVersion() {
#ifdef Pandas_Commercial_Version
	return true;
#else
	return false;
#endif // Pandas_Commercial_Version
}

inline const char* getDefinedVersion() {
#ifdef Pandas_Commercial_Version
	return Pandas_Commercial_Version;
#else
	return Pandas_Version;
#endif // Pandas_Commercial_Version
}

#ifdef _WIN32
static std::string versionPartToString(WORD value, size_t width = 0) {
	std::string part = std::to_string(value);

	if (part.length() < width)
		part.insert(part.begin(), width - part.length(), '0');

	return part;
}
#endif // _WIN32

#ifdef Pandas_Version
// Method:      getPandasVersion
// Description: 用于获取 Pandas 的主程序版本号
// Parameter:   bool bPrefix
// Parameter:   bool bSuffix
// Returns:     std::string
// Author:      Sola丶小克(CairoLee)  2019/11/04 23:20
std::string getPandasVersion(bool bPrefix, bool bSuffix) {
#ifdef _WIN32
	std::string szDefaultVersion = formatVersion(getDefinedVersion(), bPrefix, bSuffix, isCommercialVersion() ? 1 : 0);
	// 获取当前的文件名
	char szModulePath[MAX_PATH] = { 0 };
	if (GetModuleFileName(NULL, szModulePath, MAX_PATH) == 0) {
		ShowWarning("%s: Could not get module file name, defaulting to '%s'\n", __func__, szDefaultVersion.c_str());
		return szDefaultVersion;
	}
	std::string filename = std::string(szModulePath);
	// 获取文件版本信息的结构体大小
	DWORD dwInfoSize = 0, dwHandle = 0;
	dwInfoSize = GetFileVersionInfoSize(filename.c_str(), &dwHandle);
	if (dwInfoSize == 0) {
		ShowWarning("%s: Could not get version info size, defaulting to '%s'\n", __func__, szDefaultVersion.c_str());
		return szDefaultVersion;
	}
	// 获取文件的版本号, 预期格式为: x.x.x.x
	void* pVersionInfo = new char[dwInfoSize];
	dwHandle = 0; // 根据 GetFileVersionInfoA 标准, 这里的 dwHandle 应确保为 0
	if (GetFileVersionInfo(filename.c_str(), dwHandle, dwInfoSize, pVersionInfo)) {
		void* lpBuffer = NULL;
		UINT nItemLength = 0;
		if (VerQueryValue(pVersionInfo, "\\", &lpBuffer, &nItemLength)) {
			VS_FIXEDFILEINFO *pFileInfo = (VS_FIXEDFILEINFO*)lpBuffer;
			std::string sFileVersion;

			if (isCommercialVersion()) {
				sFileVersion = versionPartToString(HIWORD(pFileInfo->dwFileVersionMS), 4) + "." +
					versionPartToString(LOWORD(pFileInfo->dwProductVersionMS), 2) + "." +
					versionPartToString(HIWORD(pFileInfo->dwProductVersionLS), 2) + "." +
					versionPartToString(LOWORD(pFileInfo->dwProductVersionLS));
			}
			else {
				sFileVersion = versionPartToString(HIWORD(pFileInfo->dwFileVersionMS)) + "." +
					versionPartToString(LOWORD(pFileInfo->dwProductVersionMS)) + "." +
					versionPartToString(HIWORD(pFileInfo->dwProductVersionLS)) + "." +
					versionPartToString(LOWORD(pFileInfo->dwProductVersionLS));
			}

			delete[] pVersionInfo;
			return formatVersion(sFileVersion, bPrefix, bSuffix, isCommercialVersion() ? 1 : 0);
		}
	}
	delete[] pVersionInfo;
	ShowWarning("%s: Could not get file version, defaulting to '%s'\n", __func__, szDefaultVersion.c_str());
	return szDefaultVersion;
#else
	return formatVersion(getDefinedVersion(), bPrefix, bSuffix, isCommercialVersion() ? 1 : 0);
#endif // _WIN32
}
#endif // Pandas_Version
