#include "cx.h"
Context::Context() { }
Context::~Context() {}

Add::Add() {}
Add::~Add() {}

Edit::Edit() {}
Edit::~Edit() {}

Help::Help() {}
Help::~Help() {}

void Context::disp_title() { }
void Add::disp_title() { pg_title(cx_title); }
void Edit::disp_title() { pg_title(cx_title); }
void Help::disp_title() { pg_title(cx_title); }

// CONTEXT
void Context::action(char *& entry, Data & data)
{
	data.disp_UPC();
}

void Add::action(char *& entry, Data & data) 
{ 
	if(!entry)
		cout << "\nEnter new task:";
	else
	{
		if(task) { delete task; task = NULL; }
		task = new Task;

		if(task->add(entry) == 0)
		{
			error("Not enough fields. ");
			cerr << "You entered: " << entry << endl;
		}
		else
		{
			line('.', MAXWIDTH, false);
			center("CONFIRM ADD", true);
			line('.', MAXWIDTH, false);
			cout << endl;
			task->disp();

			if(confirm())
			{
				if(file.write_one(entry) == 0)
					error("File not found, task not written to file.");
				else
				{
					success("Task saved and written to file.");
					data.disp_UPC();
				}
			}
			else
				error("Task not saved.");
				// save to file
		}
	}
	if(task) { delete task; task = NULL; }
}

void Edit::action(char *& entry, Data & data)
{ 
}

void Help::action(char *& entry, Data & data)
{ 
	generic();
}

void Help::generic()
{
	cout
	<< "\e[1mBASIC COMMANDS:\e[0m\n"
	<< "   (a)dd, (e)dit, (r)emove, (c)omplete, (h)elp, (q)uit\n"
	<< "\e[1mHELP COMMANDS:\e[0m\n"
	<< "   'add', 'edit' 'format' ";
}
