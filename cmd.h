#include "cx.h"
#define CMDS 6

class Command: public Util
{
	public:
		Command();
		~Command();

		int get(char tmp_inp[]);
		char cx_get();

	private:
    int cmd_type(char tmp_inp[], int len);
		bool is_valid_code(char to_chk);
		char cmd_arr[CMDS] = {'a','e','r','c','h','q'};
		char cx;
};

class Interface: public Util
{
	public:
		Interface();
		~Interface();

		void container();
		int initialize();

		void cx_switch(Context *& to_set, const char current_cx);
		bool cx_test(char &current, const char test);
		
	private:
		Data data;
		Context * CX;
		Command cmd;
		bool init;
};

