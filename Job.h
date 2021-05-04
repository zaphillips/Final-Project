#ifndef PROJECT_POSITION_H
#define PROJECT_POSITION_H

#include <iostream>
#include <fstream>
#include <vector>
#include <ostream>

class Job{
public:
    Job(std::string, std::vector<std::string>, std::vector<int>);
    std::string pos_name;
    std::vector<std::string> pos_skills;
    std::vector<int> skill_prefs;
    friend std::ostream &operator<<(std::ostream &os, const Job &jobs);
    std::vector<std::string> resumeFileNames;
};


#endif //PROJECT_POSITION_H
