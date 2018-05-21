#ifndef RESULT_HPP
#define RESULT_HPP

template<class Tv, class Te>
class Result {
protected:
	union {
		Tv _value;
		Te _error;
	};
	bool _is_error : 1;

public:
	Result(Tv&& v) : _value(v), _is_error(false) {}
	Result(Te&& e) : _error(e), _is_error(true) {}

	bool is_error() const {
		return _is_error;
	}

	bool is_okay() const {
		return !_is_error;
	}

	Tv value() const {
		return _value;
	}

	Te error() const {
		return _error;
	}

	operator bool() const {
		return !_is_error;
	}

	Tv& operator *() {
		return _value;
	}

	Tv* operator ->() {
		return &_value;
	}
};

#endif