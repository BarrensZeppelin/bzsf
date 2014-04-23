

namespace bzsf {

	class PElement {
	private:
		sf::Text elementText;
		sf::Text avgText;

		sf::Time overflow;
		sf::Time updateInterval;

		std::vector<float> values;
		float average;

		sf::Clock clock;

		void Update();

	public:
		PElement(sf::Font& font, std::string elementText, sf::Time updateInterval, sf::Uint32 textSize);
	
		void PushValue(float value);

		void SetFont(sf::Font& font);

		void Draw(sf::RenderTarget& window, sf::Vector2f pos1, sf::Vector2f pos2, sf::RenderStates states = sf::RenderStates::Default);
	};

	class PerformanceDisplay {
	private:
		std::map<std::string, PElement> elements;
		sf::Font* font;
		sf::Uint32 textSize;
		sf::Uint32 offset;

		sf::Vector2f pos;

	public:
		PerformanceDisplay(sf::Font* Font = nullptr, 
						   sf::Vector2f pos = sf::Vector2f(10, 10),
						   sf::Uint32 textSize = 12u, 
						   sf::Uint32 offset = 2u);

		void RegisterElement(std::string ID, std::string elementText, sf::Time updateInterval = sf::seconds(0.1f));
		void PushValue(std::string ID, float value);


		void SetFont(sf::Font& font);


		void Draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default);
	};

}