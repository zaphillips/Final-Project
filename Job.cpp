#include "Job.h"

//public:
Job::Job(std::string pos_name, std::vector<std::string> pos_skills, std::vector<int> skill_prefs){
    this->pos_name = pos_name;
    this->pos_skills = pos_skills;
    this->skill_prefs = skill_prefs;
}

std::ostream &operator<<(std::ostream &os, const Job &jobs) {
    std::string output = "Position Name: " + jobs.pos_name;
    for(int i = 0; i < jobs.pos_skills.size(); i++){
        output.append("\nSkill: " + jobs.pos_skills[i] + "\tPreference: " + std::to_string(jobs.skill_prefs[i]));
    }
    os << output;
    return os;
}


