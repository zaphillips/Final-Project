#include "Interface.h"

//public:
Interface::Interface(){};

void Interface::getJobInfo(){
    std::cout << "Options:" << std::endl << "1. Make a Job File" << std::endl << "2. Choose a Job File" << std::endl;
    std::cout << "Choose an option:";
    getline(std::cin, userChoice);

    while(userChoice != "1" and userChoice != "2"){
        std::cout << "Choose a valid option: ";
        getline(std::cin, userChoice);
    }

    switch(userChoice[0]) {
        case '1':
            std::cout << "Enter the name of the position: ";
            getline(std::cin, pos_name);

            std::cout << "Enter a skill required for the position: ";
            getline(std::cin, skill);

            do {

                std::cout << "Enter the preference score for that skill (1-10): ";
                getline(std::cin, pref);

                while (stoi(pref) < 1 or stoi(pref) > 10) {
                    std::cout << "Enter a valid preference score (1-10): ";
                    getline(std::cin, pref);
                }

                pos_skills.push_back(skill);
                skill_pref.push_back(stoi(pref));

                std::cout << "Enter a skill required for the position (Enter 0 when you finish): ";
                getline(std::cin, skill);

            } while (skill != "0");

            jobFileName = "jobs\\" + pos_name + ".txt";

            jobFile.open(jobFileName);

            jobFile << "Position Name: " << pos_name << std::endl;

            for (int j = 0; j < pos_skills.size(); j++) {
                jobFile << "Skill: " << pos_skills[j] << std::endl << "Preference: " << std::to_string(skill_pref[j]) << std::endl;
            }

            jobFile.close();
            break;

        case '2':
            std::cout << "Enter the name of the job file (Ex: job.txt): ";
            getline(std::cin, jobFileName);
            jobFileName = "jobs\\" + jobFileName;

            std::fstream jobFileRead(jobFileName);

            while(jobFileRead.fail()){
                std::cout << "Enter a valid file name (Ex: job.txt): ";
                getline(std::cin, jobFileName);
                jobFileName = "jobs\\" + jobFileName;
                jobFileRead.open(jobFileName);
            }

            while (getline(jobFileRead, line)){
                ++lineCounter;
                currentWord = {};
                if(lineCounter == 1){
                    for(char chr: line){
                        if(spaceCounter == 2){
                            currentWord += chr;
                        }
                        if(chr == ' '){
                            ++spaceCounter;
                        }
                    }
                    pos_name = currentWord;
                    spaceCounter = 0;
                }
                else{
                    for(char chr: line){
                        if (spaceCounter == 1){
                            currentWord += chr;
                        }
                        if (chr == ' ') {
                            ++spaceCounter;
                        }
                    }
                    spaceCounter = 0;
                    if(lineCounter%2 == 0){
                        pos_skills.push_back(currentWord);
                    }
                    else{
                        skill_pref.push_back(stoi(currentWord));
                    }
                }

            }
            std::cout << "Position Name: " << pos_name << std::endl;
            for(int k = 0; k < pos_skills.size(); k++){
                std::cout << "Skill: " << pos_skills[k] << "\tPreference: " << skill_pref[k] << std::endl;
            }
            break;
    }
}

void Interface::getResumeInfo() {
    std::cout << "Enter the file name of a resume (Ex: resume.txt):";
    getline(std::cin, resumeFileName);

    resumeFileName = "resumes\\" + resumeFileName;

    do {

        resumeFile.open(resumeFileName);

        while (resumeFile.fail()) {
            std::cout << "Enter a valid file name (Ex: resume.txt):";
            getline(std::cin, resumeFileName);
            resumeFileName = "resumes\\" + resumeFileName;
            resumeFile.open(resumeFileName);
        }

        resumeFile.close();

        resumeFileNameVector.push_back(resumeFileName);

        std::cout << "Enter the file name of a resume (q to quit):";
        getline(std::cin, resumeFileName);

        resumeFileName = "resumes\\" + resumeFileName;


    }while(resumeFileName != "resumes\\q" and resumeFileName != "resumes\\Q");
}

