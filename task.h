#include "util.h"
class Task: public Util
{
	public:
		Task();
		~Task();
		void disp_one(int type = 0); // types: 0 vertical with labels
		int add(char to_parse[]);
		int count_args(const char to_count[]);
		int verify_args(char to_verify[]);
		void cpy_str(char *& dst, char src[]);
	private:
		int id;
		char * course;
		char * title;
		char * type; 
		char * date;
		int field_loc[3] = {0,0,0};
		bool complete;

    void disp_type_0();
};

