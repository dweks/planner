#include "cx.h"
Context::Context() { }
Context::~Context() {}

Add::Add():task(NULL) {}
Add::~Add() { if(task) delete task; task = NULL; }

Edit::Edit() {}
Edit::~Edit() {}

Help::Help() {}
Help::~Help() {}

void Context::disp_title() { header(cx_title); }
void Add::disp_title() { header(cx_title); }
void Edit::disp_title() { header(cx_title); }
void Help::disp_title() { header(cx_title); }

void Context::
action(char *& entry, Data & data)
{
	//data.disp_UPC();
}

void Add
::action(char *& entry, Data & data) 
{ 
	if(!entry)
    instr("Enter new task...");

  else if(!data.verify_course_name(entry))
  {
    error("NO MATCHING COURSE NAME");
    show_entry(entry);
  }

	else
	{
		if(task) { delete task; task = NULL; }
		task = new Task;

		if(task->add(entry) == 0)
		{
			error("NOT ENOUGH FIELDS");
      show_entry(entry);
		}

		else
		{
      // get course name and check against existing courses
      instr("Confirm add...");
			task->disp_one();

			if(confirm())
			{
				if(data.write_one_task(entry, 0) == 0)
					error("File not found, task not written to file.");
				else
				{
					success("Task saved and written to file.");
				}
			}
			else
				error("TASK NOT SAVED");
		}
	}
	if(task) { delete task; task = NULL; }
}

void Edit::
action(char *& entry, Data & data)
{ 
}

void Help::
action(char *& entry, Data & data)
{ 
	generic();
}

void Help::
generic()
{
	cout
	<< "\e[1mBASIC COMMANDS:\e[0m\n"
	<< "   (a)dd, (e)dit, (r)emove, (c)omplete, (h)elp, (q)uit\n"
	<< "\e[1mHELP COMMANDS:\e[0m\n"
	<< "   'add', 'edit' 'format' ";
}
