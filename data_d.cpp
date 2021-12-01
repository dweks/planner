#include "data.h"

Data::
Data(): path(NULL)
{ 
  // Loads course names to memory, returns number of courses
	num_courses = read_course_names();

  // Special error case: no courses but program is initialized
	if(num_courses == 0 && is_init())
		error("INITIALIZED BUT NO COURSES");
  else
  {
    // double free here v
    all_course_paths = new char* [num_courses];
    for(int i = 0; i < num_courses; ++i)
      all_course_paths[i] = NULL;
    load_course_paths();
    ralign("1");
    CRS = new Course* [num_courses];
    for(int i = 0; i < num_courses; ++i)
      CRS[i] = new Course(course_names[i]);
  }
  // Sets today array with [0] = month, [1] = day
  get_today(today);
}

Data::
~Data() 
{
  if(CRS) destroy_CRS();
  if(course_names) destroy_course_names();
  if(path) 
  {
    delete [] path;
    path = NULL;
  }
  num_courses = 0;
}

void Data::
destroy_CRS()
{
  if(!CRS) return;

  for(int i = 0; i < num_courses; ++i)
  {
    if(CRS[i])
    {
      delete CRS[i];
      CRS[i] = NULL;
    }
  }
  if(CRS)
  {
    delete CRS;
    CRS = NULL;
  }
}

void Data::
destroy_course_names()
{
  if(!course_names) return;

  for(int i = 0; i < num_courses; ++i)
  {
    if(course_names[i])
    {
      delete [] course_names[i];
      course_names[i] = NULL;
    }
  }

  if(course_names)
  {
    delete course_names;
    course_names = NULL;
  }
}


Course::
Course(): name(NULL)
{ 
  for(int i = 0; i < 12; ++i)
    months[i] = NULL;
}

Course::
Course(char *& to_set) 
{ 
  name = new char[strlen(to_set) + 1];
  strcpy(name, to_set);
  for(int i = 0; i < 12; ++i)
    months[i] = NULL;
}

Course::
~Course()
{
  if(name)
  {
    delete [] name; 
    name = NULL;
  }
  for(int i = 0; i < 12; ++i)
    if(months[i]) destroy_tasks(months[i]);
}

void Course::
destroy_tasks(Node* & head)
{
  if(!head) return;
  destroy_tasks(head->gnext());
  if(head)
  {
    delete head;
    head = NULL;
  }
}

Node::
Node():next(NULL), task(NULL){}

Node::
Node(Task & to_add)
{
  task = new Task(to_add);
  next = NULL;
}

Node::
~Node() 
{ 
  if(task)
  {
    delete task;
    task = NULL;
  }
  next = NULL;
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

