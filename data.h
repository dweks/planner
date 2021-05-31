#include "task.h"
class File: public Util
{
	public:
		File();
		~File();


	private:
};

struct Path
{
  char course_path[15] = "files/courses/";
  char settings_path[16] = "files/settings/";
  char txt_ext[5] = ".txt";
};

class Data: public Util
{
	public:
		Data();
		~Data();

		bool is_init();
		void set_init(bool set_to);
    int create_course_files(char **& course_names, int num_courses);

    int write_one_task(char line[], char course_name[]);
		int write_courses(char **& all_courses, int num_courses);

		int read_courses(char **& course_names);
    int read_tasks(char **& course_names, int num_courses);

    bool verify_course_name(char line_to_parse[]);
    bool add_course(class Course & to_add);
    void disp_course_names();

	private:
		char ** course_names;
		class Course ** CRS; 
    int num_courses;

    Path p;
    char* & compose_path(char dir[], char * filename, char ext[]);
    char* path;

		ofstream write;
		ifstream read;

    void destroy_CRS();
    void destroy_course_names();
};

class Course: public Util
{
	public:
		Course();
    Course(char* & to_set);
		~Course();
    bool set_name(char to_set[]);
    void disp_name();
    void load_tasks();
	private:
		char * name;
		class Node * head;

    void destroy_tasks(Node* & head);
};

class Node: public Util
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
