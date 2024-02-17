#include "parser.hpp"

using namespace std;

Parser::Parser()
{
}


[[nodiscard]] optional <Token> Parser::peek(int peakAt) {
	if (currentPos + peakAt >= input_tokens.size()) {
		return {};
	}
	else {
		return input_tokens.at(currentPos + peakAt);
	}
}

Token Parser::consume() {

	return input_tokens.at(currentPos++);

}

Node::Exit Parser::parse_temp()
{
	Node::Exit exit_node;
	while (peek().has_value())
	{
		// TODO : parse the exit token if the expresstion is valid
	}
	currentPos = 0;
	return ;
}

Node::Expression Parser::parse_expression()
{
	// TODO : parse the expression token
}