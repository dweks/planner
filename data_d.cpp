#include "data.h"

Data::Data():course_names(NULL), CRS(NULL), path(NULL)
{ 
  // Loads course names to memory
	num_courses = read_courses(course_names);

	if(num_courses == 0 && is_init())
		error("INITIALIZED BUT NO COURSES");
  else
  {
    CRS = new Course * [num_courses];
    for(int i = 0; i < num_courses; ++i)
      CRS[i] = new Course(course_names[i]);
  }

  read_tasks(course_names, num_courses);
}

Data::~Data() 
{
  ralign("DESTROYING CRS");
  if(CRS) destroy_CRS();
  ralign("DESTROYING course_names");
  if(course_names) destroy_course_names();
  if(path) 
  {
    ralign("DELETING path");
    delete [] path;
    path = NULL;
  }
  num_courses = 0;
}

void Data
::destroy_CRS()
{
  if(!CRS) return;

  for(int i = 0; i < num_courses; ++i)
  {
    if(CRS[i])
    {
      ralign("DELETING CRS[i]");
      delete CRS[i];
      CRS[i] = NULL;
    }
  }
  if(CRS)
  {
    ralign("DELETING CRS");
    delete CRS;
    CRS = NULL;
  }
}

void Data
::destroy_course_names()
{
  if(!course_names) return;

  for(int i = 0; i < num_courses; ++i)
  {
    if(course_names[i])
    {
      ralign("DELETING course_names[i]");
      delete [] course_names[i];
      course_names[i] = NULL;
    }
  }

  if(course_names)
  {
    ralign("DELETING course_names");
    delete course_names;
    course_names = NULL;
  }
}

Course::Course(): name(NULL), head(NULL) { }
Course::Course(char *& to_set) 
{ 
  name = new char[strlen(to_set) + 1];
  strcpy(name, to_set);
  head = NULL;
}
Course::~Course()
{
  if(name)
  {
    ralign("DELETING name");
    delete [] name; 
    name = NULL;
  }
  ralign("DESTROYING tasks");
  //if(head) destroy_tasks(head);
}

void Course
::destroy_tasks(Node* & head)
{
  if(!head) return;
  destroy_tasks(head->gnext());
  if(head)
  {
    ralign("DELETING head");
    delete head;
    head = NULL;
  }
}

Node::Node():next(NULL), task(NULL) {cout << "node created"; }
Node::~Node() 
{ 
  if(task)
  {
    ralign("DELETING Node:task");
    delete task;
    task = NULL;
  }
  next = NULL;
}

// Loads course names from courses.txt to array in Data
int Data
::read_courses(char **& course_names)
{
	char temp_course[7];
	int num_course;
	int i = 0;

	read.open("files/courses/courses.txt");
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


int Data
::read_tasks(char** & course_names, int num_courses)
{
  /*
  for(int i = 0; i < num_courses; ++i)
  {
    char temp_name[8];
    read.open("files/all_tasks.txt");
    if(!read)
      error("COURSE NOT READ");

    else
    {
      read.get(temp_name, 10, '|');
      cout << "\nfrom file: " << temp_name << "\ncourse array: " << course_names[i] << endl; if(strcmp(temp_name, course_names[i]) == 0);
      //if(strcmp(temp_name, course_names[i]) == 0)

      read.ignore(100, '\n');

      while(!read.eof())
      {
        char temp_name[8];
        read.get(temp_name, 50, '|');
        cout << "\nfrom file: " << temp_name << "\ncourse array: " << course_names[i] << endl;
        //if(strcmp(temp_name, course_names[i]) == 0)
        read.ignore(100, '\n');
      }
    }
  }
  read.close();
  */
  return 1;
}
/*
int Data 
::populate_UPC(Node *& head)
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
		current = NULL;
	}
	read.close();
	return 1;
}
*/

