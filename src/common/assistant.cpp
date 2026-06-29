#include <string>

#include <fmt/core.h>

#include <config/pandas.hpp>

#include "showmsg.hpp"

#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

std::string formatVersion(std::string ver, bool bPrefix, bool bSuffix, int ver_type);
bool isCommercialVersion();

inline const char* getDefinedVersion() {
#ifdef Pandas_Commercial_Version
	return Pandas_Commercial_Version;
#else
	return Pandas_Version;
#endif // Pandas_Commercial_Version
}

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
			std::string szVersionFormat = (isCommercialVersion() ? "{:04}.{:02}.{:02}.{}" : "{}.{}.{}.{}");
			std::string sFileVersion = fmt::format(szVersionFormat,
				HIWORD(pFileInfo->dwFileVersionMS), LOWORD(pFileInfo->dwProductVersionMS),
				HIWORD(pFileInfo->dwProductVersionLS), LOWORD(pFileInfo->dwProductVersionLS)
			);
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
