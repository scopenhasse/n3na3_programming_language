#pragma once 

#include "tokenize.hpp"
#include <vector>
#include <optional>
#include <variant>
using namespace std;

namespace Node
{
	struct Int_Expression {
		Token int_value;
	};

	struct Ident_Expression {
		Token ident_value;
	};

	struct Expression {
		variant<Int_Expression, Ident_Expression> value;
	};

	struct Exit {
		Expression exit;
	};

	struct Statement_var {
		Token ident;
		Expression expression;
	};

	struct Statement {
		variant<Exit, Statement_var> value;
	};

	struct Prog {
		vector<Statement> expressions;
	};
}

class Parser
{
public:
	explicit Parser(vector<Token> input_tokens);

	optional<Node::Expression> parse_expression();

	optional<Node::Statement> parse_statement();

	optional<Node::Prog> parse_prog();

	[[nodiscard]] optional<Token> peek(int peakAt = 0);
	Token consume();

private:
	const vector<Token> input_tokens;
	size_t currentPos = 0;


};

