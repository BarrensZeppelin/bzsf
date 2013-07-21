#include <SFML_Snips.hpp>

namespace bzsf {
	int Animation::GetWidth()				{return frameWidth;				}
	int Animation::GetHeight()				{return texture.getSize().y;	}
	int Animation::GetIndex()				{return frameIndex;				}
	int Animation::GetFrames()				{return numFrames;				}
	sf::Uint32 Animation::GetSpeed()		{return speed;					}
	sf::Clock& Animation::GetTimer()		{return timer;					}
	bool Animation::IsRepeating()			{return repeat;					}
	sf::Texture& Animation::GetTexture()	{return texture;				}

	void Animation::SetSpeed(sf::Uint32 s)	{speed = s;}


	void Animation::SetFrame(int index, bool speedToZero) {
		if(index < numFrames) {
			frameIndex = index;
		} else { std::cerr << "Tried to assign invalid frame " << index << "/" << numFrames-1 << " to an animation." << std::endl; }
		
		if(speedToZero) {speed = 0;}
	}


	bool Animation::Update() {
		if(speed == 0) {timer.restart(); return true;}
		else if((overflow + timer.getElapsedTime().asMilliseconds()) >= speed) {
			
			overflow = (overflow + timer.restart().asMilliseconds() - speed)%speed;

			if(frameIndex < numFrames-1) {
				frameIndex++;
			} else if(repeat) {
				frameIndex = 0;
			}

			return true;
		}

		return false;
	}


	Animation::Animation(int fWidth, const sf::Texture& t, int Speed, bool Repeat) : repeat(Repeat), texture(t), speed(Speed), frameWidth(fWidth), frameIndex(0), overflow(0) {
		if(t.getSize().x%fWidth!=0) { std::cerr << "Animation creation error: sizes are incompatible" << std::endl;}
		numFrames = t.getSize().x / fWidth;
	}


	Animation::Animation() {}
}