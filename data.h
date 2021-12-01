#include "task.h"
struct Path
{
  // For dynamic pathname composition
  char course_path[15] = "files/courses/";
  char settings_path[16] = "files/settings/";
  char txt_ext[5] = ".txt";

  const char course_file[26] = "files/courses/courses.txt";
  const char init_file[26] = "files/settings/init.txt";
};

class Data: public Util
{
	public:
		Data();
		~Data();

    // Initialization
		bool is_init();
		void set_init(bool set_to);
    int create_course_files(char **& course_names, int num_courses);
		int write_courses_file(char **& all_courses, int num_courses);

    // File W/R
    int write_one_task(char line[]);

    int add_one_task(Task & to_add, int course_num);

    int verify_course_name(char line_to_parse[]);
    void disp_course_names();
    void disp_course_tasks();

	private:
		char ** course_names;
		class Course ** CRS; 
    int num_courses;
    int today[2] = {0,0};

    // Startup
		int read_course_names();
    int read_all_tasks();
    int load_course_paths();

    Path p;
    char* & compose_path(char dir[], char * filename, char ext[]);
    char** all_course_paths;
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
    int add_task(Task & to_add);
    void disp_tasks();
    void load_tasks();
	private:
		char* name;
		class Node* months[12];

    void disp_tasks(Node* head);
    int add_task(Task & to_add, Node* & head, int day);
    void destroy_tasks(Node* & head);
};

class Node: public Util
{
	public:
		Node();
    Node(Task & to_add);
		~Node();
		Node* & gnext();
    int get_date();
		void disp();
	private:
		Node* next;
		class Task* task;
};
