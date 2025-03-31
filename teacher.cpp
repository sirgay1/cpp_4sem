#include "teacher.hpp"


Teacher::Teacher() : queue(), students(), answers(), table(), tasks() {}

void Teacher::input_n_reading(const std::string filename) {
	std::ifstream file(filename);
	if (!file) {
		std::cerr << "Ошибка открытия файла!" << std::endl;
		return;
	}

	Quadratic_equations task;

	while (getline(file, task.task)) {
		tasks.push_back(task);
	}

	file.close();
	return;
}

void Teacher::open_n_read(const std::string filename) {
	std::ifstream file(filename);
	if (!file) {
		std::cerr << "Ошибка открытия файла!" << std::endl;
		return;
	}

	std::string type;
	std::string line;
	Student student;

	while (getline(file, line)) {
		std::stringstream ss(line);
		std::string name, surname, characteristic;
		if (ss >> name >> surname >> characteristic) {
			student.name = name + " " + surname;
			if (characteristic == "good") {
				student.type = good;
			}
			else if (characteristic == "mid") {
				student.type = mid;
			}
			else {
				student.type = bad;
			}
			students.push_back(student);
		}
	}

	file.close();

	return;
}

void Teacher::create_queue() {
	for (size_t i = 0; i < students.size(); ++i) {
		Letter str;
		str.student = students[i];
		for (size_t j = 0; j < tasks.size(); ++j) {
			str.task = tasks[j];
			str.roots = solving(&str.task, str.student.type);
			queue.push(str);
		}
	}
}

void Teacher::check_works() {
	Progress_table str;
	for (size_t i = 0; i < students.size(); ++i) {
		str.student = students[i];
		table.push_back(str);
	}

	while (!queue.empty()) {
		for (size_t i = 0; i < table.size(); ++i) {
			if (table[i].student.name == queue.front().student.name) {
				for (size_t j = 0; j < answers.size(); ++j) {
					if (answers[j].task.task == queue.front().task.task) {
						if (answers[j].roots.im1 == queue.front().roots.im1 && answers[j].roots.im2 == queue.front().roots.im2 && answers[j].roots.re1 == queue.front().roots.re1 && answers[j].roots.re2 == queue.front().roots.re2) {
							table[i].count_right_task++;
							break;
						}
					}
				}
				queue.pop();
				break;
			}
		}
	}
}
void Teacher::publish_results() {
	for (size_t i = 0; i < table.size(); ++i) {
		std::cout << table[i].student.name << ": " << table[i].count_right_task << std::endl;
	}
	std::cout << "Результаты опубликованы" << std::endl;
}
void Teacher::make_answers() {
	Answer answer;
	for (size_t i = 0; i < tasks.size(); ++i) {
		answer.task = tasks[i];
		answer.roots = solving(&tasks[i], get_type());
		answers.push_back(answer);
	}
}