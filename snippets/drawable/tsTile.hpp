#ifndef BZSF_DRAWABLE_TSTILE
#define BZSF_DRAWABLE_TSTILE

#include <SFML/Graphics.hpp>

namespace bzsf {
	struct tsTile {
	public:
		int xOffset, yOffset, width, height;
		const sf::Texture* texture;
	};
}

#endif
