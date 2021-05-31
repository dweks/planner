#include "data.h"

int Data
::write_one_task(char line[], char course_name[])
{
  /*
	write.open("files/all_tasks.txt", ios::app);

	if(write)
		write << to_write << '\n';
	write.close();
	if(!write)
		return 0;
  */
	return 1;
}

bool Data::
is_init()
{
	int init;
  int course_check;

	read.open("files/settings/init.txt");
	if(read)
		read >> init;
	read.ignore(100, '\n');
	read.close();
  // Sends warning if program says uninitialized but 
  // course files exist
	if(init != 1)
  {
    read.open("files/courses/courses.txt");
    if(read)
      read >> course_check;
    read.ignore(100, '\n');
    read.close();
    if(course_check > 0)
    {
      cout
      << "\n(!) Program uninitialized but courses exist.\n"
      << "    Check courses.txt and init.txt before adding\n"
      << "    new courses.\n";
    }
		return false;
  }

	return true;
}

void Data::
set_init(bool set_to)
{
	if(set_to == true)
	{
		write.open("files/settings/init.txt", ios::trunc);
		if(write)
			write << set_to << '\n';
		write.close();
	}
}

int Data
::write_courses(char **& all_courses, int num_course)
{
	write.open("files/courses/courses.txt", ios::trunc);
	if(write)
	{
		write << num_course << '\n';
		for(int i = 0; i < num_course; ++i)
			write << all_courses[i] << '\n';
		write.close();
		return 1;
	}
	write.close();
	return 0;
}

// Create .txt files based on user input for course names.
int Data
::create_course_files(char **& course_names, int num_course)
{
  if(!course_names) return 0;
  for(int i = 0; i < num_course; ++i)
  {
    ralign(course_names[i]);
    char* temp = compose_path(p.course_path, course_names[i], p.txt_ext);

    if(!temp) error("COMPOSE PATH FAIL"); 

    else
    {
      write.open(temp);
      if(!write) error("COURSE FILE NOT WRITTEN");
      write.close();
    }
  }
  return 1;
}

char* & Data
::compose_path(char dir[], char * filename, char ext[])
{
  if(path) 
  {
    delete [] path;
    path = NULL;
  }

  ralign(dir);
  ralign(filename);
  ralign(ext);

  cpy_str(path, dir);
  strcat(path, filename);
  strcat(path, ext);
  return path;
}

bool Data
::verify_course_name(char line_to_parse[])
{
  char temp[CRSLEN]; 
  char* for_cmp = NULL;
  int x = 0;

  while(line_to_parse[x] != '|')
  {
    temp[x] = line_to_parse[x];
    ++x;
  }

  cpy_str(for_cmp, temp);

  for(int i = 0; i < num_courses; ++i)
  {
    if(strcmp(for_cmp, course_names[i]) == 0)
      return true;
  }
  return false;
}

bool Data
::add_course(Course & to_add) { return false; }

void Data
::disp_course_names()
{
  for(int i = 0; i < num_courses; ++i)
    CRS[i]->disp_name();
}

bool Course
::set_name(char to_set[])
{
  if(!to_set) return false;
  cpy_str(name, to_set);
  if(name) return true;
  return false;
}

void Course
::disp_name() { cout << name << " "; }

Node *& Node::gnext() { return next; }

int Node::
set_task(char entry[])
{
	if(task) delete task;
	task = new Task;
	return task->add(entry);
}

void Node::disp() { task->disp_one(); }

