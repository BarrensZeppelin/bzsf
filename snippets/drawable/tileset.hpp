#ifndef BZSF_TILESET_H
#define BZSF_TILESET_H

#include <SFML/Graphics.hpp>

namespace bzsf {
	
	class tsTile;

	class Tileset {
	public:
		typedef std::unique_ptr<Tileset> Ptr;

		const sf::Texture* texture;

	private:
		typedef std::unique_ptr<tsTile> tPtr;

		std::vector<std::vector<tPtr>> tiles;

		sf::Vector2u size;

	public:
		Tileset(const sf::Texture& texture, sf::Vector2u frameSize);
	
		tsTile* get(sf::Uint32 column, sf::Uint32 row);

		const sf::Vector2u getSize() const;

		~Tileset();
	};


} //ENDOF NAMESPACE bzsf

#endif
