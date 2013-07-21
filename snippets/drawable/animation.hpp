namespace bzsf {
	class Animation {
	protected:
		int frameWidth;
		
		int frameIndex;
		int numFrames;

		sf::Uint32 speed; //Speed in milliseconds between each change of frame
		sf::Uint32 overflow;

		bool repeat;

		sf::Clock timer;

		sf::Texture texture;

	public:
		int GetWidth();
		int GetHeight();
		int GetIndex();
		int GetFrames();
		sf::Uint32 GetSpeed();
		sf::Clock& GetTimer();
		bool IsRepeating();
		sf::Texture& GetTexture();
		

		void SetSpeed(sf::Uint32 s);
		
		
		///////////////////////////////////////////////////
		/// \brief Sets the frame index of the Animation
		///
		/// If you would want to manually set the frame of the animation,
		/// 	you can do that with this function.
		/// Simply call it with the index of the frame and the
		/// 	drawable affected.
		/// drawable.GetAnimation()->SetFrame('index', drawable)
		///
		/// \param index The index you want to change to
		/// \param entity The drawable you want the change to affect
		/// \param speedToZero Default: false. Reset the speed to 0 after the change of frame?
		///////////////////////////////////////////////////
		void SetFrame(int index, bool speedToZero = false);

		
		bool Update();
		
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
		/// \see Drawable::SetAnimation
		///
		//////////////////////////////////////////////////
		Animation(int fWidth, const sf::Texture& t, int Speed, bool Repeat = true);

		Animation();
	};
}