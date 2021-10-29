#pragma once

#include "JSONNode.h"
#include <vector>
#include <algorithm>

template <typename T>
class JSONVectorNode : public JSONNode
{
public:
	JSONVectorNode(std::vector<T> value);

	std::vector<T> GetValue();

	// Inherited via JSONNode
	virtual std::string ToString() override;

private:
	std::vector<T> _value;
};

template <typename T>
inline std::vector<T> JSONVectorNode<T>::GetValue()
{
	return _value;
}

template<typename T>
inline JSONVectorNode<T>::JSONVectorNode(std::vector<T> value) : _value(value)
{

}

template<typename T>
inline std::string JSONVectorNode<T>::ToString()
{
	std::string msg = "[";
	std::for_each(_value.begin(), _value.end(), [&msg](T x) {
		if constexpr (std::is_same<T, std::string>::value)
			msg += "\"" + x + "\", ";
		else
			msg += std::to_string(x) + ", ";
	});

	msg += "]";

	return msg;
}

