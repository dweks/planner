#include "util.h"

Util::Util() { }
Util::~Util(){}

bool Util::
cin_fail()
{
  if(cin.fail())
  {
    cin.clear();
    cin.ignore(100,'\n');
    return true;
  }
  return false;
}

void Util::
pg_title(const char text[], const char ch)
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

void Util::
line(char ch, int len, bool own_line) const
{
	if(own_line) cout << endl;
	for(int i = 0; i < len; ++i)
		cout << ch;
	if(own_line) cout << endl;
}

void Util::
spacer(int len)
{
	for(int i = 0; i < len; ++i)
		cout << ' ';
}

void Util::
cpy_str(char *& dest, char source[], int offset)
{
	dest = new char[strlen(source + offset) + 1];
	strcpy(dest, source + offset);
}

void Util::
center(const char to_center[], bool own_line) 
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

void Util::
header(const char text[], const char ch)
{
	int offset = 0;
	int len = strlen(text);
	if(len % 2 == 0)
		offset = 3;
	else
		offset = 2;
	cout << endl;
	line('=', (MAXWIDTH - len - 4) / 2, false);
	cout << "| " << text << " |";
	line('=', (MAXWIDTH - len - offset) / 2, false);
	cout << endl;
}

bool Util::
confirm(const char msg[])
{
	char choice;
	bool done = true;

  
	do
	{
		choice = '\0';
		cout << "\n\ny/n > ";
		cin >> choice;
		cin.ignore(100, '\n');
		choice = tolower(choice);
		if(choice != 'y' && choice != 'n')	
		{
			error("INVALID ENTRY", "Enter y or n.");
			done = false;
		}
		else
			done = true;
	} while(!done);

	if(choice == 'y')
		return true;
	return false;
}

void Util::
ralign(const char test_msg[])
{
	cout << endl;
	spacer(MAXWIDTH - strlen(test_msg));
	cout << test_msg << endl;
}

void Util::
error(const char msg[], const char sub_msg[])
{
  line(' ');
  cerr << "\033[1;31m—\033[0m " << msg;
  if(strcmp(sub_msg, "") != 0)
    cout << endl << "  " << sub_msg;
  line(' ');
}

void Util::
warning(const char msg[], const char sub_msg[])
{
  line(' ');
  cout << "\033[1;33m!\033[0m " << msg;
  if(strcmp(sub_msg, "") != 0)
    cout << endl << "  " << sub_msg;
  line(' ');
}

void Util::
success(const char msg[], const char sub_msg[])
{
  line(' ');
  cout << "\033[1;32m+\033[0m " << msg;
  if(strcmp(sub_msg, "") != 0)
    cout << endl << "  " << sub_msg;
  line(' ');
}

void Util::
instr(const char msg[], const char sub_msg[]) 
{
  line(' ');
  cout << "\033[1;34m>\033[0m " << msg;
  if(strcmp(sub_msg, "") != 0)
    cout << endl << "  " << sub_msg;
  line(' ');
}

void Util::
get_today(int to_fill[])
{
  using std::atoi;
  const char months[12][4] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

  char parse_month[4] = {};
  char parse_day[6] = {};  

  time_t now = time(0);
  char* full_date = ctime(&now);

  for(int i = 0; i < 3; ++i)
    parse_month[i] = full_date[i + 4];

  for(int i = 0; i < 2; ++i)
    parse_day[i] = full_date[i + 8];

  for(int i = 0; i < 12; ++i)
  {
    if(strcmp(months[i], parse_month) == 0)
    {
      to_fill[0] = i + 1;
      i = 12;
    }
  }

  to_fill[1] = atoi(parse_day);
}

