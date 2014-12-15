
namespace bzsf{
	template<typename T>
	std::string toString(const T& t) {
		std::ostringstream os;
		os << t;
		return os.str();
	}

	template<typename T>
	T fromString(const std::string& str) {
		std::istringstream is(str);
		T t;
		is >> t;
		return t;
	}
}