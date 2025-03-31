#include "teacher.hpp"


int main()
{
	setlocale(LC_ALL, "Rus");
	Teacher teacher;

	teacher.input_n_reading("tasks.txt");
	teacher.open_n_read("students.txt");
	teacher.create_queue();
	teacher.make_answers();
	teacher.check_works();
	teacher.publish_results();

	return 0;
}
