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
	_Delim
};

// token struct : defines the token struct type and the value
struct Token {
	Type_Token type;
	std::optional<string> value;
};


class Tokenize
{
public:
	explicit Tokenize();
	Tokenize(fstream inputfile);
	~Tokenize();
	void tokenizer();
	[[nodiscard]] optional<char> peek(int peakAt = 1);
	char consume();
	void tokens_to_asm();
	void asm_to_machine_code();
private:

	vector<Token> tokens;
	string input_string;
	int currentPos = 0;
	string asm_code;

};


