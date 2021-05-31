#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <cctype>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::ios;
#define MAXWIDTH 56
#define DEFAULTCH '-'
#define INPUT 50
#define CRSLEN 8

class Util
{
	public:
		Util();
		~Util();
		// Functional
		void cpy_str(char *& dest, char source[], int offset = 0);
		bool confirm();
		// Visual
		void line(char ch = DEFAULTCH, int len = MAXWIDTH, bool own_line = true) const;
		void spacer(const int len);
		void center(const char to_center[], bool own_line = true);
		void header(const char text[], const char ch = '-');
		void ralign(const char to_align[]);
		// Informational
		void pg_title(const char text[], const char ch = '=');
		void error(const char err_msg[]);
		void show_entry(const char entry_to_print[]);
		void instr(const char msg[]);
		void success(const char succ_msg[]);
};

