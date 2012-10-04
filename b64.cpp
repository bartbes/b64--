#include <string>
#include <sstream>
#include "b64.h"

using std::string;
using std::stringstream;

const string b64::characterSet = 
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz"
	"0123456789+/";

const char b64::pad = '=';

string b64::encode(const string &input)
{
	stringstream output;
	char remainder = 0;
	unsigned int i;

	for (i = 0; i < input.size(); i++)
	{
		unsigned char c = input[i];

		switch(i%3)
		{
		case 0:
			output <<characterSet[c >> 2];
			remainder = (c & 0x03) << 4;
			break;
		case 1:
			output <<characterSet[remainder | (c >> 4)];
			remainder = (c & 0x0f) << 2;
			break;
		case 2:
			output <<characterSet[remainder | (c >> 6)]
				<< characterSet[c & 0x3f];
			break;
		}
	}

	if (i % 3 != 0)
	{
		output <<characterSet[remainder];
		for (unsigned int j = 3; j > (i % 3); j--)
			output <<pad;
	}

	return output.str();
}

string b64::decode(const string &input)
{
	stringstream output;
	char remainder = 0;
	unsigned int i;
	bool foundPadding = false;

	for (i = 0; i < input.size(); i++)
	{
		unsigned char c = input[i];

		if (c == pad)
		{
			foundPadding = true;
			continue;
		}
		else if (foundPadding)
			return "";

		switch(i%4)
		{
		case 0:
			c = characterSet.find(c);
			if (c == string::npos)
				return "";

			remainder = (c << 2);
			break;
		case 1:
			c = characterSet.find(c);
			if (c == string::npos)
				return "";

			output <<(unsigned char) (remainder | (c >> 4));
			remainder = (c & 0x0f) << 4;
			break;
		case 2:
			c = characterSet.find(c);
			if (c == string::npos)
				return "";

			output <<(unsigned char) (remainder | (c >> 2));
			remainder = (c & 0x03) << 6;
			break;
		case 3:
			c = characterSet.find(c);
			if (c == string::npos)
				return "";

			output <<(unsigned char) (remainder | c);
			break;
		}
	}

	if (i % 4 != 0)
	{
		return "";
	}

	return output.str();
}
