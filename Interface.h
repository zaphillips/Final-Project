#ifndef PROJECT_POSITION_H
#define PROJECT_POSITION_H

#include <iostream>
#include <fstream>
#include <vector>

class Interface{
public:
    std::string pos_name;
    std::vector<int> skill_pref;
    std::vector<std::string> pos_skills;
    std::string skill;
    std::string pref;
    std::string userChoice;
    std::string jobFileName;
    std::ofstream jobFile;
    std::string line;
    int lineCounter = 0;
    std::string currentWord;
    int spaceCounter = 0;
    std::string resumeFileName;
    std::vector<std::string> resumeFileNameVector;
    std::fstream resumeFile;
    Interface();
    void getJobInfo();
    void getResumeInfo();


};


#endif //PROJECT_POSITION_H
