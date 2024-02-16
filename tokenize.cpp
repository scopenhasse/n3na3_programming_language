#include "tokenize.hpp"

using namespace std;

Tokenize::Tokenize()
{
}

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

void Tokenize::tokenizer()
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

void Tokenize::tokens_to_asm() {
	stringstream output;
	output << "section .text\n    global main\n";
	output << "extern ExitProcess\n";
	output << "main:\n";
	output << "    mov rcx," << tokens.at(1).value.value() << "\n";
	output << "    call ExitProcess";
	this->asm_code = output.str();
}

void Tokenize::asm_to_machine_code(){
	fstream outFile("main.asm", ios::out);
	outFile << this->asm_code;
	outFile.close();
	system("nasm -f win64 -o main.obj main.asm");
	system("gcc -o main.exe main.obj");
}