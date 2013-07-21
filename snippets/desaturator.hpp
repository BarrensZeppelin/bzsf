namespace bzsf {

	class Desaturator {
	protected:
		sf::Uint8 * targetPixels;
		sf::Uint8 * startPixels;
		sf::Uint8 * pixels;
		sf::Uint16 duration;

		bool done;

		sf::Vector2u area;
		sf::Clock clock;

	public:
		//Return array of pixels
		sf::Uint8 * GetPixels();

		Desaturator(const sf::Image& img, sf::Uint16 _duration);

		~Desaturator();

	};

} //ENDOF NAMESPACE bzsf