#ifndef DATA_STRUCTURES_PROJECT_OPTION_H
#define DATA_STRUCTURES_PROJECT_OPTION_H

template<typename T>
class Option {
	
	T thing;
	bool populated;
	
public:
	Option() noexcept : populated(false) {}
	Option(T const& value) noexcept : thing(value), populated(true) {}
	Option(T&& value) noexcept : thing(std::move(value)), populated(true) {}
	virtual ~Option() = default;
	
	bool hasValue() const { return populated; }
	const T& value() const { return populated ? &thing : std::terminate(); }
	const T& valueOr(T const& alt) const { return populated ? &thing : alt; }
	T&& unwrap() {
		if (! populated)
			std::terminate();
		
		populated = false;
		return std::move(thing);
	}
	T&& unwrapOr(T&& alt) {
		if (! populated)
			return std::forward(alt);
		
		populated = false;
		return std::move(thing);
	}
	
};

#endif //DATA_STRUCTURES_PROJECT_OPTION_H
