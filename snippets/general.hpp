namespace bzsf {
	
	template <typename T>
	class ValueLimiter {
	private:
		T * value;

		sf::Vector2<T>  limits;
 
		enum Type {HARD = 1, SOFT};
		Type type;

	public:
		const T GetValue() {return *value;}

		ValueLimiter(T& val, sf::Vector2<T> limit, Type limType) : type(limType) {
			value = &val;

			if(limit.y > limit.x) swap(limit.x, limit.y);
			limits = limit;
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
	};


} //ENDOF NAMESPACE bzsf