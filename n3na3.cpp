// n3na3.cpp : Defines the entry point for the compiler

#include "n3na3.h"
#include <fstream>
#include <string>
#include <sstream>
#include <optional>
#include <vector>

using namespace std;

enum class Type_Token {
	_return,
	_Int,
	delim
};

struct Token {
	Type_Token type;
	std::optional<string> value;
};



vector<Token> tokenizer(const string &input) 
{
	vector<Token> result;
	string buff;
	cout << "here" << endl;
	for (unsigned int i = 0; i < input.length(); i++)
	{
		char c = input.at(i);
		if (isalpha(c))
		{
			buff.push_back(input.at(i));
			i++;
			while (isalnum(input.at(i)))
			{
				buff.push_back(input.at(i));
				i++;
			}
			i--;
			if (buff == "return")
			{
				result.push_back({ .type = Type_Token::_return });
				buff.clear();
				continue;
			}
			else 
			{
				cout << "no no no" << endl;
				exit(EXIT_FAILURE);
			}
		}
		else if (isdigit(c))
		{
			buff.push_back(input.at(i));
			i++;
			while (isdigit(input.at(i)))
			{
				buff.push_back(input.at(i));
				i++;
			}
			i--;
			result.push_back({ .type = Type_Token::_Int, .value = buff});
			buff.clear();
		}
		else if (c == ';')
		{
			result.push_back({ .type = Type_Token::delim });
		}
		else if (isspace(c)) 
		{
			continue;
		}
		else 
		{
			cout << "no no no" << endl;
			exit(EXIT_FAILURE);
		}
	}
	return result;
}

string tokens_to_asm(const vector<Token> tokens) {
	stringstream output;
	output << "section .text\n    global main\n";
	output << "extern ExitProcess\n";
	output << "main:\n";
	output << "    mov rcx," << tokens.at(1).value.value() << "\n";
	output << "    call ExitProcess";
	return output.str();
}

int main(int argc, char* argv[])
{
	if (argc < 2) {
		cout << "Please Specify the Source File !" << endl;
		cout << "Correct usage n3na3 [file.n3] !" << endl;
		return EXIT_FAILURE;
	}

	fstream input(argv[1], ios::in);
	stringstream input_content;
	input_content << input.rdbuf();
	input.close();

	string string_content;
	string_content = input_content.str();

	fstream outFile("output.asm", ios::out);
	outFile << tokens_to_asm(tokenizer(string_content));
	outFile.close();
	
	system("nasm -f win64 output.asm");
	system("gcc -o output.exe output.obj");

	return 0;
}
