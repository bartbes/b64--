b64--
=====

A terribly named (RFC 2045) base64 encoder/decoder for c++.

Interface
---------

	// Returns a new, base64-encoded string
	std::string b64::encode(const std::string &input);

	// Returns a new, base64-decoded string
	std::string b64::decode(const std::string &input);


Example
-------

	#include <iostream>
	#include "b64.h"

	using namespace std;

	int main()
	{
		string source = "abcdefg";
		string encoded = b64::encode(source);
		string decoded = b64::decode(encoded);
		cout <<source <<endl
			<<encoded <<endl
			<<decoded <<endl;
		return 0;
	}

Will output

	abcdefg
	YWJjZGVmZw==
	abcdefg
