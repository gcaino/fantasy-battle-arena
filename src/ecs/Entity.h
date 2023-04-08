#pragma once
// ---------------------------------------------------------------------------
#include "pch.h"
#include "ecs\Component.h"
// ---------------------------------------------------------------------------
namespace lpa
{
	class Entity
	{
	public:
		using Components = std::vector<std::unique_ptr<Component>>;

		Entity();

		constexpr void activate()		noexcept { m_active = true; }
		constexpr void deactivate()		noexcept { m_active = false; }
		constexpr bool isActive() const	noexcept { return m_active; }

		// Use case: addComponent<SpriteCmp>();
		template<typename Cmp>
		Cmp& addComponent()
		{
			auto tmpCmp = std::make_unique<Cmp>();

			auto cmpType = Component::getComponentType<Cmp>();
			if (cmpType == Component::Type::None)
			{
				std::string errMsg = "Component Type \"" + std::string(typeid(Cmp).name()) + "\" not exist.";
				throw std::invalid_argument(errMsg);
			}
			tmpCmp->type = cmpType;

			auto it = m_components.emplace(m_components.end(), std::move(tmpCmp));
			return static_cast<Cmp&>(*it->get());
		}

		// Use case: getComponent<SpriteCmp>();
		template<typename Cmp>
		const Cmp& getComponent() const
		{
			auto cmpType = Component::getComponentType<Cmp>();
			if (cmpType == Component::Type::None)
			{
				std::string errMsg = "Component Type \"" + std::string(typeid(Cmp).name()) + "\" not exist.";
				throw std::invalid_argument(errMsg);
			}

			auto it = std::ranges::find_if(m_components, [=](const auto& cmp) { return cmp->type == cmpType; });
			if (it != m_components.end())
			{
				return static_cast<Cmp&>(*it->get());
			}

			std::string errMsg = "Component \"" + std::string(typeid(Cmp).name()) + "\" is not added.";
			throw std::invalid_argument(errMsg);
		}

		template<typename Cmp>
		Cmp& getComponent()
		{
			return const_cast<Cmp&>(std::as_const(*this).getComponent<Cmp>());
		}

	private:
		Components m_components;
		bool m_active;
	};
}
