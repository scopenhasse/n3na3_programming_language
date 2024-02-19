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
		return Node::Expression{ .value = Node::Int_Expression{.int_value = consume()}};
	}
	else if (peek().has_value() && peek().value().type == Type_Token::_Ident)
	{
		return Node::Expression{ .value = Node::Ident_Expression{.ident_value = consume()}};
	}
	else
	{
		return {};
	}
}

optional <Node::Statement> Parser::parse_statement()
{
	if (peek().value().type == Type_Token::_EXIT)
	{
		consume();
		Node::Exit statexit;
		if (auto exp = parse_expression())
		{
			statexit.exit = exp.value();
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

		return Node::Statement{ .value = statexit };
	}
	else if (peek().has_value() && peek().value().type == Type_Token::_var && peek(1).has_value() && peek(1).value().type == Type_Token::_Ident && peek(2).has_value() && peek(2).value().type == Type_Token::_Assign)
	{
		consume();
		auto varStat = Node::Statement_var{ .ident = consume() };
		consume();
		if(auto exp = parse_expression())
		{
			varStat.expression = exp.value();
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
		return Node::Statement{ .value = varStat };
	}
	else
	{
		return {};
	}
}