#include "tokenize.hpp"

using namespace std;

Tokenize::Tokenize(fstream inputfile)
{
	stringstream input_content;
	input_content << inputfile.rdbuf();
	inputfile.close();
	this->input_string = input_content.str();
}

Tokenize::~Tokenize()
{
}

vector<Token> Tokenize::tokenizer()
{
	vector<Token> tokens;
	string buff;
	while (peek().has_value())
	{
		if(isalpha(peek().value()))
		{
			buff.push_back(consume());
			while (isalnum(peek().value()) && peek().has_value())
			{
				buff.push_back(consume());
			}
			if (buff == "exit")
			{
				tokens.push_back(Token(Type_Token::_EXIT));
				buff.clear();
				continue;
			}
			else
			{
				cout << "Error: " << buff << " is not a valid command" << endl;
				exit(EXIT_FAILURE);
			}
		}
		else if (isdigit(peek().value()))
		{
			buff.push_back(consume());
			while (isdigit(peek().value()) && peek().has_value())
			{
				buff.push_back(consume());
			}
			tokens.push_back(Token(Type_Token::_Int, buff));
			buff.clear();
			continue;

		}
		else if (peek().value()== ';')
		{
			consume();
			tokens.push_back(Token(Type_Token::_Delim));
			continue;
		}
		else if (isspace(peek().value()))
		{
			consume();
			continue;
		}
		else
		{
			cout << "Error: " << peek().value() << " is not a valid character" << endl;
			exit(EXIT_FAILURE);
		}
	}
	currentPos = 0;
	this->tokens = tokens;
	return tokens;
}

[[nodiscard]] optional <char> Tokenize::peek(int peakAt) {
	if (currentPos + peakAt >= input_string.length()) {
		return {};
	}
	else {
		return input_string.at(currentPos + peakAt);
	}
}

char Tokenize::consume() {

	return input_string.at(currentPos++);

}