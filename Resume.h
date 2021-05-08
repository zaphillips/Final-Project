#ifndef PROJECT_RESUME_H
#define PROJECT_RESUME_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "Job.h"
#include <numeric>
#include <cmath>

class Resume {
public:
    std::string fileName;
    std::string candidateName;
    Resume();
    void getCandidateName();
    void calcSkillPercents(Job&);
    std::vector<double> skillMatchPercents;
    double totalPercentMatch = 0;
    std::vector<std::string> softSkills = {"COMMUNICATION", "PROBLEM-SOLVING", "TIME MANAGEMENT", "COLLABORATION", "LEADERSHIP", "WORK ETHIC", "MULTITASKING", "HARD-WORKING"};
    double softSkillScore = 0;
    void calcSoftSkillScore();
    void scanForJob(Job&);
    bool jobNameFound;
    void calcTotalMatch();
};


#endif //PROJECT_RESUME_H
