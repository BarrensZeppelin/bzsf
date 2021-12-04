#include <SFML_Snips.hpp>

namespace bzsf {
	PElement::PElement(sf::Font& font, std::string elementText, std::string postfix, sf::Time updateInterval, sf::Uint32 textSize)
		: elementText(elementText, font, textSize)
		, postfix(postfix)
		, avgText(std::string("0") + postfix, font, textSize)
		, overflow(sf::Time::Zero)
		, updateInterval(updateInterval)
		, average(0.f) {

		auto lbounds = this->elementText.getLocalBounds();
		this->elementText.setOrigin(sf::Vector2f(floor(lbounds.width), floor(lbounds.height / 2.f)));

		auto lbounds2 = this->avgText.getLocalBounds();
		this->avgText.setOrigin(sf::Vector2f(0.f, floor(lbounds2.height / 2.f)));
	}
	

	void PElement::update() {
		overflow += clock.restart();

		if(overflow >= updateInterval && values.size() > 0) {
			average = 0.f;
			for(float& val : values)
				average += val;
			average /= values.size();

			std::stringstream ss; ss << average << postfix;
			avgText.setString(ss.str());

			values.clear();
		}

		while(overflow >= updateInterval) overflow -= updateInterval;
	}


	void PElement::pushValue(float value) {
		values.push_back(value);
	}


	void PElement::setFont(const sf::Font& font) {
		elementText.setFont(font);
		avgText.setFont(font);

		auto lbounds = this->elementText.getLocalBounds();
		this->elementText.setOrigin(sf::Vector2f(floor(lbounds.width), floor(lbounds.height / 2.f)));

		auto lbounds2 = this->avgText.getLocalBounds();
		this->avgText.setOrigin(sf::Vector2f(0.f, floor(lbounds2.height / 2.f)));
	}

	void PElement::setColor(const sf::Color& c) {
		elementText.setFillColor(c);
		avgText.setFillColor(c);
	}


	void PElement::draw(sf::RenderTarget& window, sf::Vector2f pos1, sf::Vector2f pos2, sf::RenderStates states) {
		update();

		elementText.setPosition(pos1);
		avgText.setPosition(pos2);

		window.draw(elementText, states);
		window.draw(avgText, states);
	}




	PerformanceDisplay::PerformanceDisplay(sf::Color c, sf::Vector2f pos, sf::Uint32 textSize, sf::Uint32 offset, sf::Font* Font)
		: font(Font), color(c), pos(pos), textSize(textSize), offset(offset) {}

	void PerformanceDisplay::draw(sf::RenderTarget& window, sf::RenderStates states) const {
		assert(("PerformanceDisplay: No font given!", font != nullptr));
		
		sf::Uint32 count = 0;
		for(auto& p : elements) {
			PElement& e = p.second;

			sf::Vector2f pos1 = sf::Vector2f(floor(pos.x), floor((textSize + offset) * count + pos.y));
			sf::Vector2f pos2 = sf::Vector2f(floor(pos.x + textSize), floor((textSize + offset) * count + pos.y));

			e.draw(window, pos1, pos2, states);
			count++;
		}
	}


	void PerformanceDisplay::registerElement(std::string ID, std::string elementText, sf::Time updateInterval, std::string postfix) {
		auto iter = elements.insert(std::make_pair(ID, PElement(*font, elementText, postfix, updateInterval, textSize)));
		assert(iter.second);

		iter.first->second.setColor(color);
	}

	void PerformanceDisplay::pushValue(std::string ID, float value) {
		auto iter = elements.find(ID);
		if(iter == elements.end()) {
			registerElement(ID, ID); // Create a new PElement with the ID
			iter = elements.find(ID);
		}

		iter->second.pushValue(value);
	}



	void PerformanceDisplay::setFont(sf::Font& font) {
		this->font = &font;

		for(auto& el : elements)
			el.second.setFont(font);
	}

	void PerformanceDisplay::setColor(const sf::Color& c) {
		color = c;

		for(auto& el : elements)
			el.second.setColor(c);
	}

	void PerformanceDisplay::setPosition(sf::Vector2f pos) {
		this->pos = pos;
	}
}
