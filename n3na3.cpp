// n3na3.cpp : Defines the entry point for the compiler

#include "n3na3.h"

using namespace std;


int main(int argc, char* argv[])
{
	if (argc < 2) {
		cout << "Please Specify the Source File !" << endl;
		cout << "Correct usage n3na3 [file.n3] !" << endl;
		return EXIT_FAILURE;
	}

	Tokenize tk((fstream)argv[1]);
	tk.tokenizer();
	tk.tokens_to_asm();
	tk.asm_to_machine_code();

	return 0;
}
