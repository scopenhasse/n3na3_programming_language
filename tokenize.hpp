#pragma once 

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <optional>
#include <vector>

using namespace std;

// token types
enum class Type_Token {
	_EXIT,
	_Int,
	_Delim,
	_Ident,
	_var,
	_Assign
};

// token struct : defines the token struct type and the value
struct Token {
	Type_Token type;
	std::optional<string> value;
};


class Tokenize
{
public:
	Tokenize(fstream inputfile);
	~Tokenize();
	vector<Token> tokenizer();
	[[nodiscard]] optional<char> peek(int peakAt = 0);
	char consume();
private:

	vector<Token> tokens;
	string input_string;
	size_t currentPos = 0;

};


