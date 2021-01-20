#include "task.h"
class File: public Util
{
	public:
		File();
		~File();
		int write_one(char to_write[]);
		bool is_init();
		void set_init(bool set_to);
		int write_courses(char **& all_courses, int num_course);
		int read_courses(char **& course_names);
		int populate_UPC(class Node *& head);

	private:
		ofstream write;
		ifstream read;
};

class Data: public File
{
	public:
		Data();
		~Data();
		void disp_UPC();

	private:
		char ** course_names;
		class Upcoming * UPC;
		class Course ** CRS; // array of courses
};

class Course: public File 
{
	public:
		Course();
		~Course();
	private:
		char * name;
		class Node * head;
};

class Node
{
	public:
		Node();
		~Node();
		Node *& gnext();
		int set_task(char entry[]);
		void disp();
	private:
		Node * next;
		class Task * task;
};

class Upcoming: public File
{
	public:
		Upcoming();
		~Upcoming();
		void disp();
	private:
		void disp(Node *&);
		Node * head;
		Node * tail;
};
