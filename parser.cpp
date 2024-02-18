#include "parser.hpp"

using namespace std;

Parser::Parser(vector<Token> input_tokens) : input_tokens(move(input_tokens))
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

optional<Node::Expression> Parser::parse_expression()
{
	if (peek().has_value() && peek().value().type == Type_Token::_Int)
	{
		return Node::Expression{.int_value = consume()};
	}
	else
	{
		return {};
	}
}


Node::Exit Parser::parse_temp()
{
	Node::Exit exit_node;
	while (peek().has_value())
	{
		if (peek().value().type == Type_Token::_EXIT)
		{
			consume();
		    if(auto exp = parse_expression())
			{
				exit_node.exp = exp.value();
			}
			else
			{
				cout << "Error: is not a valid expression" << endl;
				exit(EXIT_FAILURE);
			}
			if (peek().has_value() && peek().value().type == Type_Token::_Delim)
			{
				consume();
			}
			else
			{
				cout << "Expection a ;" << endl;
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			cout << "Error: is not a Exit function" << endl;
			exit(EXIT_FAILURE);
		}
	}
	currentPos = 0;
	return exit_node;
}

