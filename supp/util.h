#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

class Util
{
	public:
		Util();
	
	protected:
		// For any numerical menu choice with varying options
		int menuChoice(int max);
		// Template for 'page' titles
		void title(const char text[], const char lineChar[] = "=");
		// Template for generic headers including header header
		void header(const char msgHead[], const char lineChar[] = "-");
		// Centers text own its own line or not
		void center(const char centerText[], bool ownLine = true);
		// Versatile printed line for readability and aesthetics
		void line(const char lineChar[] = "―", int lineLen = 50, bool ownLine = true);
		// Simialr to line() but purely for spacing
		void spacer(int spaceLen);
		// A "yes" or "no" prompt
		bool confirm();
		// Holds screen position for readability
		void pause();
	private:
		// Determines various design outcomes; can be modified in constructor
		const int lineLen;
};

class Interface: public Util
{
	public:
		Interface();
		void home();
		void pagePlay();
		void pageDisplay();
		void pageErase();

	private:
		// What should go here? My thoughts are an object of whatever
		// data structure we'll be using so that anything in the 
		// surrounding menu will be able to make requests to it.
};
