namespace bzsf {
	class Drawable;

	class Animation {
		friend Drawable;

	private:
		sf::Vector2u frameSize;
		
		sf::Uint32 frameIndex;
		sf::Uint32 numFrames;

		sf::Time timePerFrame; //Speed in milliseconds between each change of frame
		sf::Time overflow;

		bool repeat;

		sf::Clock timer;

		sf::Texture texture;

	public:
		sf::Vector2u GetFrameSize();
		sf::Uint32 GetIndex();
		sf::Uint32 GetFrameCount();
		sf::Time GetTimePerFrame();
		bool IsRepeating();
		sf::Texture& GetTexture();
		

		void SetTimePerFrame(sf::Time s);
		
		
		/////////////////////////////////////////////////
		/// \brief Create a new Animation from a texture
		///
		/// After you have created the animation, attach it to to a drawable:
		/// drawable.SetAnimation(&animation);
		/// Multiple drawables can use the same animation, but
		/// they will always be on the same frame and can't have different speeds.
		///
		/// \param fSize The size of each frame in the animation
		/// \param t The texture the animation should use
		/// \param TimePerFrame The time between each framechange
		/// \param Repeat Default: true. Repeat animation after it has ended?
		///
		/// \see Drawable::SetAnimation
		///
		//////////////////////////////////////////////////
		Animation(sf::Vector2u fSize, const sf::Texture& t, sf::Time TimePerFrame, bool Repeat = true);


		/////////////////////////////////////////////////
		/// \brief Create a new Animation from a texture
		///
		/// After you have created the animation, attach it to to a drawable:
		/// drawable.SetAnimation(&animation);
		/// Multiple drawables can use the same animation, but
		/// they will always be on the same frame and can't have different speeds.
		///
		/// \param columns Columns in the animation strip
		/// \param rows Rows in the animation strip
		/// \param t The texture the animation should use
		/// \param TimePerFrame The time between each framechange
		/// \param Repeat Default: true. Repeat animation after it has ended?
		///
		/// \see Drawable::SetAnimation
		///
		//////////////////////////////////////////////////
		Animation(sf::Uint16 columns, sf::Uint16 rows, const sf::Texture& t, sf::Time TimePerFrame, bool Repeat = true);

		Animation();

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
		void SetFrame(sf::Uint32 index, bool speedToZero = false);

		
		bool Update();

		

	private:
		sf::IntRect GetFrameRect();

	};
}