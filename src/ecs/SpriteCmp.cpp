#include "pch.h"
#include "SpriteCmp.h"
// --------------------------------------------------------------------------------
namespace lpa
{
	void SpriteCmp::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_sprite);
	}
}