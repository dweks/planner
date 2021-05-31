#include "cmd.h"

Command::Command(): cx('s') { } 
Command::~Command() { } 

Interface::Interface(): CX(NULL)
{
	if(data.is_init())
		init = true;
	else
	{
		if(initialize() == 1)
			data.set_init(true);
		else
			error("INIT NOT SET");
	}
}
Interface::~Interface() 
{ 
  ralign("DELETING CX");
	if(CX) { delete CX; CX = NULL; } 
}

int Command::
get(char tmp_inp[])
{
  /* ret key:
    -3 = empty input
    -2 = quit program
    -1 = invalid entry
     0 = entry only
     1 = command only
     2 = command with entry
  */ 
  int len = 0;
  int ret = 0;
  char cx_sig = toupper(cx);

	cout << endl << "|" << cx_sig << "|› ";
	cin.get(tmp_inp, 50, '\n'); 
  if(cin.fail())
  {
    cin.clear();
    cin.ignore(100,'\n');
    return -3;
  }

	cin.ignore(100,'\n');

	len = strlen(tmp_inp);
	if(len == 0) return -1;

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
  // invalid: too short for command
  if(len < 2 || len == 3) return -1; 

  if(!is_valid_code(tmp_inp[1])) return -1;
  if(len == 2) 
  {
    cx = tmp_inp[1];
    return 1;
  }
  // invalid: first character after cmd code is not a space
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
	char name_entry[8];
	bool done = false;

  header("INITIALIZE PROGRAM");
	do
	{
    instr("Enter number of courses");
    cout << " > ";

		cin >> num_courses;
		cin.ignore(100, '\n');

		course_names = new char*[num_courses];
		
		// Get all course names
    instr("Name course...");
		for(int i = 0; i < num_courses; ++i)
		{
      cout << i + 1 << " > ";
			cin.get(name_entry, 8, '\n');
			cpy_str(course_names[i], name_entry);
			cin.ignore(100, '\n');
		}

		// Print courses and confirm
    instr("Verify entries");
		for (int i = 0; i < num_courses; ++i)
			cout << i + 1 << ": " << course_names[i] << endl;

		cout << "\nCorrect?";
		if(confirm())
			done = true;
		else
		{
			for(int i = 0; i < num_courses; ++i)
			{
				delete [] course_names[i];
				course_names[i] = NULL;
			}
		}

	}while(!done);

	// If file write is successful, delete array, set_init, and return success
	if(data.write_courses(course_names, num_courses) == 1)
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

void Interface::
container()
{
	CX = new Context;

	char tmp_inp[INPUT] = "DEFAULT";
	char * entry = NULL;
	char current_cx = 's';
	char test_cx = '-';

	bool first_run = true;
	bool new_cx = false;
	bool quit = false;

  // Main program loop
	while(!quit)
	{
		if(new_cx || first_run)
		{
			CX->disp_title();
			first_run = false;
		}

		CX->action(entry, data);

		if(entry) 
    { 
      delete [] entry; 
      entry = NULL; 
    }

		switch(cmd.get(tmp_inp))
		{
			case -3: break;
			case -2: quit = true; break;

			case -1: // Invalid
			{
				error("INVALID ENTRY");
        show_entry(tmp_inp);
				new_cx = false;
			} break;

			case 0: // Entry only
			{ 
				cpy_str(entry, tmp_inp, 0); 
				new_cx = false;
			} break;

			case 1: // Command only
			{ 
				test_cx = cmd.cx_get();
				new_cx = cx_test(current_cx, test_cx); 
			} break;

			case 2: // Command with entry
			{
				test_cx = cmd.cx_get();
				new_cx = cx_test(current_cx, test_cx); 
				cpy_str(entry, tmp_inp, 3);
			} break;
		}

		if(!quit && new_cx)
		{
			if(CX){ delete CX; CX = NULL; }
			cx_switch(CX, current_cx);
		}
	}
}

bool Interface::
cx_test(char &current, const char test)
{
	if(current != test)
	{
		current = test;
		return true;
	}
	return false;

}

void Interface::
cx_switch(Context *& to_set, const char current_cx) 
{
	switch(current_cx)
	{
		case 'a': to_set = new Add(); break;
		case 'e': to_set = new Edit(); break;
		case 'h': to_set = new Help(); break;
	}
}
