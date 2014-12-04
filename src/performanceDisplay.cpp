#include <SFML_Snips.hpp>

namespace bzsf {

	void PElement::Update() {
		overflow += clock.restart();

		if(overflow >= updateInterval && values.size() > 0) {
			average = 0.f;
			for(float& val : values) {
				average += val;
			}
			average /= values.size();

			std::stringstream ss; ss << average << postfix;
			avgText.setString(ss.str());

			values.clear();
		}

		while(overflow >= updateInterval) overflow -= updateInterval;
	}


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


	void PElement::PushValue(float value) {
		values.push_back(value);
	}


	void PElement::SetFont(sf::Font& font) {
		elementText.setFont(font);
		avgText.setFont(font);

		auto lbounds = this->elementText.getLocalBounds();
		this->elementText.setOrigin(sf::Vector2f(floor(lbounds.width), floor(lbounds.height / 2.f)));

		auto lbounds2 = this->avgText.getLocalBounds();
		this->avgText.setOrigin(sf::Vector2f(0.f, floor(lbounds2.height / 2.f)));
	}

	void PElement::SetColor(sf::Color c) {
		elementText.setColor(c);
		avgText.setColor(c);
	}


	void PElement::Draw(sf::RenderTarget& window, sf::Vector2f pos1, sf::Vector2f pos2, sf::RenderStates states) {
		Update();

		elementText.setPosition(pos1);
		avgText.setPosition(pos2);

		window.draw(elementText, states);
		window.draw(avgText, states);
	}




	PerformanceDisplay::PerformanceDisplay(sf::Font* Font, sf::Color c, sf::Vector2f pos, sf::Uint32 textSize, sf::Uint32 offset)
		: font(Font), color(c), pos(pos), textSize(textSize), offset(offset) {}


	void PerformanceDisplay::RegisterElement(std::string ID, std::string elementText, sf::Time updateInterval, std::string postfix) {
		assert(font != nullptr);

		auto iter = elements.insert(std::make_pair(ID, PElement(*font, elementText, postfix, updateInterval, textSize)));
		assert(iter.second);

		iter.first->second.SetColor(color);
	}

	void PerformanceDisplay::PushValue(std::string ID, float value) {
		assert(font != nullptr);

		auto iter = elements.find(ID);
		assert(iter != elements.end());

		iter->second.PushValue(value);
	}



	void PerformanceDisplay::SetFont(sf::Font& font) {
		this->font = &font;

		for(auto& el : elements) {
			el.second.SetFont(font);
		}

	}

	void PerformanceDisplay::SetColor(sf::Color c) {
		color = c;

		for(auto& el : elements)
			el.second.SetColor(c);
	}



	void PerformanceDisplay::Draw(sf::RenderTarget& window, sf::RenderStates states) {

		sf::Uint32 count = 0;
		for(auto iter = elements.begin(); iter != elements.end(); iter++) {
			PElement& e = iter->second;

			sf::Vector2f pos1 = sf::Vector2f(floor(pos.x), floor((textSize + offset) * count + pos.y));
			sf::Vector2f pos2 = sf::Vector2f(floor(pos.x + textSize), floor((textSize + offset) * count + pos.y));

			e.Draw(window, pos1, pos2, states);
			count++;
		}

	}
}