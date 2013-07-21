#include <SFML_Snips.hpp>

namespace bzsf {
	
	tsTile::tsTile() : xOffset(0), yOffset(0), width(0), height(0), texture(0) {}
	tsTile::~tsTile() {}

	std::vector<std::vector<tsTile>> newTileset(sf::Texture * texture, int hSize, int vSize) {
		std::vector<std::vector<tsTile>> tileset;
		tileset.resize(texture->getSize().x/hSize);
		for(unsigned int i=0; i<tileset.size(); i++) {
			tileset[i].resize(texture->getSize().y/vSize);
		}

		for(unsigned int i=0; i < texture->getSize().x/hSize; i++) {
			for(unsigned int u=0; u < texture->getSize().y/vSize; u++) {
				tileset[i][u].xOffset = i*hSize;
				tileset[i][u].yOffset = u*vSize;
				tileset[i][u].width	= hSize;
				tileset[i][u].height = vSize;
				tileset[i][u].texture = texture;
			}
		}
		return tileset;
	}


}