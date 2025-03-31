#ifndef TEACHER_H
#define TEACHER_H

#include "structs.hpp"
#include "funcs.hpp"

#include <queue>
#include <fstream>
#include <vector>


class Teacher {
private:
    Type type = good;

    std::queue <Letter> queue;
    std::vector <Student> students;
    std::vector <Answer> answers;
    std::vector <Progress_table> table;
    std::vector <Quadratic_equations> tasks;

public:
    Teacher();

    Type get_type() {
        return this->type;
    }

    void input_n_reading(const std::string filename);
    void open_n_read(const std::string filename);
    void create_queue();
    void check_works();
    void publish_results();
    void make_answers();

};

#endif
