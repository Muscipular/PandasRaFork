#include "assistant.hpp"

#include <algorithm>
#include <cctype>
#include <cstring>
#include <filesystem>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#include <config/pandas.hpp>

#include "processmutex.hpp"
#include "showmsg.hpp"
#include "strlib.hpp"

#if defined(_MSC_VER)
extern "C" int __isa_available;
#endif // defined(_MSC_VER)

#ifdef _WIN32
#include <Windows.h>
#else
#include <limits.h>
#include <unistd.h>
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

void isaAvailableHotfix() {
#if defined(_MSC_VER) && _MSC_VER == 1923
	if (__isa_available > 5) {
		__isa_available = 5;
	}
#endif // defined(_MSC_VER) && _MSC_VER == 1923
}

bool deployImportDirectory(std::string fromImportDir, std::string toImportDir) {
	std::string workDirectory;
	if (!getExecuteFileDirectory(workDirectory)) {
		return false;
	}

	std::string fromDirectory = workDirectory + fromImportDir;
	std::string toDirectory = workDirectory + toImportDir;

	ensurePathEndwithSep(fromDirectory, PATH_SEPARATOR);
	ensurePathEndwithSep(toDirectory, PATH_SEPARATOR);

	standardizePathSep(fromDirectory);
	standardizePathSep(toDirectory);

	if (!isDirectoryExists(toDirectory)) {
		if (!copyDirectory(fromDirectory, toDirectory)) {
			ShowWarning("Could not copy %s to %s.\n", fromImportDir.c_str(), toImportDir.c_str());
			return false;
		}
	}

	try {
		for (const auto& entry : std::filesystem::directory_iterator(fromDirectory)) {
			if (!entry.is_regular_file()) {
				continue;
			}

			std::filesystem::path toFullPath = std::filesystem::path(toDirectory) / entry.path().filename();
			if (isFileExists(toFullPath.string())) {
				continue;
			}

			std::string displayTargetPath = toImportDir;
			ensurePathEndwithSep(displayTargetPath, PATH_SEPARATOR);
			displayTargetPath += entry.path().filename().string();
			standardizePathSep(displayTargetPath);

			if (!copyFile(entry.path().string(), toFullPath.string())) {
				ShowWarning("Deploy %s is failed.\n", displayTargetPath.c_str());
			}
			else {
				ShowInfo("Deploy %s is successful.\n", displayTargetPath.c_str());
			}
		}
	}
	catch (const std::filesystem::filesystem_error& e) {
		ShowWarning("%s: %s\n", __func__, e.what());
		return false;
	}

	if (!isDirectoryExists(std::string(workDirectory + "src"))) {
		deleteDirectory(fromDirectory);
	}

	return true;
}

void deployImportDirectories() {
	ProcessMutex mutex = ProcessMutex("PANDAS_IMPORT_DEPLOY_MUTEX");
	const bool locked = mutex.lock();

	const struct import_data {
		std::string import_from;
		std::string import_to;
	} import_data[] = {
		{ "conf/import-tmpl", "conf/import" },
		{ "conf/msg_conf/import-tmpl", "conf/msg_conf/import" },
		{ "db/import-tmpl", "db/import" }
	};

	for (const auto& entry : import_data) {
		deployImportDirectory(entry.import_from, entry.import_to);
	}

	if (locked) {
		mutex.unlock();
	}
}

bool getExecuteFilepath(std::string& outFilepath) {
#ifdef _WIN32
	std::string buffer(MAX_PATH, '\0');
	DWORD length = GetModuleFileNameA(nullptr, buffer.data(), static_cast<DWORD>(buffer.size()));

	while (length == buffer.size() && GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
		buffer.resize(buffer.size() * 2, '\0');
		length = GetModuleFileNameA(nullptr, buffer.data(), static_cast<DWORD>(buffer.size()));
	}

	if (length == 0) {
		outFilepath.clear();
		return false;
	}

	buffer.resize(length);
	outFilepath = buffer;
	return true;
#else
	char buffer[PATH_MAX] = { 0 };
	ssize_t length = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);

	if (length == -1) {
		outFilepath.clear();
		return false;
	}

	buffer[length] = '\0';
	outFilepath = buffer;
	return true;
#endif // _WIN32
}

bool getExecuteFileDirectory(std::string& outFileDirectory) {
	std::string filePath;
	if (!getExecuteFilepath(filePath)) {
		outFileDirectory.clear();
		return false;
	}

	std::size_t pos = filePath.rfind(PATH_SEPARATOR);
	if (pos == std::string::npos) {
		outFileDirectory.clear();
		return false;
	}

	outFileDirectory = filePath.substr(0, pos);
	ensurePathEndwithSep(outFileDirectory, PATH_SEPARATOR);
	return true;
}

bool isDirectoryExists(const std::string& path) {
	try {
		std::filesystem::path dirpath(path);
		dirpath = dirpath.lexically_normal();
		return std::filesystem::is_directory(dirpath);
	}
	catch (const std::filesystem::filesystem_error& e) {
		ShowWarning("%s: %s\n", __func__, e.what());
		return false;
	}
}

bool makeDirectories(const std::string& dirpath) {
	try {
		std::filesystem::path path(dirpath);
		path = path.lexically_normal();
		if (isDirectoryExists(dirpath) || isFileExists(dirpath)) {
			return true;
		}
		return std::filesystem::create_directories(path);
	}
	catch (const std::filesystem::filesystem_error& e) {
		ShowWarning("%s: %s\n", __func__, e.what());
		return false;
	}
}

