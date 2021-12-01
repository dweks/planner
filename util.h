#include "preproc.h"

class Util
{
	public:
		Util();
		~Util();

		// Functional
		void cpy_str(char *& dest, char source[], int offset = 0);
		bool confirm(const char msg[] = "");
    bool cin_fail();

		// Heading
		void header(const char text[], const char ch = '-');
		void pg_title(const char text[], const char ch = '=');
		void line(char ch = DEFAULTCH, int len = MAXWIDTH, bool own_line = true) const;

    // Alignment
		void ralign(const char to_align[]);
		void spacer(const int len);
		void center(const char to_center[], bool own_line = true);

		// Informational
		void error(const char msg[], const char sub_msg[] = "");
		void warning(const char msg[], const char sub_msg[] = "");
		void success(const char msg[], const char sub_msg[] = "");
		void instr(const char msg[], const char sub_msg[] = "");
    void get_today(int to_fill[]);
};
