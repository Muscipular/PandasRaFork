#include "map_artisan.hpp"

#include <algorithm>
#include <exception>
#include <regex>

#include <common/assistant.hpp>
#include <common/showmsg.hpp>
#include <common/utilities.hpp>

using namespace rathena;

// Method:      hasCatchPet
// Description: 判断脚本是否拥有宠物捕捉指令, 并提取它支持捕捉的宠物编号
// Parameter:   const std::string& script
// Parameter:   std::vector<uint32> & pet_mobid
// Returns:     bool
// Author:      Sola丶小克(CairoLee)  2019/10/13 15:59
bool hasCatchPet(const std::string& script, std::vector<uint32>& pet_mobid) {
	pet_mobid.clear();
	static const std::vector<std::string> valid_cmds = { "multicatchpet", "catchpet", "mpet", "pet" };
	static const std::string patterns = R"(.*?((multicatchpet|catchpet|mpet|pet)(\s{1,}|\()(\(|)(.*?)(|\))(\s*|);))";

	if (!strContain(valid_cmds, script))
		return false;

	try {
		std::regex re(patterns, std::regex::icase);
		std::smatch match_result;
		if (!std::regex_search(script, match_result, re))
			return false;
		if (match_result.size() != 8)
			return false;

		std::string cmd = util::tolower_copy(match_result[2].str());
		std::string params = util::trim_copy(match_result[5].str());
		if (!params.length())
			return false;

		std::vector<std::string> explode = strExplode(params, ',');
		if (cmd == "multicatchpet" || cmd == "mpet") {
			for (const std::string& it : explode) {
				pet_mobid.push_back(std::stoi(util::trim_copy(it)));
			}
		}
		else {
			for (const std::string& it : explode) {
				pet_mobid.push_back(std::stoi(util::trim_copy(it)));
				break;
			}
		}

		std::sort(pet_mobid.begin(), pet_mobid.end());
		pet_mobid.erase(std::unique(pet_mobid.begin(), pet_mobid.end()), pet_mobid.end());
	}
	catch (const std::regex_error& e) {
		ShowWarning("%s throw regex_error : %s\n", __func__, e.what());
		return false;
	}
	catch (const std::exception& e) {
		ShowWarning("%s throw exception : %s\n", __func__, e.what());
		pet_mobid.clear();
		return false;
	}

	return true;
}

// Method:      hasCallfunc
// Description: 判断一个脚本是否调用了 callfunc 指令
// Parameter:   const std::string& script
// Returns:     bool
// Author:      Sola丶小克(CairoLee)  2019/10/13 15:59
bool hasCallfunc(const std::string& script) {
	if (!strContain("callfunc", script))
		return false;

	return isRegexMatched(script, R"(.*?callfunc(\s.*|\(\s*)\"(.*?)\".*?)");
}
