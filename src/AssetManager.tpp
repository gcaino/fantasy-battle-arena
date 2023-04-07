#include "pch.h"
#include "AssetManager.h"

namespace lpa
{
	template<typename T>
	void AssetManager<T>::Insert(std::string_view key, const std::filesystem::path& path)
	{
		// Find Asset Key, if exist not insert again in the container
		auto found = m_assets.find(key.data());
		if (found != m_assets.end()) return;

		// Load Asset from File
		T tempAsset{};
		if (!tempAsset.loadFromFile(path.string()))
			throw std::runtime_error("Runtime Error, Failed to load: " + path.string() + '\n');

		// Insert Asset in Container
		auto [it, result] = m_assets.emplace(key, std::make_pair(path, std::move(tempAsset)));

		// TODO: FIX assert message
		std::string assertMsg{ std::string("Assert Error, Could not be possible Emplace Asset: ") + path.string() + '\n' };
		assert(result && assertMsg.c_str());
	}

	template<typename T>
	T& AssetManager<T>::GetAssetByKey(std::string_view key)
	{
		auto it = m_assets.find(key.data());

		std::string assertMsg{ std::string("Assert Error, Invalid Asset Key: ") + key.data() + '\n' };
		assert(it != m_assets.end() && assertMsg.c_str());

		return it->second.second;
	}

	template<typename T>
	std::string AssetManager<T>::GetAssetPathByKey(std::string_view key)
	{
		auto it = m_assets.find(key.data());

		std::string assertMsg{ std::string("Assert Error, Invalid Asset Key: ") + key.data() + '\n' };
		assert(it != m_assets.end() && assertMsg.c_str());

		return it->second.first.string();
	}
}