class texAnimation {
protected:
	int frameWidth;
	
	int frameIndex;
	int numFrames;

	unsigned int speed; //Speed in milliseconds between each change

	bool repeat;

	sf::Clock timer;

	sf::Texture * texture;

public:
	int GetWidth()			{return frameWidth;	}
	int GetHeight()			{return texture->getSize().y;}
	int GetIndex()			{return frameIndex;	}
	int GetFrames()			{return numFrames;	}
	unsigned int GetSpeed()	{return speed;		}

	void SetSpeed(unsigned int s) {speed = s;}

	void UpIndex()	{
		if(frameIndex < numFrames-1) {
			frameIndex++;
		} else if(repeat) {
			frameIndex = 0;
		}
	}


	sf::Clock * GetTimer()		{return &timer;	}
	bool IsRepeating()			{return repeat;	}
	sf::Texture * GetTexture()	{return texture;}

	texAnimation(int fWidth, sf::Texture * t, bool r, int s) : repeat(r), texture(t), speed(s), frameWidth(fWidth), frameIndex(0) {
		if(t->getSize().x%fWidth!=0) {cerr << "Animation creation error: sizes are incompatible" << endl;}
		numFrames = t->getSize().x / fWidth;
	}
};