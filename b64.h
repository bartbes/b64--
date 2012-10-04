#ifndef B64_H
#define B64_H

#include <string>

class b64
{
private:
	static const std::string characterSet;
	static const char pad;

public:
	static std::string encode(const std::string &input);
	static std::string decode(const std::string &input);
};

#endif // B64_H
