#include "task.h"
Task::Task(): course(NULL), title(NULL), type(NULL), date(NULL)
{
	id = 0;
	complete = false;
}

Task::~Task() 
{ 
	id = 0;
	if(course) { delete [] course; course = NULL; } 
	if(title) { delete [] title; title = NULL; } 
	if(type) { delete [] type; type = NULL; } 
	if(date) { delete [] date; date = NULL; } 
	complete = 0;
}

void Task::disp()
{
	if(course) cout << course << "|";
	if(title) cout << title << "|";
	if(date) cout << date << "|";
	if(type) cout << type << "|\n";
}

int Task::add(char to_parse[])
{
	int len = 0;
	int ret = 0;

	if(count_args(to_parse) == 0)
		return 0;

	ret = parse(course, to_parse, len, field_loc[0]);
	len += ret + 1;
	
	ret = parse(title, to_parse, len, field_loc[1]);
	len += ret + 1;

	ret = parse(date, to_parse, len, field_loc[2]);
	len += ret + 1;

	ret = parse(type, to_parse, len, strlen(to_parse) - 1);
	len += ret + 1;

	return 1;
}

int Task::count_args(char to_count[])
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
	if(counter < 4)
		return 0;
	return 1;
}

int Task::verify_args(char to_verify[])
{
	// Check course 
	return 0;
}

int Task::parse(char *& dst, char prs[], int off1, int off2)
{
	int c = off1;
	int t = 0;
	int len = off2 - off1;

	char * tmp = NULL;
	tmp = new char[len + 1];

	//cout << off2 << " " << off1 << " " << len << " " << strlen(tmp) << endl;
	while(prs[c] != '|' && prs[c] != '\0' && prs[c] != '\n')
	{
		tmp[t] = prs[c];
		++c; ++t;
	}

	//int test = strlen(tmp) + 1;
	//cout << "\nin cpystr, strlen = " << test << endl;
	cpy_str(dst, tmp);
		
	if(tmp) { delete [] tmp; tmp = NULL; }
	return t;
}

void Task::cpy_str(char *& dest, char source[])
{
	dest = new char[strlen(source) + 1];
	strcpy(dest, source);
}
