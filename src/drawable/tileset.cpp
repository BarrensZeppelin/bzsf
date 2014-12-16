#include <SFML_Snips.hpp>
#include <bzsf\snippets\drawable\tsTile.hpp>

namespace bzsf {
	Tileset::Tileset(const sf::Texture& texture, sf::Vector2u frameSize) 
	: tiles(texture.getSize().x / frameSize.x)
	, texture(&texture) {
		
		for(sf::Uint32 i = 0; i < tiles.size(); i++)
			tiles[i].resize(texture.getSize().y / frameSize.y);

		for(sf::Uint32 i = 0; i < texture.getSize().x / frameSize.x; i++) {
			for(sf::Uint32 u = 0; u < texture.getSize().y / frameSize.y; u++) {
				tiles[i][u].reset(new tsTile());
				tiles[i][u]->xOffset = i*frameSize.x;
				tiles[i][u]->yOffset = u*frameSize.y;
				tiles[i][u]->width	= frameSize.x;
				tiles[i][u]->height = frameSize.y;
				tiles[i][u]->texture = &texture;
			}
		}
	}


	tsTile* Tileset::get(sf::Uint32 column, sf::Uint32 row) {
		return tiles[column][row].get();
	}


	Tileset::~Tileset() {
		tiles.clear();
	}
}