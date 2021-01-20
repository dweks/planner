#include "util.h"
///#include "characterinterface.h"

// DeCon

Interface::Interface(){}
Util::Util(): lineLen(50){}

// 'Util' implementations - Utility functions for entire program. //

/* menuChoice
Interacts with user to direct switch-based menus.
Argument 'max' should correspond with the last menu option displayed.
Entering 0 serves as a "return to home page" option for all menus.
User cannot proceed without entering a number between 0 and max.
*/

int Util::menuChoice(int max)
{
	bool goodInput = false;
	int choice = 0;

	do
	{
		cout << "\nEnter choice > ";
		cin >> choice; cin.ignore();

		if(choice < 0 || choice > max)
		{
			cout 
			<< "(!) Please enter an number between 1 and " << max << ", or \n"
			<< "    enter 0 to return to the main menu.\n";
			goodInput = false;
		}
		else
			goodInput = true;

	}while(goodInput == false);

	return choice;
}
/* title Builds main page titles using line() and passed string arg.
*/ 

void Util::title(const char text[], const char lineChar[]) 
{
	int textLength = strlen(text);

	cout << endl << "┌";
	line(lineChar, lineLen - 2, false);
	cout << "┐\n│ " ; center(text, false);
	spacer(((lineLen - textLength) / 2) - (textLength % 2 == 0 ? 2:1));
	cout << "│\n└";
	line(lineChar, lineLen - 2, false);
	cout << "┘" << endl;
}

/* header
A stylized container for a generic header.
The first passed string will be the header header, followed
by the second argument as the body.
*/
void Util::header(const char msgHead[], const char lineChar[])
{
	cout << endl;
	line("-", (lineLen - strlen(msgHead) - 4) / 2, false);
	cout << "[ " << msgHead << " ]";
	line("-", (lineLen - strlen(msgHead) - 2) / 2, false);
	cout << endl;
}

/* center
Centers passed string relative to the lineLen constant.
The ownLine argument will put centered text on its own
line if true.
*/
void Util::center(const char centerText[], bool ownLine)
{
	int textLength= strlen(centerText);
	if(textLength % 2 != 0)
		++textLength;
	
	if(ownLine) 
		cout << endl;
	spacer((lineLen - textLength) / 2 - 1);
	cout << centerText;
	if(ownLine) 
		cout << endl;
}

/* line
Prints a line primarily for readability.
By default, the line will print with character '=' 50 times.
The character and length can be changed by passing variables or strings.
Note that new lines occur on either side of the line within this funciton
by default but can be changed by passing false as an arg.
*/

void Util::line(const char lineChar[], int lineLen, bool ownLine)
{
	if(ownLine)
		cout << endl;
	for(int i = 0; i < lineLen; ++i)
		cout << lineChar;
	if(ownLine)
		cout << endl;
}

/* spacer
Adds space depending on the passed integer.
*/

void Util::spacer(int spaceLen)
{
	for(int i = 0; i < spaceLen; ++i)
		cout << ' ';
}

/* confirm
For any occasion that requires user confirmation of an action.
Note that anything entered besides a 'y' or 'Y' will return false.
*/

bool Util::confirm()
{
	char answer = '\0';

	cout << "\nEnter Y or N > ";
	cin >> answer; cin.ignore(100, '\n');

	if(toupper(answer) == 'Y')
		return true;
	
	return false;
}

/* pause
For occasions when significant on-screen info could be overridden.
*/

void Util::pause()
{
	center("[ Press ENTER to continue ]");
	cin.ignore();
}

// 'Interface' implementations - The "pages" where main game functionality occurs.

void Interface::home()
{
	bool quit = false;

	do
	{
		title("PAGE TITLE");
		title("Info box","—");
		title("123");
		title("1234");
		title("12345");
		header("WELCOME");

		cout
		<< "Choose from the following menu: \n\n"
		<< "   [1] Begin combat\n"
		<< "   [2] View player stats\n"
		<< "   [3] Erase all data\n"
		<< "   [4] Quit\n";
		
		switch(menuChoice(4))
		{
			case 1: pagePlay(); break;
			case 2: pageDisplay(); break;
			case 3: pageErase(); break;
			case 4: quit = true; break;
		}

	}while(quit == false);
}

void Interface::pagePlay()
{
	title("BEGIN THE FIGHT");
	pause();
	confirm();
}

void Interface::pageDisplay()
{
	title("DISPLAY ALL PLAYER DATA");
	pause();

}

void Interface::pageErase()
{
	title("ERASE ALL PLAYER DATA");
	pause();
}

