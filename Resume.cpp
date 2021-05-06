//
// Created by zaphi on 5/3/2021.
//

#include "Resume.h"

//public:

Resume::Resume()= default;

void Resume::calcSkillPercents(Job &myJob) {
    std::string tempFileName = "resumes\\" + fileName;
    std::fstream resumeFile;
    std::string line;
    resumeFile.open(tempFileName);
    double skillPoint;
    for(int k = 0; k < myJob.pos_skills.size(); k++) {

        skillPoint = 0;

        std::string SKILL = myJob.pos_skills[k];
        std::transform(SKILL.begin(), SKILL.end(), SKILL.begin(), toupper);

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

        resumeFile.clear();
        resumeFile.seekg(0, std::ios::beg);
    }
    resumeFile.close();
}

void Resume::calcSoftSkillScore(){
    std::string tempFileName = "resumes\\" + fileName;
    std::fstream resumeFile;
    std::string line;

    resumeFile.open(tempFileName);

    while(getline(resumeFile, line)){
        for(std::string skills : softSkills) {
            std::transform(line.begin(), line.end(), line.begin(), toupper);
            auto found = line.find(skills);
            if (found != std::string::npos)
                softSkillScore += 0.1;
        }
    }
    resumeFile.clear();
    resumeFile.seekg(0, std::ios::beg);
    resumeFile.close();
}

void Resume::getCandidateName(){ //Only works if candidate name is first line of file.
    std::string tempFileName = "resumes\\" + fileName;
    std::fstream resumeFile;
    std::string line;

    resumeFile.open(tempFileName);

    getline(resumeFile, candidateName);

    resumeFile.clear();
    resumeFile.seekg(0, std::ios::beg);
    resumeFile.close();
}

void Resume::scanForJob(Job &myJob){
    std::string tempFileName = "resumes\\" + fileName;
    std::fstream resumeFile;
    std::string line;
    std::string POS_NAME = myJob.pos_name;

    std::transform(POS_NAME.begin(), POS_NAME.end(), POS_NAME.begin(), toupper);

    resumeFile.open(tempFileName);

    while(getline(resumeFile, line)){
        std::transform(line.begin(), line.end(), line.begin(), toupper);
        auto found = line.find(POS_NAME);
        if (found != std::string::npos)
            jobNameFound = true;
    }
    resumeFile.clear();
    resumeFile.seekg(0, std::ios::beg);
    resumeFile.close();
}

void Resume::calcTotalMatch(){
    double skillPercentAvg = (accumulate(skillMatchPercents.begin(), skillMatchPercents.end(), 0.0))/skillMatchPercents.size();
    totalPercentMatch = (skillPercentAvg + softSkillScore);

    if(jobNameFound == true){
        totalPercentMatch++;
    }
    if(totalPercentMatch > 100)
        totalPercentMatch = 100;
}
