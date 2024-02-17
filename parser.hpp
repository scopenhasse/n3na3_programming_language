#pragma once 

#include "tokenize.hpp"
#include <vector>

using namespace std;

namespace Node
{
	struct Expression {
		Token int_value;
	};

	struct Exit {
		Node::Expression exp;
	};
}

class Parser
{
public:
	explicit Parser();

	Node::Expression parse_expression();

	Node::Exit parse_temp();

	[[nodiscard]] optional<Token> peek(int peakAt = 0);
	Token consume();

private:
	const vector<Token> input_tokens;
	size_t currentPos = 0;


};

