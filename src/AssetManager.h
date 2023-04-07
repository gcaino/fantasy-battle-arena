#pragma once
#include "pch.h"
// --------------------------------------------------------------------------------
namespace lpa
{
	template <typename T>
	class AssetManager final
	{
	public:
		AssetManager() = delete;

		static void Insert(std::string_view key, const std::filesystem::path& path);

		static T& GetAssetByKey(std::string_view key);
		static std::string  GetAssetPathByKey(std::string_view key);

	private:
		inline static std::unordered_map<std::string, std::pair<std::filesystem::path, T>> m_assets;
	};
}
// -------------------------------------------------------------------------------
#include "AssetManager.tpp"

