//
// Created by zaphi on 5/3/2021.
//

#ifndef PROJECT_RESUME_H
#define PROJECT_RESUME_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "Job.h"

class Resume {
public:
    std::string fileName;
    Resume();
    void calcSkillPercents(Job);
    std::vector<double> skillMatchPercents;
    double totalPoints = 0;
    std::vector<std::string> softSkills = {"COMMUNICATION", "PROBLEM-SOLVING", "TIME MANAGEMENT", "COLLABORATION", "LEADERSHIP", "WORK ETHIC", "MULTITASKING"};
    double softSkillScore = 0;
    void calcSoftSkillScore();

};


#endif //PROJECT_RESUME_H
