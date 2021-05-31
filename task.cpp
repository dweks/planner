#include "task.h"
Task::Task(): course(NULL), title(NULL), type(NULL), date(NULL)
{
	id = 0;
	complete = false;
}

Task::~Task() 
{ 
	id = 0;
  ralign("DELETING Task:course");
	if(course) { delete [] course; course = NULL; } 
  ralign("DELETING Task:title");
	if(title) { delete [] title; title = NULL; } 
  ralign("DELETING Task:type");
	if(type) { delete [] type; type = NULL; } 
  ralign("DELETING Task:date");
	if(date) { delete [] date; date = NULL; } 
	complete = 0;
}

void Task::
disp_one(int type)
{
  switch(type)
  {
    case 0: disp_type_0();
  }
}

void Task::
disp_type_0()
{
  cout << "\nCourse:  ";
  if(course) cout << course;
  else cout << "-no info-";

  cout << "\nTitle:   ";
  if(title) cout << title;
  else cout << "-no info-";

  cout << "\nType:    ";
  if(type) cout << type;
  else cout << "-no info-";

  cout << "\nDate:    ";
  if(date) cout << date;
  else cout << "-no info-";

}

int Task::
add(char to_parse[])
{
  char tmp_course[20] = {};
  char tmp_title[20] = {};
  char tmp_type[20] = {};
  char tmp_date[20] = {};

  int len = strlen(to_parse);
  int i = 0;
  int pos = 0;

  if(len == 0) return 0;

	if(count_args(to_parse) == 0)
		return 0;
 
  while(to_parse[pos] != '|')
  {
    tmp_course[i] = to_parse[pos];
    ++pos;
    ++i;
  }

  cpy_str(course, tmp_course);
  ++pos;
  i = 0;
  field_loc[0] = pos;

  while(to_parse[pos] != '|')
  {
    tmp_title[i] = to_parse[pos];
    ++pos;
    ++i;
  }

  cpy_str(title, tmp_title);
  ++pos;
  i = 0;
  field_loc[1] = pos;

  while(to_parse[pos] != '|')
  {
    tmp_type[i] = to_parse[pos];
    ++pos;
    ++i;
  }

  cpy_str(type, tmp_type);
  ++pos;
  i = 0;
  field_loc[2] = pos;

  while(to_parse[pos] != '|')
  {
    tmp_date[i] = to_parse[pos];
    ++pos;
    ++i;
  }

  cpy_str(date, tmp_date);
  ++pos;

	return 1;
}

int Task::
count_args(const char to_count[])
{
	int len = strlen(to_count);
	int counter = 0;

	for(int i = 0; i < len; ++i)
	{
		if(to_count[i] == '|')
		{
			field_loc[counter] = i;
			++counter;
		}
	}
	if(counter != 4)
		return 0;
	return 1;
}

int Task::
verify_args(char to_verify[])
{
	// Check course 
	return 0;
}

void Task::cpy_str(char *& dest, char source[])
{
	dest = new char[strlen(source) + 1];
	strcpy(dest, source);
}
