#include <SFML/Graphics.hpp>

namespace bzsf {

	class PElement {
		private:
			sf::Text elementText;
			sf::Text avgText;

			std::string postfix;

			sf::Time overflow;
			sf::Time updateInterval;

			std::vector<float> values;
			float average;

			sf::Clock clock;

		public:
			void update();

			PElement(sf::Font& font, 
					std::string elementText,
					std::string postfix,
					sf::Time updateInterval,
					sf::Uint32 textSize);

			void pushValue(float value);

			void setFont(const sf::Font& font);
			void setColor(const sf::Color& color);

			void draw(sf::RenderTarget& window, sf::Vector2f pos1, sf::Vector2f pos2, sf::RenderStates states = sf::RenderStates::Default);
	};


	class PerformanceDisplay : public sf::Drawable {
	private:
		mutable std::map<std::string, PElement> elements;
		
		sf::Font* font;
		sf::Uint32 textSize;
		sf::Uint32 offset;
		sf::Color color;

		sf::Vector2f pos;

	private:
		void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

	public:
		PerformanceDisplay(sf::Color c = sf::Color(),
			sf::Vector2f pos = sf::Vector2f(100 , 10),
			sf::Uint32 textSize = 12u, 
			sf::Uint32 offset = 2u,
			sf::Font* font = nullptr);

		void registerElement(std::string ID, 
			std::string elementText, 
			sf::Time updateInterval = sf::seconds(0.1f), 
			std::string postfix = "");
		void pushValue(std::string ID, float value);


		void setFont(sf::Font& font);
		void setColor(const sf::Color& c);
		void setPosition(sf::Vector2f pos);	
	};
}
