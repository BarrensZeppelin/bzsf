#include <SFML_Snips.hpp>

namespace bzsf {
	Animation::Animation(sf::Vector2u fSize, const sf::Texture& t, sf::Time timePerFrame, bool repeat) 
		: repeat(repeat)
		, texture(&t)
		, timePerFrame(timePerFrame)
		, frameSize(fSize)
		, frameIndex(0)
		, overflow(sf::Time::Zero) {
		
		assert(("Animation creation error: sizes are incompatible", t.getSize().x % fSize.x == 0 && t.getSize().y % fSize.y == 0));
		numFrames = t.getSize().x / fSize.x; // Columns
		numFrames *= t.getSize().y / fSize.y; // * rows
	}

	Animation::Animation(sf::Uint16 columns, sf::Uint16 rows, const sf::Texture& t, sf::Time timePerFrame, bool repeat)
		: repeat(repeat)
		, texture(&t)
		, timePerFrame(timePerFrame)
		, numFrames(columns*rows)
		, frameIndex(0)
		, overflow(sf::Time::Zero) {
		
		frameSize = sf::Vector2u(t.getSize().x / columns, t.getSize().y / rows);
	}
	
	Animation::Animation() {}


	bool Animation::update(sf::Time dt) {
		bool updated = false;
		
		if(timePerFrame != sf::Time::Zero) {
			overflow += dt;
			while(overflow >= timePerFrame) {
				overflow -= timePerFrame;
				if(frameIndex < numFrames - 1) {
					frameIndex++;
				} else if(repeat) {
					frameIndex = 0;
				}

				updated = true;
			}
		}
		
		return updated;
	}


	sf::Vector2u Animation::getFrameSize() const	{ return frameSize; }
	sf::Uint32 Animation::getIndex() const		{ return frameIndex; }
	sf::Uint32 Animation::getFrameCount() const	{ return numFrames; }
	sf::Time Animation::getTimePerFrame() const	{ return timePerFrame; }
	bool Animation::isRepeating() const			{ return repeat; }
	const sf::Texture* Animation::getTexture() const { return texture; }

	const sf::IntRect Animation::getFrameRect() const {
		sf::Uint32 column = frameIndex % (texture->getSize().x / frameSize.x);
		sf::Uint32 row = sf::Uint32(floor(float(frameIndex) / (texture->getSize().x / frameSize.x)));

		sf::IntRect pRect(
			column * frameSize.x,
			row * frameSize.y,
			frameSize.x,
			frameSize.y);
		return pRect;
	}

	void Animation::setRepeating(bool repeat) { this->repeat = repeat; }
	void Animation::setTimePerFrame(sf::Time t)	{ timePerFrame = t; }


	void Animation::setFrame(sf::Uint32 index, bool resetOverflow) {
		assert(index < numFrames);

		frameIndex = index;
		if(resetOverflow)
			overflow = sf::Time::Zero;
	}
}