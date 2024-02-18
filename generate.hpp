#pragma once
#include "parser.hpp"

class Generate
{
public:
	explicit Generate(Node::Exit root);
	~Generate();

	[[nodiscard]] string generater_asm();
	void generater_machine_code();

private:
	Node::Exit root_node;
	string asm_code;

};