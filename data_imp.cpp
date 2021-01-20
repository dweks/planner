#include "data.h"

int File::write_one(char to_write[])
{
	write.open("files/all_tasks.txt", ios::app);

	if(write)
		write << to_write << '\n';
	write.close();
	if(!write)
		return 0;
	return 1;
}

bool File::is_init()
{
	int init;
	read.open("files/init.txt");
	if(read)
		read >> init;
	read.ignore(100, '\n');
	read.close();
	if(init == 1)
		return true;
	return false;
}

void File::set_init(bool set_to)
{
	if(set_to == true)
	{
		write.open("files/init.txt", ios::trunc);
		if(write)
			write << set_to << '\n';
		write.close();
	}
}

int File::write_courses(char **& all_courses, int num_course)
{
	write.open("files/courses.txt", ios::trunc);
	if(write)
	{
		write << num_course << '\n';
		for(int i = 0; i < num_course; ++i)
			write << all_courses[i] << '\n';
		write.close();
		return 1;
	}
	write.close();
	return 0;
}

Node *& Node::gnext() { return next; }

int Node::set_task(char entry[])
{
	if(task) delete task;
	task = new Task;
	return task->add(entry);
}

void Data::disp_UPC() { UPC->disp(); }

void Node::disp() { task->disp(); }

void Upcoming::disp()
{
	if(!head) return;
	head->disp();
	disp(head->gnext());
}

void Upcoming::disp(Node *& head)
{
	if(head == nullptr) return;
	head->disp();
	return disp(head->gnext());
}

