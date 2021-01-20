#include "cx.h"
#define CMDS 6

class Command: public Util
{
	public:
		Command();
		~Command();
		int get(char tmp_inp[]);
		bool chk_type(char to_chk);
		char cx_get();
	private:
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
		File file;
		Context * CX;
		Command cmd;
		bool init;
};

