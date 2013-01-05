class drawable;

namespace sf {

	class Animation {
	protected:
		int frameWidth;
		
		int frameIndex;
		int numFrames;

		unsigned int speed; //Speed in milliseconds between each change of frame

		bool repeat;

		sf::Clock timer;

		sf::Texture * texture;

	public:
		int GetWidth()				{return frameWidth;				}
		int GetHeight()				{return texture->getSize().y;	}
		int GetIndex()				{return frameIndex;				}
		int GetFrames()				{return numFrames;				}
		unsigned int GetSpeed()		{return speed;					}
		sf::Clock * GetTimer()		{return &timer;					}
		bool IsRepeating()			{return repeat;					}
		sf::Texture * GetTexture()	{return texture;				}
		

		void SetSpeed(unsigned int s) {speed = s;}
		
		
		///////////////////////////////////////////////////
		/// \brief Sets the frame index of the Animation
		///
		/// If you would want to manually set the frame of the animation,
		/// you can do that with this function.
		/// Simply call it with the index of the frame and the
		/// drawable affected.
		/// drawable.GetAnimation()->SetFrame('index', drawable)
		///
		/// \param index The index you want to change to
		/// \param entity The drawable you want the change to affect
		/// \param speedToZero Default: false. Reset the speed to 0 after the change of frame?
		///////////////////////////////////////////////////
		void SetFrame(int index, drawable& entity, bool speedToZero);
		
		
		void UpIndex()	{
			if(frameIndex < numFrames) {
				frameIndex++;
			} else if(repeat) {
				frameIndex = 0;
			}
		}
		
		/////////////////////////////////////////////////
		/// \brief Create a new Animation from a texture
		///
		/// After you have created the animation, attach it to to a drawable:
		/// drawable.SetAnimation(&animation);
		/// Multiple drawables can use the same animation, but
		/// they will always be on the same frame and can't have different speeds.
		///
		/// \param fWidth The width of each frame in the animation
		/// \param t The texture the animation should use
		/// \param Speed The time in milliseconds between each frame
		/// \param Repeat Default: true. Repeat animation after it has ended?
		///
		/// \see drawable::SetAnimation
		//////////////////////////////////////////////////
		Animation(int fWidth, sf::Texture& t, int Speed, bool Repeat = true) : repeat(Repeat), texture(&t), speed(Speed), frameWidth(fWidth), frameIndex(0) {
			if(t.getSize().x%fWidth!=0) { std::cerr << "Animation creation error: sizes are incompatible" << std::endl;}
			numFrames = t.getSize().x / fWidth;
		}
	};
}