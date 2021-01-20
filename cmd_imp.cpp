#include "cmd.h"
Command::Command(): cx('s') { } 
Command::~Command() { } 
Interface::Interface(): CX(NULL)
{
	if(file.is_init() == true)
		init = true;
	else
	{
		if(initialize() == 1)
		{
			ralign("initialize() == 1");
			file.set_init(true);
		}
		else
			error("INIT NOT SET");
	}
}
Interface::~Interface() 
{ 
	if(CX) { delete CX; CX = NULL; } 
}

int Command::get(char tmp_inp[])
{
	cout << endl << "|" << cx << "|› ";
	cin.get(tmp_inp, 50, '\n'); 
	cin.ignore(100,'\n');
	int len = strlen(tmp_inp);

	// Test correct command input
	if(len == 0)
		return -1;

	if(tmp_inp[0] == '\\') 
	{ 
		if(len < 2) 
			return -1; 
		if(len == 2)
		{
			// Run through array to check for valid command
			if(!chk_type(tmp_inp[1])) 
				return -1; 

			// Set context if valid command
			if(cx == 'q')
				return -2;

			cx = tmp_inp[1];
			return 1;
		}
		if(tmp_inp[2] != ' ' || len == 3)
			return -1;

		cx = tmp_inp[1];
		return 2;
	}
	// Test correct entry input

	return 0; // return as entry only by default
}

bool Command::chk_type(char to_chk)
{
	for(int i = 0; i < CMDS; ++i)
	{
		if(to_chk == cmd_arr[i])
			return true;
	}
	return false;
}

char Command::cx_get() { return cx; }

int Interface::initialize()
{
	char ** course_names;
	int num_course;
	char name_entry[7];
	bool done = false;

	do
	{
		cout 
		<< "FIRST RUN OF PROGRAM\n"
		<< "Enter number of courses: ";

		cin >> num_course;
		cin.ignore(100, '\n');

		course_names = new char*[num_course];
		
		// Get all course names
		for(int i = 0; i < num_course; ++i)
		{
			cout << "Enter course " << i + 1 << ": ";
			cin.get(name_entry, 7, '\n');
			cpy_str(course_names[i], name_entry);
			cin.ignore(100, '\n');
		}
		// Print courses and confirm
		for (int i = 0; i < num_course; ++i)
			cout << "Course " << i + 1 << ": " << course_names[i] << endl;

		cout << "\nCorrect?";
		if(confirm())
			done = true;
		else
		{
			for(int i = 0; i < num_course; ++i)
			{
				delete [] course_names[i];
				course_names[i] = NULL;
			}
		}
	}while(!done);

	// If file write is successful, delete array, set_init, and return success
	if(file.write_courses(course_names, num_course) == 1)
	{
		success("Files written succesfully.");
		for(int i = 0; i < num_course; ++i)
		{
			delete [] course_names[i];
			course_names[i] = NULL;
		}
		return 1;
	}
	return 0;

}
void Interface::container()
{
	CX = new Context;

	char tmp_inp[INPUT] = "DEFAULT";
	char * entry = NULL;
	char current_cx = 's';
	char test_cx = '-';

	bool first_run = true;
	bool new_cx = false;
	bool quit = false;

	while(!quit)
	{
		if(new_cx || first_run)
		{
			CX->disp_title();
			first_run = false;
		}

		CX->action(entry, data);
		if(entry) { delete [] entry; entry = NULL; }

		switch(cmd.get(tmp_inp))
		{
			case -2: quit = true; break;

			case -1: // Invalid
			{
				error("Invalid entry. ");
				cout << "You entered: '" << tmp_inp << "'\n";
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

bool Interface::cx_test(char &current, const char test)
{
	if(current != test)
	{
		current = test;
		return true;
	}
	return false;

}

void Interface::cx_switch(Context *& to_set, const char current_cx) 
{
	switch(current_cx)
	{
		case 'a': to_set = new Add(); break;
		case 'e': to_set = new Edit(); break;
		case 'h': to_set = new Help(); break;
	}
}
