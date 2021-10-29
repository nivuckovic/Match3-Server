#include "StringUtility.h"

std::vector<std::string> StringUtility::Split(std::string stringToSplit, char delimiter)
{
	std::vector<std::string> result;

	size_t pos = 0;
	std::string token;
	while ((pos = stringToSplit.find(delimiter)) != std::string::npos) {
		result.push_back(token = stringToSplit.substr(0, pos));

		stringToSplit.erase(0, pos + 1); // 1 = delimiter length
	}

	if(stringToSplit.size() > 0)
		result.push_back(stringToSplit);

	return result;
}
