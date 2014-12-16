#ifndef BZSF_TILESET_H
#define BZSF_TILESET_H

namespace bzsf {

	struct tsTile;
	
	class Tileset {
	public:
		typedef std::unique_ptr<Tileset> Ptr;

	private:
		typedef std::unique_ptr<tsTile> tPtr;

		std::vector<std::vector<tPtr>> tiles;

	public:
		Tileset(const sf::Texture& texture, sf::Vector2u frameSize);

		const sf::Texture* texture;
	
		tsTile* get(sf::Uint32 column, sf::Uint32 row);
	};


} //ENDOF NAMESPACE bzsf

#endif