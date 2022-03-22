#pragma once
#include <string>

using std::string;

bool iequals(const string& a, const string& b)
{
	const auto size = a.size();
	if (b.size() != size)
		return false;
	for (unsigned int i = 0; i < size; i++)
		if (tolower(a.at(i)) != tolower(b.at(i)))
			return false;
	return true;
}

void string_toLower(string& a)
{
	const auto size = a.size();
	for (unsigned int i = 0; i < size; i++)
		a.at(i) = (char)tolower(a.at(i));
}