#include "pch.h"
#include "GameEngine.h"
// -----------------------------------------
#include "AssetManager.h"
#include "JsonUtility.h"
#include "screens\TitleScreen.h"
#include "AnimationManager.h"
// -----------------------------------------
namespace lpa
{
	GameEngine::GameEngine()
		: m_window{}
		, m_screenManager{ m_window }

	{
		m_window.create(sf::VideoMode(Constants::k_WindowWidth,
			Constants::k_WindowHeight), Constants::k_WindowTitle.data());
		
		loadAssetsFromFiles();
		
		m_screenManager.addScreen(std::make_unique<TitleScreen>(m_screenManager));
	}
	void GameEngine::loadAssetsFromFiles()
	{
		const auto& assetsFile = json::ParseJsonFile("assets/json/assets.json");
		for (const auto& assets : assetsFile)
		{
			if (!assets["textures"].empty())
			{
				for (const auto& texture : assets["textures"])
					AssetManager<sf::Texture>::Insert(texture["key"], texture["path"]);
			}

			if (!assets["sounds"].empty())
			{
				for (const auto& sound : assets["sounds"])
					AssetManager<sf::SoundBuffer>::Insert(sound["key"], sound["path"]);
			}

			if (!assets["musics"].empty())
			{
				// TODO: Music Player
			}

			if (!assets["fonts"].empty())
			{
				for (const auto& font : assets["fonts"])
					AssetManager<sf::Font>::Insert(font["key"], font["path"]);
			}
		}

		AssetManager<sf::SoundBuffer>::GetAssetByKey("wooden-click-sound");
		AssetManager<sf::Font>::GetAssetByKey("credits-screen-font");

		const auto& animationsFile = json::ParseJsonFile("assets/json/animations.json");
		for (const auto& animationData : animationsFile["animations"])
		{
			FrameAnimationData data{};
			auto frames = animationData["frames"].get<int>();

			const auto& key = static_cast<std::string>(animationData["key"]);
			AnimationManager::insert(key);

			const auto& textureID = static_cast<std::string>(animationData["textureID"]);
			auto& animation = AnimationManager::getAnimationByKey(key);
			animation.setSpriteSheet(AssetManager<sf::Texture>::GetAssetByKey(textureID));

			for (int frame = 0; frame < frames; frame++)
			{
				data.x		= frame * animationData["width"].get<int>();
				data.y		= animationData["originY"].get<int>();
				data.width	= animationData["width"].get<int>();
				data.height = animationData["height"].get<int>();

				animation.addFrame(sf::IntRect(data.x, data.y, data.width, data.height));
			}
		}
	}
	void GameEngine::run()
	{
		sf::Clock clock{};
		sf::Time  elapsedTime{ sf::Time::Zero };
		sf::Time  timePerFrame{ sf::seconds(k_TimePerFrame) };
		while (m_window.isOpen())
		{
			handleEvents();

			elapsedTime += clock.restart();
			while (elapsedTime > timePerFrame)
			{
				elapsedTime -= timePerFrame;
				update(timePerFrame);
			}

			draw();
		}
	}
	void GameEngine::handleEvents()
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window.close();

			m_screenManager.getScreen().handleEvent(event);
		}
	}
	void GameEngine::update(sf::Time elapsedTime)
	{
		m_screenManager.getScreen().update(elapsedTime);
	}
	void GameEngine::draw()
	{
		m_window.clear();
		m_screenManager.getScreen().draw(m_window, sf::RenderStates::Default);
		m_window.display();
	}
}
