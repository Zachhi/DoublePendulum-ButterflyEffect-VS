#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <math.h>
#include <assert.h>

namespace fb
{
	namespace utils
	{
		inline float distance(const sf::Vector2f& v1, const sf::Vector2f& v2)
		{
			return sqrtf(((v2.x - v1.x) * (v2.x - v1.x)) + ((v2.y - v1.y) * (v2.y - v1.y)));
		}

		inline float length(const sf::Vector2f& v)
		{
			return sqrtf(v.x * v.x + v.y * v.y);
		}

		inline sf::Vector2f normalize(const sf::Vector2f& v)
		{
			assert(v != sf::Vector2f(0.f, 0.f));
			return v / length(v);
		}

		inline void centerOrigin(sf::Shape& shape)
		{
			sf::FloatRect bounds = shape.getLocalBounds();
			shape.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
		}
	}
}