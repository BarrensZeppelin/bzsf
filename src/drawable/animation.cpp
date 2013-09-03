#include <SFML_Snips.hpp>

namespace bzsf {
	sf::Vector2u Animation::GetFrameSize()	{return frameSize;				}
	sf::Uint32 Animation::GetIndex()		{return frameIndex;				}
	sf::Uint32 Animation::GetFrameCount()	{return numFrames;				}
	sf::Time Animation::GetTimePerFrame()	{return timePerFrame;			}
	bool Animation::IsRepeating()			{return repeat;					}
	sf::Texture& Animation::GetTexture()	{return texture;				}

	void Animation::SetTimePerFrame(sf::Time t)	{timePerFrame = t;}



	Animation::Animation(sf::Vector2u fSize, const sf::Texture& t, sf::Time TimePerFrame, bool Repeat) : repeat(Repeat), texture(t), timePerFrame(TimePerFrame), frameSize(fSize), frameIndex(0), overflow(sf::Time::Zero) {
		if(t.getSize().x%fSize.x!=0 && t.getSize().y%fSize.y!=0) { std::cerr << "Animation creation error: sizes are incompatible" << std::endl;}
		numFrames = t.getSize().x / fSize.x; // Columns
		numFrames *= t.getSize().y / fSize.y; // * rows
	}


	Animation::Animation(sf::Uint16 columns, sf::Uint16 rows, const sf::Texture& t, sf::Time TimePerFrame, bool Repeat) : repeat(Repeat), texture(t), timePerFrame(TimePerFrame), numFrames(columns*rows), frameIndex(0), overflow(sf::Time::Zero) {
		frameSize = sf::Vector2u(t.getSize().x / columns, t.getSize().y / rows);	
	}


	Animation::Animation() {}



	void Animation::SetFrame(sf::Uint32 index, bool speedToZero) {
		if(index < numFrames) {
			frameIndex = index;
		} else { std::cerr << "Tried to assign invalid frame " << index << "/" << numFrames-1 << " to an animation." << std::endl; }
		
		if(speedToZero) {timePerFrame = sf::Time::Zero;}
	}


	bool Animation::Update() {
		if(timePerFrame == sf::Time::Zero) {timer.restart(); return true;}
		else {
			bool updated = false;
			overflow += timer.restart();
			while(overflow > timePerFrame) {
				overflow -= timePerFrame;
				if(frameIndex < numFrames-1) {
					frameIndex++;
				} else if(repeat) {
					frameIndex = 0;
				}

				updated = true;
			}

			return updated;
		}
	}


	sf::IntRect Animation::GetFrameRect() {
		sf::Uint32 column = frameIndex%(texture.getSize().x / frameSize.x);
		sf::Uint32 row = sf::Uint32(floor(float(frameIndex)/(texture.getSize().x / frameSize.x)));
	
		sf::IntRect pRect(
			column*frameSize.x,
			row*frameSize.y,
			frameSize.x,
			frameSize.y);
		return pRect;
	}
}