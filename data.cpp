#include "data.h"

bool Data::
is_init()
{
	int init;
  int course_check;

	read.open(p.init_file);
	if(read)
		read >> init;
	read.ignore(100, '\n');
	read.close();
  // Sends warning if program says uninitialized but 
  // course files exist
	if(init != 1)
  {
    read.open(p.course_file);
    if(read)
      read >> course_check;
    read.ignore(100, '\n');
    read.close();

    if(course_check > 0)
    {
      error(
      "UNINITIALIZED BUT EXISTING COURSES",
      "Check courses.txt and init.txt");
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
		write.open(p.init_file, ios::trunc);
		if(write)
			write << set_to << '\n';
		write.close();
	}
}

int Data::
write_courses_file(char **& all_courses, int num_course)
{
	write.open(p.course_file, ios::trunc);
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


int Data::
write_one_task(char line[])
{
  char temp[CRSLEN] = {}; 
  char* to_compose = NULL;
  char* write_to = NULL;
  int x = 0;

  while(line[x] != '|')
  {
    temp[x] = line[x];
    ++x;
  }

  cpy_str(to_compose, temp);
  write_to = compose_path(p.course_path, to_compose, p.txt_ext);
  
	write.open(write_to, ios::app);

	if(write)
		write << line << '\n';
	else
		return 0;
	write.close();
	return 1;
}

// Create .txt files based on user input for course names.
int Data::
create_course_files(char **& course_names, int num_course)
{
  if(!course_names) return 0;
  for(int i = 0; i < num_course; ++i)
  {
    char* temp = compose_path(p.course_path, course_names[i], p.txt_ext);
    if(!temp) error("COMPOSE PATH FAIL"); 
    else
    {
      write.open(temp);
      if(!write) error("COURSE FILE NOT WRITTEN");
      write.close();
    }
    if(temp) { delete [] temp; temp = NULL; }
  }
  return 1;
}

char* & Data::
compose_path(char dir[], char * filename, char ext[])
{
  if(path) 
  {
    delete [] path;
    path = NULL;
  }

  cpy_str(path, dir);
  strcat(path, filename);
  strcat(path, ext);
  return path;
}

int Data::
verify_course_name(char line_to_parse[])
{
  int ret = -1;
  char temp[CRSLEN] = {}; 
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
      ret = i;
  }
  return ret;
}

void Data::
disp_course_names()
{
  for(int i = 0; i < num_courses; ++i)
  {
    cout << "Course " << i + 1 << ": ";
    CRS[i]->disp_name();
    cout << endl;
  }
}

int Data::
add_one_task(Task & to_add, int course_num)
{
  return CRS[course_num]->add_task(to_add);
}

void Data::
disp_course_tasks()
{
  for(int i = 0; i < num_courses; ++i)
    CRS[i]->disp_tasks();
}

// Loads course names from courses.txt to array in Data
int Data::
read_course_names()
{
	char temp_course[7];
	int num_course;
	int i = 0;

	read.open(p.course_file);
	if(read)
	{
    // Reads first line of courses.txt which contains 
    // number of courses determined at initialization
		read >> num_course;
		read.ignore(100, '\n');
		course_names = new char*[num_course];

    // Reads each line after first to load course_names array
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

int Data::
load_course_paths()
{
  for(int i = 0; i < num_courses; ++i)
  {
    char* temp_full_path
    = compose_path(p.course_path, course_names[i], p.txt_ext);

    cpy_str(all_course_paths[i], temp_full_path);
  }
}

int Data::
read_all_tasks()
{
  for(int i = 0; i < num_courses; ++i)
  {
    read.open(all_course_paths[i]);
    if(read)
    {
      read.ignore(100, '\n');

      while(!read.eof()) 
      {
      }
    }
    else return -1;
    read.close();
  }
  return 0;
}

bool Course::
set_name(char to_set[])
{
  if(!to_set) return false;
  cpy_str(name, to_set);
  if(name) return true;
  return false;
}

int Course::
add_task(Task & to_add)
{
  int m = to_add.get_date(0) - 1;
  int d = to_add.get_date(1);
  if(!months[m])
  {
    months[m] = new Node(to_add);
    return 1;
  }
  return add_task(to_add, months[m], d);
}

int Course::
add_task(Task & to_add, Node* & head, int day)
{
  if(!head) return 0;
  if(day >= head->get_date())
    return add_task(to_add, head->gnext(), day);
  Node * temp = new Node(to_add);
  Node * hold = head->gnext();
  head->gnext() = temp;
  temp->gnext() = hold;
  return 1;
}

void Course::
disp_tasks()
{
  for(int i = 0; i < 12; ++i)
    disp_tasks(months[i]);
}

void Course::
disp_tasks(Node* head)
{
  if(!head) return;
  head->disp();
  disp_tasks(head->gnext());
}

void Course::
disp_name() { cout << name << " "; }

int Node::
get_date() { return task->get_date(1); }

Node *& Node::
gnext() { return next; }

void Node::
disp() { task->disp_one(); }


