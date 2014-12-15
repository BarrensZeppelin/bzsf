#include <SFML_Snips.hpp>

namespace bzsf {

	const float PI = 3.14159265359f;
	float DEGTORAD(float deg) {return ((deg * PI) / 180.f);}
	float RADTODEG(float rad) {return ((180.f * rad) / PI);}

	// Helper functions
	float length(sf::Vector2f vector) {
		return sqrt(vector.x * vector.x + vector.y * vector.y);
	}

	float sqrLength(sf::Vector2f vector) {
		return vector.x * vector.x + vector.y * vector.y;
	}

	sf::Vector2f unitVector(sf::Vector2f vector) {
		return vector / length(vector);
	}


	// Float Randomisation
	float randf() {
		return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	}

	float randf(float highlimit) {
		return static_cast<float>(rand()) / static_cast<float>(RAND_MAX / highlimit);
	}

	float randf(float lowlimit, float highlimit) {
		return lowlimit + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (highlimit - lowlimit));
	}

	/*template <typename T>
	class ValueLimiter*/

}