#include "generate.hpp"


Generate::Generate(Node::Exit root) : root_node(move(root))
{
}

Generate::~Generate()
{
}

[[nodiscard]] string Generate::generater_asm() {
	stringstream output;
	output << "section .text\n    global main\n";
	output << "extern ExitProcess\n";
	output << "main:\n";
	output << "    mov rcx," << "root_node.exp.value" << "\n";
	output << "    call ExitProcess";
	this->asm_code = output.str();
	return this->asm_code;
}

void Generate::generater_machine_code()
{
	fstream outFile("main.asm", ios::out);
	outFile << this->asm_code;
	outFile.close();
	system("nasm -f win64 -o main.obj main.asm");
	system("gcc -o main.exe main.obj");
}
