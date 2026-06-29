#pragma once

#include <string>
#include <vector>

#include <common/cbasetypes.hpp>
#include <config/pandas.hpp>

bool hasCatchPet(const std::string& script, std::vector<uint32>& pet_mobid);
bool hasCallfunc(const std::string& script);
