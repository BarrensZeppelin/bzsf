class Desaturator {
protected:
	sf::Uint8 * targetPixels;
	sf::Uint8 * startPixels;
	sf::Uint8 * pixels;
	sf::Uint16 duration;

	bool done;

	sf::Vector2u area;
	sf::Clock clock;

public:

	sf::Uint8 * GetPixels() {
		float factor;
		if(duration != 0) {
			factor = float(clock.getElapsedTime().asMilliseconds()) / duration;
		} else factor = 20; // Just something above 1. This will make it evaluate the colours once for instant desaturation

		if(factor > 1) {
			factor = 1;
			if(done) return pixels; else done=true;
		}
		
		delete pixels;
		pixels = new sf::Uint8[area.x*area.y*4];

		for(sf::Uint16 x = 0; x < area.x; x++) {
			for(sf::Uint16 y = 0; y < area.y; y++) {
				sf::Uint32 pos = y * area.x;

				//Calculate in-between colours (during transform)
				sf::Uint8 red = startPixels[4*(pos + x)]		+ sf::Uint8((targetPixels[pos+x] - startPixels[4*(x + pos)])	*factor);
				sf::Uint8 green = startPixels[4*(pos + x)+1]	+ sf::Uint8((targetPixels[pos+x] - startPixels[4*(x + pos)+1])	*factor);
				sf::Uint8 blue = startPixels[4*(pos + x)+2]		+ sf::Uint8((targetPixels[pos+x] - startPixels[4*(x + pos)+2])	*factor);
				
				pixels[4*(x + pos)] = red;
				pixels[4*(x + pos)+1] = green;
				pixels[4*(x + pos)+2] = blue;
				pixels[4*(x + pos)+3] = startPixels[4*(x + pos)+3];
			}
		}

		return pixels;
	}

	Desaturator(const sf::Image& img, sf::Uint16 _duration) : duration(_duration), done(false), pixels(0) {	
		area = img.getSize();

		targetPixels = new sf::Uint8[area.x*area.y];
		startPixels = new sf::Uint8[area.x*area.y*4];
		
		//Create array of target pixels
		for(sf::Uint16 x = 0; x < img.getSize().x; x++) {
			for(sf::Uint16 y = 0; y < img.getSize().y; y++) {
				sf::Color c = img.getPixel(x, y); // Grab the current color

				// Calculate gray color
				//sf::Uint8 tC = (max(c.r, max(c.g, c.b)) + min(c.r, min(c.g, c.b)))/2; // Lightness
				sf::Uint8 tC = sf::Uint8(0.21f * c.r + 0.72f * c.g + 0.07f * c.b); //Luminocity
				//sf::Uint8 tC = (c.r + c.g + c.b)/3; // Average

				sf::Uint32 pos = y * area.x;
				startPixels[4*(x + pos)]   = c.r; // R
				startPixels[4*(x + pos)+1] = c.g; // G
				startPixels[4*(x + pos)+2] = c.b; // B
				startPixels[4*(x + pos)+3] = c.a; // A
			
				targetPixels[x + pos] = tC;
			}
		}
	}

	~Desaturator() {
		delete startPixels;
		delete targetPixels;
	}

};