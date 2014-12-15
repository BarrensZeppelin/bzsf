namespace bzsf {
	extern const float PI;
	float DEGTORAD(float deg);
	float RADTODEG(float rad);

	// Generalized toString
	template<typename T>
	std::string toString(const T& t);

	template<typename T>
	T fromString(const std::string& str);

	// Helper functions
	float length(sf::Vector2f vector);

	float sqrLength(sf::Vector2f vector);

	sf::Vector2f unitVector(sf::Vector2f vector);


	// Float Randomization
	float randf();
	float randf(float highlimit);
	float randf(float lowlimit, float highlimit);

	/*template <typename T>
	class ValueLimiter {
	private:
		T value;

		sf::Vector2<T>  limits;
 
		enum Type {HARD = 1, SOFT};
		Type type;

	public:
		const T GetValue() {return *value;}

		ValueLimiter(T& val, sf::Vector2<T> limit, Type limType) : type(limType) {
			value = val;

			if(limit.y < limit.x) swap(limit.x, limit.y);
			limits = limit;

			if(value < limit.x) value = limit.x;
			if(value > limit.y) value = limit.y;
		}

		void Add(const T val) {
			if( *value + val < limits.y ) {
				*value+=val;
				if(type == HARD) { if(*value > limits.y) *value = limits.y; }
			}
		}

		void Sub(const T val) {
			if( *value - val > limits.x ) {
				*value-=val;
				if(type == HARD) { if(*value < limits.x) *value = limits.x; }
			}
		}

		
		operator T() {
			return *value;
		}


		ValueLimiter& operator=(const T val) {
			*value = val;
			return *this;
		}

		ValueLimiter& operator+=(const T val) {
			Add(val);
			return *this;
		}

		ValueLimiter& operator-=(const T val) {
			Sub(val);
			return *this;
		}

		const T operator+(const T& val) const {
			return *(*this += val).value;
		}

		const T operator-(const T& val) const {
			return *(*this -= val).value;
		}
	};*/

} //ENDOF NAMESPACE bzsf


#include "general.inl"