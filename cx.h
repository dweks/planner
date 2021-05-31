#include "data.h"

class Context: public Util 
{
	public:
		Context();
		virtual ~Context();
		virtual void disp_title();
		virtual void action(char *& entry, Data & data);
	private:
		const char cx_title[8] = "Planner";
};

class Add: public Context
{
	public:
		Add();
		~Add();
		void disp_title();
		void action(char *& entry, Data & data);

	private:
		const char cx_title[4] = "Add";
		Task * task;
};

class Edit: public Context
{
	public:
		Edit();
		~Edit();
		void disp_title();
		void action(char *& entry, Data & data);
	private:
		const char cx_title[5] = "Edit";

};

class Help: public Context
{
	public:
		Help();
		~Help();
		void disp_title();	
		void action(char *& entry, Data & data);
		void generic();
	private:
		const char cx_title[5] = "Help";
};
