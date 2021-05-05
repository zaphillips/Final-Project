//
// Created by zaphi on 5/3/2021.
//

#include "Resume.h"

//public:

Resume::Resume()= default;

void Resume::calcSkillPercents(Job myJob) {
    for(int k = 0; k < myJob.pos_skills.size(); k++) {
        double skillPoint = 0;
        fileName = "resumes\\" + fileName;
        std::fstream resumeFile;
        std::string line;
        std::string SKILL = myJob.pos_skills[k];
        std::transform(SKILL.begin(), SKILL.end(), SKILL.begin(), toupper);

        resumeFile.open(fileName);

        while (getline(resumeFile, line)) {
            std::transform(line.begin(), line.end(), line.begin(), toupper);
            auto found = line.find(SKILL);
            if (found != std::string::npos)
                skillPoint += 2;
        }
        if(skillPoint == 0)
            skillMatchPercents.push_back(0);
        else if(skillPoint >= myJob.skill_prefs[k])
            skillMatchPercents.push_back(100);
        else
            skillMatchPercents.push_back((skillPoint/myJob.skill_prefs[k]) * 100);
    }

}

void Resume::calcSoftSkillScore(){
    fileName = "resumes\\" + fileName;
    std::fstream resumeFile;
    std::string line;

    resumeFile.open(fileName);

    while(getline(resumeFile, line)){
        for(std::string skills : softSkills) {
            std::transform(line.begin(), line.end(), line.begin(), toupper);
            auto found = line.find(skills);
            if (found != std::string::npos)
                softSkillScore += 0.1;
        }
    }
}