bool ensureDirectories(const std::string& filepath) {
	try {
		std::filesystem::path path(filepath);
		path = path.lexically_normal().parent_path();
		return makeDirectories(path.string());
	}
	catch (const std::filesystem::filesystem_error& e) {
		ShowWarning("%s: %s\n", __func__, e.what());
		return false;
	}
}

bool deleteDirectory(std::string path) {
	try {
		std::filesystem::path dirpath(path);
		dirpath = dirpath.lexically_normal();
		std::filesystem::remove_all(dirpath);
		return true;
	}
	catch (const std::filesystem::filesystem_error& e) {
		ShowWarning("%s: %s\n", __func__, e.what());
		return false;
	}
}

bool copyDirectory(const std::filesystem::path& from, const std::filesystem::path& to) {
	try {
		if (std::filesystem::exists(to)) {
			throw std::runtime_error("The path " + to.generic_string() + " is already exists.");
		}

		if (std::filesystem::is_directory(from)) {
			std::filesystem::create_directories(to);
			for (const auto& item : std::filesystem::directory_iterator(from)) {
				if (!copyDirectory(item.path(), to / item.path().filename())) {
					return false;
				}
			}
		}
		else if (std::filesystem::is_regular_file(from)) {
			std::filesystem::copy_file(from, to, std::filesystem::copy_options::overwrite_existing);
		}
		else {
			throw std::runtime_error("The path " + from.generic_string() + " is not found.");
		}
	}
	catch (const std::exception& e) {
		ShowWarning("%s: %s\n", __func__, e.what());
		return false;
	}

	return true;
}

bool isFileExists(const std::string& path) {
	try {
		std::filesystem::path filepath(path);
		filepath = filepath.lexically_normal();
		return std::filesystem::is_regular_file(filepath);
	}
	catch (const std::filesystem::filesystem_error& e) {
		ShowWarning("%s: %s\n", __func__, e.what());
		return false;
	}
}

bool copyFile(const std::string& from, const std::string& to) {
	try {
		std::filesystem::path frompath(from);
		frompath = frompath.lexically_normal();

		std::filesystem::path topath(to);
		topath = topath.lexically_normal();

		std::filesystem::copy_file(frompath, topath, std::filesystem::copy_options::overwrite_existing);
		return true;
	}
	catch (const std::filesystem::filesystem_error&) {
		return false;
	}
}

bool deleteFile(const std::string& path) {
	try {
		std::filesystem::path filepath(path);
		filepath = filepath.lexically_normal();
		return std::filesystem::remove(filepath);
	}
	catch (const std::filesystem::filesystem_error&) {
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

bool strEndWith(std::string fullstring, std::string ending) {
	if (fullstring.length() >= ending.length()) {
		return (0 == fullstring.compare(fullstring.length() - ending.length(), ending.length(), ending));
	}
	return false;
}

bool strEndWith(std::wstring fullstring, std::wstring ending) {
	if (fullstring.length() >= ending.length()) {
		return (0 == fullstring.compare(fullstring.length() - ending.length(), ending.length(), ending));
	}
	return false;
}

void standardizePathSep(std::string& path) {
	strReplace(path, "/", PATH_SEPARATOR);
	strReplace(path, "\\", PATH_SEPARATOR);
}

void standardizePathSep(std::wstring& path) {
	strReplace(path, L"/", WIDE_PATH_SEPARATOR);
	strReplace(path, L"\\", WIDE_PATH_SEPARATOR);
}

void ensurePathEndwithSep(std::string& path, const std::string& sep) {
	if (!(strEndWith(path, "\\") || strEndWith(path, "/"))) {
		path.append(sep);
	}
}

void ensurePathEndwithSep(std::wstring& path, const std::wstring& sep) {
	if (!(strEndWith(path, L"\\") || strEndWith(path, L"/"))) {
		path.append(sep);
	}
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

bool isGBKCharacter(unsigned char high, unsigned char low) {
	// 判断基于 GBK 编码的双字节字符规则
	// https://www.qqxiuzi.cn/zh/hanzi-gbk-bianma.php
	// 由于 GBK 兼容 GB2312, 是 GB2312 的超集, 所以这里不再单独对 GB2312 区间做判断
	// GBK 亦采用双字节表示, 总体编码范围为 0x8140-0xFEFE.
	// 高位字节在 0x81-0xFE 之间, 低位字节在 0x40-0xFE 之间, 剔除 xx7F 一条线
	if (low != 0 && low != 0x7f && low >= 0x40 && low <= 0xfe) {
		if (high != 0 && high >= 0x81 && high <= 0xFE) {
			return true;
		}
	}

	return false;
}

bool isBIG5Character(unsigned char high, unsigned char low) {
	// 判断基于 BIG5 编码的双字节字符规则
	// https://www.qqxiuzi.cn/zh/hanzi-big5-bianma.php
	// BIG5 使用两个字节表示一个字符, 高位字节 0x81-0xFE,
	// 低位字节 0x40-0x7E 或 0xA1-0xFE.
	if (low != 0 && ((low >= 0x40 && low <= 0x7e) || (low >= 0xa1 && low <= 0xfe))) {
		if (high != 0 && high >= 0x81 && high <= 0xFE) {
			return true;
		}
	}

	return false;
}

bool isDoubleByteCharacter(unsigned char high, unsigned char low) {
	return (isGBKCharacter(high, low) || isBIG5Character(high, low));
}

bool isEscapeSequence(const char* start_p) {
	char buf[8] = { 0 };
	size_t len = skip_escaped_c(start_p) - start_p;
	if (len != 2)
		return false;
	size_t n = sv_unescape_c(buf, start_p, len);
	return (n == 1);
}
