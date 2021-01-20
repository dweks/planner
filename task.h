#include "util.h"
class Task
{
	public:
		Task();
		~Task();
		void disp();
		int add(char to_parse[]);
		int count_args(char to_count[]);
		int verify_args(char to_verify[]);
		int parse(char *&, char[], int off1, int off2 = 0);
		void cpy_str(char *& dst, char src[]);
	private:
		int id;
		char * course;
		char * title;
		char * type; 
		char * date;
		int field_loc[3];
		bool complete;
};

