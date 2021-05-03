#include <iostream>
#include <fstream>
#include <vector>
#include "Interface.h"

using namespace std;

void getJobInfo();
void getResumeInfo();

int main() {

    getJobInfo();
    getResumeInfo();

    return 0;
}

void getJobInfo(){
    string pos_name;
    vector<int> skill_pref;
    vector<string> pos_skills;
    string skill;
    string pref;
    string userChoice;
    string jobFileName;
    ofstream jobFile;
    string line;
    int lineCounter = 0;
    string currentWord;
    int spaceCounter = 0;

    cout << "Options:" << endl << "1. Make a Job File" << endl << "2. Choose a Job File" << endl;
    cout << "Choose an option:";
    getline(cin, userChoice);

    while(userChoice != "1" and userChoice != "2"){
        cout << "Choose a valid option: ";
        getline(cin, userChoice);
    }

    switch(userChoice[0]) {
        case '1':
            cout << "Enter the name of the position: ";
            getline(cin, pos_name);

            cout << "Enter a skill required for the position: ";
            getline(cin, skill);

            do {

                cout << "Enter the preference score for that skill (1-10): ";
                getline(cin, pref);

                while (stoi(pref) < 1 or stoi(pref) > 10) {
                    cout << "Enter a valid preference score (1-10): ";
                    getline(cin, pref);
                }

                pos_skills.push_back(skill);
                skill_pref.push_back(stoi(pref));

                cout << "Enter a skill required for the position (Enter 0 when you finish): ";
                getline(cin, skill);

            } while (skill != "0");

            jobFileName = "jobs\\" + pos_name + ".txt";

            jobFile.open(jobFileName);

            jobFile << "Position Name: " << pos_name << endl;

            for (int j = 0; j < pos_skills.size(); j++) {
                jobFile << "Skill: " << pos_skills[j] << endl << "Preference: " << to_string(skill_pref[j]) << endl;
            }

            jobFile.close();
            break;

        case '2':
            cout << "Enter the name of the job file (Ex: job.txt): ";
            getline(cin, jobFileName);
            jobFileName = "jobs\\" + jobFileName;

            fstream jobFileRead(jobFileName);

            while(jobFileRead.fail()){
                cout << "Enter a valid file name (Ex: job.txt): ";
                getline(cin, jobFileName);
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
            cout << "Position Name: " << pos_name << endl;
            for(int k = 0; k < pos_skills.size(); k++){
                cout << "Skill: " << pos_skills[k] << "\tPreference: " << skill_pref[k] << endl;
            }
            break;
    }
}

void getResumeInfo(){
    string resumeFileName;
    vector<string> resumeFileNameVector;
    fstream resumeFile;

    cout << "Enter the file name of a resume (Ex: resume.txt):";
    getline(cin, resumeFileName);

    resumeFileName = "resumes\\" + resumeFileName;

    do {

        resumeFile.open(resumeFileName);

        while (resumeFile.fail()) {
            cout << "Enter a valid file name (Ex: resume.txt):";
            getline(cin, resumeFileName);
            resumeFileName = "resumes\\" + resumeFileName;
            resumeFile.open(resumeFileName);
        }

        resumeFile.close();

        resumeFileNameVector.push_back(resumeFileName);

        cout << "Enter the file name of a resume (q to quit):";
        getline(cin, resumeFileName);

        resumeFileName = "resumes\\" + resumeFileName;


    }while(resumeFileName != "resumes\\q" and resumeFileName != "resumes\\Q");
}