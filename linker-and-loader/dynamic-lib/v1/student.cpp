#include "student.h"


void Student::update(int grade_, double score_) {
    grade = grade_;
    score = score_;
}

void Student::upgrade() {
    if (score > QUALIFIED_SCORE) {
        grade += 1;
    }
}

std::ostream& operator<<(std::ostream& out, const Student& student) {
    out << "Student v1] grade=" << student.grade << ", score=" << student.score;
    return out;
}