#include "task.h"
Task::
Task(): course(NULL), title(NULL), type(NULL) 
{
	id = 0;
	complete = false;
}

Task::
Task(const Task & to_copy)
{
  id = to_copy.id;
  cpy_str(course, to_copy.course);
  cpy_str(title, to_copy.title);
  cpy_str(type, to_copy.type);

  for(int i = 0; i < 3; ++i)
    date[i] = to_copy.date[i];

  for(int i = 0; i < 4; ++i)
    field_loc[i] = to_copy.field_loc[i];
}

Task::
~Task() 
{ 
	id = 0;
	if(course) { delete [] course; course = NULL; } 
	if(title) { delete [] title; title = NULL; } 
	if(type) { delete [] type; type = NULL; } 
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

int Task::
get_date(int index)
{
  if(index == 0) return date[0];
  if(index == 1) return date[1];
  if(index == 2) return date[2];
  return -1;
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
  cout << date[0] << "-" << date[1] << "-" << date[2] << endl;
}

int Task::
add(char to_parse[])
{
  if(!to_parse) return -1;
  int len = strlen(to_parse);
  int pos = 0;

  if(len == 0 || count_args(to_parse) == 0) return 0;

  pos = add_course(to_parse, pos);
  pos = add_title(to_parse, pos);
  pos = add_type(to_parse, pos);
  pos = add_date(to_parse, pos);
 
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
add_course(char* & to_parse, int offset)
{
  int i = 0;
  char tmp[CRSLEN] = {};
  field_loc[0] = offset;

  while(to_parse[offset] != '|')
  {
    tmp[i] = to_parse[offset];
    ++offset;
    ++i;
  }
  cpy_str(course, tmp);
  return ++offset;
}

int Task::
add_title(char* & to_parse, int offset)
{
  int i = 0;
  char tmp[TTLLEN] = {};
  field_loc[1] = offset;

  while(to_parse[offset] != '|')
  {
    tmp[i] = to_parse[offset];
    ++offset;
    ++i;
  }
  cpy_str(title, tmp);
  return ++offset;
}

int Task::
add_type(char* & to_parse, int offset)
{
  int i = 0;
  char tmp[TYPLEN] = {};
  field_loc[2] = offset;

  while(to_parse[offset] != '|')
  {
    tmp[i] = to_parse[offset];
    ++offset;
    ++i;
  }

  cpy_str(type, tmp);
  return ++offset;
}

int Task::
add_date(char* & to_parse, int offset)
{
  int i = 0;
  char tmp[DATLEN] = {};
  field_loc[3] = offset;

  while(to_parse[offset] != '|')
  {
    tmp[i] = to_parse[offset];
    ++offset;
    ++i;
  }

  if(date_parse(tmp) == 0)
    error("INVALID DATE, YOU ENTERED: ", tmp);
  return ++offset;
}

int Task::
date_parse(char to_parse[])
{
  using std::atoi;

  char mon[3] = {};
  char day[3] = {};
  char year[3] = {};

  int temp_mon, temp_day, temp_year = 0;
  int i = 0;

  for(int m = 0; m < 2; ++m)
  {
    mon[m] = to_parse[i];
    ++i;
  }

  for(int d = 0; d < 2; ++d)
  {
    day[d] = to_parse[i];
    ++i;
  }
  
  for(int y = 0; y < 2; ++y)
  {
    year[y] = to_parse[i];
    ++i;
  }

  temp_mon = atoi(mon);
  temp_day = atoi(day);
  temp_year = atoi(year);

  if(temp_mon > 12 || temp_mon < 1)
    return 0;
  if(temp_day > 31 || temp_day < 1)
    return 0;
  if(temp_year > 99 || temp_year < 1)
    return 0;

  date[0] = atoi(mon);
  date[1] = atoi(day);
  date[2] = atoi(year);

  return 1;
}
