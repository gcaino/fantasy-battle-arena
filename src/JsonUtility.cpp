#include "pch.h"
#include "JsonUtility.h"
// ----------------------------------------------------------
namespace lpa::json
{
	using json = nlohmann::json;

	json ParseJsonFile(const std::filesystem::path& filePath)
	{
		std::ifstream file(filePath);
		json data = nlohmann::json::parse(file);
		return data;
	}
}