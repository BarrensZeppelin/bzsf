#include <SFML_Snips.hpp>

namespace bzsf {

	const float PI = 3.14159265359f;
	float DEGTORAD(float deg) {return ((deg * PI) / 180.f);}
	float RADTODEG(float rad) {return ((180.f * rad) / PI);}

	// Helper functions
	float Length(sf::Vector2f vector) {
		return sqrt(vector.x * vector.x + vector.y * vector.y);
	}

	float SqrLength(sf::Vector2f vector) {
		return vector.x * vector.x + vector.y * vector.y;
	}

	sf::Vector2f UnitVector(sf::Vector2f vector) {
		return vector / Length(vector);
	}

	/*template <typename T>
	class ValueLimiter*/

}