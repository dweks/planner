#include "data.h"

Data::Data() 
{ 
	course_names = nullptr;
	UPC = nullptr;
	CRS = nullptr;
	int num = read_courses(course_names);
	if(num == 0)
		cout << "\nNo courses!\n";
	UPC = new Upcoming;
}

Data::~Data() { }

Course::Course(){}
Course::~Course(){}
Node::Node():next(nullptr), task(nullptr) { }
Node::~Node() { }

Upcoming::Upcoming(): head(nullptr), tail(nullptr)
{ 
	populate_UPC(head); 
}

Upcoming::~Upcoming(){}

File::File()
{ }

File::~File(){}

int File::read_courses(char **& course_names)
{
	char temp_course[7];
	int num_course;
	int i = 0;
	read.open("files/courses.txt");
	if(read)
	{
		read >> num_course;
		read.ignore(100, '\n');
		course_names = new char*[num_course];

		while(i < num_course && !read.eof()) 
		{
			read.get(temp_course, 7, '\n');
			cpy_str(course_names[i], temp_course);
			read.ignore(100, '\n');
			++i;
		}
	}
	read.close();
	return num_course;
}

int File::populate_UPC(Node *& head)
{
	char line[50];
	if(!head) head = new Node;
	Node * current = head;
	
	read.open("files/all_tasks.txt");
	if(read)
	{
		read.get(line, 50, '\n');
		current->set_task(line);
		read.ignore(100, '\n');

		while(!read.eof())
		{
			current->gnext() = new Node;
			current = current->gnext();
			read.get(line, 50, '\n');
			current->set_task(line);
			read.ignore(100, '\n');
		}
		current = nullptr;
	}
	read.close();
	return 1;
}

