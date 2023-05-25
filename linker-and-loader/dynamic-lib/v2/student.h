#pragma once

#include <ostream>
#include <string>

static const std::string VERSION = "1.0.0";

struct Student {
    static constexpr double QUALIFIED_SCORE = 85;

    void update(const std::string& name, int grade_, double score_);

    void upgrade();
    friend std::ostream& operator<<(std::ostream& out, const Student& student);

    std::string name;
    int grade;
    double score;
};
