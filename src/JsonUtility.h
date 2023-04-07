#pragma once
#include "nlohmann/json.hpp"
// ----------------------------------------------------------
namespace lpa::json
{
	using json = nlohmann::json;

	json ParseJsonFile(const std::filesystem::path& filePath);
}