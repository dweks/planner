#include "util.h"
Util::Util() { }

Util::~Util(){}
void Util::pg_title(const char text[], const char ch)
{
	int len = strlen(text);

	cout << endl << "┌";
	line(ch, MAXWIDTH - 2, false);
	cout << "┐\n│ " ; center(text, false);
	spacer(((MAXWIDTH - len) / 2) - (len % 2 == 0 ? 2:1));
	cout << "│\n└";
	line(ch, MAXWIDTH - 2, false);
	cout << "┘" << endl;
}

void Util::line(char ch, int len, bool own_line) const
{
	if(own_line)
		cout << endl;
	for(int i = 0; i < len; ++i)
		cout << ch;
	if(own_line)
		cout << endl;
}

void Util::spacer(int len)
{
	for(int i = 0; i < len; ++i)
		cout << ' ';
}

void Util::cpy_str(char *& dest, char source[], int offset)
{
	dest = new char[strlen(source + offset) + 1];
	strcpy(dest, source + offset);
}

void Util::center(const char to_center[], bool own_line) 
{
	int len = strlen(to_center);
	if(len % 2 != 0)
		++len;
	
	if(own_line) 
		cout << endl;
	spacer((MAXWIDTH - len) / 2 - 1);
	cout << to_center;
	if(own_line) 
		cout << endl;
}

void Util::header(const char text[], const char ch)
{
	int offset = 0;
	int len = strlen(text);
	if(len % 2 == 0)
		offset = 3;
	else
		offset = 2;
	cout << endl;
	line(ch, (MAXWIDTH - len - 4) / 2, false);
	cout << "[ " << text << " ]";
	line(ch, (MAXWIDTH - len - offset) / 2, false);
	cout << endl;
}

bool Util::confirm()
{
	char choice;
	bool done = true;

	do
	{
		choice = '\0';
		cout << "\ny/n > ";
		cin >> choice;
		cin.ignore(100, '\n');
		choice = tolower(choice);
		if(choice != 'y' && choice != 'n')	
		{
			error("Invalid input. Enter y or n.");
			done = false;
		}
		else
			done = true;
	} while(!done);

	if(choice == 'y')
		return true;
	return false;
}

void Util::ralign(const char test_msg[])
{
	cout << endl;
	spacer(MAXWIDTH - strlen(test_msg));
	cout << test_msg << endl;
}

void Util::error(const char err_msg[])
{
	cerr <<"\n\033[1;31m × \033[0m" << err_msg << endl;
}

void Util::success(const char succ_msg[])
{
	cout <<"\n\033[1;32m ✓ \033[0m" << succ_msg << endl;
}
