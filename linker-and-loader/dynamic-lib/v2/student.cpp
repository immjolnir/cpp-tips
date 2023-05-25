#include "student.h"



void Student::update(const std::string& name_, int grade_, double score_) {
    name = name_;
    grade = grade_;
    score = score_;
}

void Student::upgrade() {
    if (score > QUALIFIED_SCORE) {
        grade += 1;
    }
}

std::ostream& operator<<(std::ostream& out, const Student& student) {
    out << "Student v2] name=" << student.name << ", grade=" << student.grade << ", score=" << student.score;
    return out;
}
