#include "cx.h"
Context::Context() { }
Context::~Context() {}

Add::Add(){}
Add::~Add(){}

View::View() {}
View::~View() {}

Edit::Edit() {}
Edit::~Edit() {}

Help::Help() {}
Help::~Help() {}

void Context::disp_title() { header(cx_title); }
void Add::disp_title() { header(cx_title); }
void View::disp_title() { header(cx_title); }
void Edit::disp_title() { header(cx_title); }
void Help::disp_title() { header(cx_title); }

void Context::
action(char* & entry, Data & data) 
{
}

void Add::
action(char* & entry, Data & data) 
{ 
  bool cont = true;
  int course = -1;

	if(!entry)
    instr("ENTER NEW TASK", "Format: course|title|type|name|");

	else 
	{
    Task task;

    switch(task.add(entry))
    {
      case -1: error("NO ENTRY TO PARSE"); cont = false; break;
      case 0: error("INVALID FORMAT, YOU ENTERED:", entry); cont = false; break;
      case 1: cont = true; break;
    }

		if(cont)
		{
      // Get course name and check against existing courses
      course = data.verify_course_name(entry);

      if(course == -1)
        error("CANNOT FIND COURSE, CHECK ENTRY:", entry);
      else
      {
        instr("Confirm addition...");
        task.disp_one();

        if(confirm("Is this correct?"))
        {
          if(data.write_one_task(entry) == 0)
            error("FILE NOT FOUND", "Task not written to file.");
          else
          {
            data.add_one_task(task, course);
            success("TASK SAVED", "Task data is written to file.");
          }
        }
        else
          warning("TASK NOT SAVED", "No new task data has been written.");
      }
		}
	}
}

void View::
action(char* & entry, Data & data) 
{
  // intro: list all things that can be viewed
  // or upcoming as default + list?
  // choosing one without options defaults to certain view
  // ideas:
  //    courses: just names;  
  //    settings: 
  //    tasks: completed, upcoming
  //    
	if(!entry)
    instr("Choose what to view");
  else
    disp_view_options();

  data.disp_course_tasks();
}

void View::
disp_view_options()
{
  cout
  << "(T)asks: (a)ll, (b)y course, (u)pcoming" << endl
  << "(G)eneral: (a)ll, (c)ourses, (y)ear" << endl
  << "(P)rogram: (a)ll, (c)ommands, (o)ptions, (s)ettings" << endl
  ;
}

void Edit::
action(char* & entry, Data & data) { }

void Help::
action(char* & entry, Data & data) { generic(); }

void Help::
generic()
{
	cout
	<< "\e[1mBASIC COMMANDS:\e[0m\n"
	<< "   (a)dd, (e)dit, (r)emove, (c)omplete, (h)elp, (q)uit\n"
	<< "\e[1mHELP COMMANDS:\e[0m\n"
	<< "   'add', 'edit' 'format' ";
}
