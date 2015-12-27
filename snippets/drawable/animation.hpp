namespace bzsf {
	class Drawable;

	class Animation {
	public:
		typedef std::unique_ptr<Animation> Ptr;

	private:
		sf::Vector2u frameSize;
		
		sf::Uint32 frameIndex;
		sf::Uint32 numFrames;

		sf::Time timePerFrame; //Speed in milliseconds between each change of frame
		sf::Time overflow;

		bool repeat;

		const sf::Texture* texture;
	
	protected:
		bool update(sf::Time dt);

	public:
		sf::Vector2u getFrameSize() const;
		sf::Uint32 getIndex() const;
		sf::Uint32 getFrameCount() const;
		sf::Time getTimePerFrame() const;
		bool isRepeating() const;
		const sf::Texture* getTexture() const;

		const sf::IntRect getFrameRect() const;
		

		void setRepeating(bool repeat);
		void setTimePerFrame(sf::Time s);

		///////////////////////////////////////////////////
		/// \brief sets the frame index of the Animation
		///
		/// If you would want to manually set the frame of the animation,
		/// 	you can do that with this function.
		/// Simply call it with the index of the frame and the
		/// 	drawable affected.
		/// drawable.getAnimation()->setFrame('index', drawable)
		///
		/// \param index The index you want to change to
		/// \param entity The drawable you want the change to affect
		/// \param resetOverflow set the frame time overflow to zero when changing
		///////////////////////////////////////////////////
		void setFrame(sf::Uint32 index, bool resetOverflow = true);


		/////////////////////////////////////////////////
		/// \brief Create a new Animation from a texture
		///
		/// After you have created the animation, attach it to to a drawable:
		///		drawable.setAnimation(&animation);
		/// Multiple drawables can use the same animation, but
		///		they will always be on the same frame and can't have different speeds.
		///
		/// \param fSize The size of each frame in the animation
		/// \param t The texture the animation should use
		/// \param TimePerFrame The time between each framechange
		/// \param Repeat Default: true. Repeat animation after it has ended?
		///
		/// \see Drawable::setAnimation
		//////////////////////////////////////////////////
		Animation(sf::Vector2u fSize, const sf::Texture& t, sf::Time timePerFrame, bool repeat = true);


		/////////////////////////////////////////////////
		/// \brief Create a new Animation from a texture
		///
		/// After you have created the animation, attach it to to a drawable:
		///		drawable.setAnimation(&animation);
		/// Multiple drawables can use the same animation, but
		///		they will always be on the same frame and can't have different speeds.
		///
		/// \param columns Columns in the animation strip
		/// \param rows Rows in the animation strip
		/// \param t The texture the animation should use
		/// \param TimePerFrame The time between each framechange
		/// \param Repeat Default: true. Repeat animation after it has ended?
		///
		/// \see Drawable::setAnimation
		//////////////////////////////////////////////////
		Animation(sf::Uint16 columns, sf::Uint16 rows, const sf::Texture& t, sf::Time timePerFrame, bool repeat = true);

		Animation();


		friend Drawable;
	};
}