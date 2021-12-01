  /* ret key:
    -
    3 = empty input
    -2 = quit program
    -1 = invalid entry
     0 = entry only
     1 = command only
     2 = command with entry
  */ 

#include "cmd.h"

Command::Command(): cx('s') { } 
Command::~Command() { } 

Interface::
Interface(): CX(NULL), invalid(true)
{
	if(data.is_init())
		init = true;
	else
	{
		if(initialize() == 1)
			data.set_init(true);
		else
			error("INIT NOT SET", "This is the first run of the program.");
	}
}

Interface::
~Interface() { if(CX) { delete CX; CX = NULL; } }

int Command::
get(char tmp_inp[])
{
  int len = 0;
  int ret = 0;
  char cx_sig = toupper(cx);

  // Display current context with cmd prompt
	cout << cx_sig << " - ";
	cin.get(tmp_inp, 50, '\n'); 

  // Handles empty input
  if(cin_fail()) return -3;
	cin.ignore(100,'\n');

	len = strlen(tmp_inp);
	if(len == 0) return -1;

  // Tests for command symbol and checks validity
	if(tmp_inp[0] == '\\') 
  {
    ret = cmd_type(tmp_inp, len);
    if(cx == 'q' && ret != -1) return -2;
  }
	return ret; // return as entry only by default
}

int Command::
cmd_type(char tmp_inp[], int len)
{
  // Invalid: too short for command
  if(len < 2 || len == 3) return -1; 

  if(!is_valid_code(tmp_inp[1])) return -1;
  if(len == 2) 
  {
    cx = tmp_inp[1];
    return 1;
  }

  // Invalid: first character after cmd code is not a space
  if(tmp_inp[2] != ' ') return -1;

  cx = tmp_inp[1];
  return 2;
}

bool Command::
is_valid_code(char to_chk)
{
	for(int i = 0; i < CMDS; ++i)
	{
		if(to_chk == cmd_arr[i])
			return true;
	}
	return false;
}

char Command::
cx_get() { return cx; }

int Interface::
initialize()
{
	char ** course_names = NULL;
	int num_courses;
	bool done = false;

  header("INITIALIZE PROGRAM");
	do
	{
    num_courses = take_course_num();
    course_names = new char*[num_courses];
    
    // Get all course names
    if(take_course_names(course_names, num_courses) == 1)
    {
      // Print courses and confirm
      instr("VERIFY COURSES", "Ensure all course names are accurate.\n");
      for(int i = 0; i < num_courses; ++i)
        cout << endl << i + 1 << "| " << course_names[i];

      cout << endl;
      if(confirm("Is this correct?"))
      {
        done = true;
        data.set_init(true);
      }

      else
      {
        for(int i = 0; i < num_courses; ++i)
        {
          delete [] course_names[i];
          course_names[i] = NULL;
        }
      }
    }
	}while(!done);

	// If file write is successful, delete array, set_init, and return success
	if(data.write_courses_file(course_names, num_courses) == 1)
	{
		success("Files written succesfully.");
    data.create_course_files(course_names, num_courses);
		for(int i = 0; i < num_courses; ++i)
		{
			delete [] course_names[i];
			course_names[i] = NULL;
		}
		return 1;
	}
	return 0;

}

int Interface::
take_course_num()
{
  int num_courses;
  bool done = false;
  do
  {
    instr("Enter number of courses");
    cout << ": ";

    cin >> num_courses;
    cin.ignore(100, '\n');

    if(num_courses > 5)
    {
      warning("ARE YOU SURE?\n");
      cout << "  You entered " << num_courses << " as your number of courses.";
      done = confirm();
    }
    else
      done = true;
   }while(!done);

   return num_courses;
}

int Interface::
take_course_names(char** & names_arr, int num_courses)
{
	char name_entry[8];
  if(num_courses == 0)
  {
    error("NO COURSES TO TAKE", "The num_courses variable is invalid.");
    return 0;
  }

  instr("Name course...\n");
  for(int i = 0; i < num_courses; ++i)
  {
    cout << i + 1 << " > ";
    cin.get(name_entry, 8, '\n');
    cpy_str(names_arr[i], name_entry);
    cin.ignore(100, '\n');
  }
  if(!names_arr[0])
  {
    error("NAMES ARRAY NOT FILLED");
    return 0;
  }
  return 1;
}

// At start of loop
void Interface::
container()
{
	CX = new Context;

	char tmp_inp[INPUT] = "DEFAULT";
	char * entry = NULL;
	char current_cx = 's';

	bool first_run = true;
	bool is_new_cx = false;
	bool quit = false;

  // Show title if first run or new context
	while(!quit)
	{
		if(is_new_cx || first_run)
		{
			CX->disp_title();
			first_run = false;
      is_new_cx = false;
		}

    // Perform context specific action using current entry
    // cx actions designed to handle invalid entry 
    // Skipped if user gives invalid input
    if(!invalid) CX->action(entry, data);

    // Reset invalid until made otherwise
    invalid = false;

    // Delete entry so user can enter another
		if(entry) 
    {
      delete [] entry;
      entry = NULL;
    }

		switch(cmd.get(tmp_inp))
		{
			case -3: invalid = true; break; // Empty entry
			case -2: quit = true; break; // Quit program
			case -1: invalid = true; error("INVALID ENTRY, YOU ENTERED:", tmp_inp); break;
			case 0: cpy_str(entry, tmp_inp, 0); break;
			case 1: is_new_cx = cx_test(current_cx, cmd.cx_get()); break;
			case 2: // Command with entry
			{
				is_new_cx = cx_test(current_cx, cmd.cx_get()); 
				cpy_str(entry, tmp_inp, 3);
			} break;
		}

		if(!quit && is_new_cx)
		{
			if(CX){ delete CX; CX = NULL; }
			cx_switch(CX, current_cx);
		}
	}
}

bool Interface::
cx_test(char & current, const char test)
{
	if(current != test)
	{
		current = test;
		return true;
	}
	return false;

}

void Interface::
cx_switch(Context* & to_set, const char current_cx) 
{
	switch(current_cx)
	{
		case 'a': to_set = new Add(); break;
		case 'h': to_set = new Help(); break;
		case 'v': to_set = new View(); break;
	}
}
