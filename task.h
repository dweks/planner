#include "util.h"
class Task: public Util
{
	public:
		Task();
    Task(const Task & to_copy);
		~Task();
		void disp_one(int type = 0); // types: 0 vertical with labels
		int add(char to_parse[]);
		int count_args(const char to_count[]);
    int get_date(int index);

	private:
    int add_course(char* & to_parse, int offset);
    int add_title(char* & to_parse, int offset);
    int add_type(char* & to_parse, int offset);
    int add_date(char* & to_parse, int offset);
    int date_parse(char to_parse[]);

		int id; // needs hash function
		bool complete;
		char * course;
		char * title;
		char * type; 
		int date[3] = {0,0,0};
		int field_loc[4] = {0,0,0,0};

    void disp_type_0();
};

