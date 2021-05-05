#include <iostream>
#include <fstream>
#include <vector>
#include "Job.h"
#include "Resume.h"
#include <dirent.h>
using namespace std;

Job getJobInfo();

int main() {
    vector<string> resumeFileNames;
    vector<Resume> resumes;
    Resume myResume;
    DIR *dr;
    struct dirent *en;
    dr = opendir("./resumes");

    //gets file names in the "resumes" file
    if (dr){
        while((en = readdir(dr)) != nullptr){
            resumeFileNames.push_back(en->d_name);
        }
        closedir(dr);
    }

    //erases invalid file names in resumeFileNames vector
    for (int res = 0; res < resumeFileNames.size(); res++){
        auto it = resumeFileNames.begin() + res;
        auto found = resumeFileNames[res].find(".txt");
        if(found == string::npos) {
            resumeFileNames.erase(it);
            res = -1;
        }
    }

    //gets job position name/skills/preferences from user (either choosing a file or creating one)
    Job myJob = getJobInfo();

    //Creates Resume class object for each resume file in the "resumes" folder
    for(int j = 0; j < resumeFileNames.size(); j++){
        myResume.fileName = resumeFileNames[j];
        resumes.push_back(myResume);
        myResume = {};
    }

    //TODO: Implement name finder, implement Education/Job Name calculations, implement total match calculations, implement file appending, print out results (in order based on % match), make program bullet-proof.
    //TODO (if time): Implement experience year scanner, implement job type variable (intern, full-time/part-time, etc.), implement name finder, adjust calculations.

    return 0;
}

Job getJobInfo(){
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

    cout << "Options:\n1. Create a Preference File\n2. Choose a Preference File";
    cout << "\nChoose an option:";
    getline(cin,userChoice);

    while(userChoice != "1" and userChoice != "2"){
        cout << "Choose a valid option:";
        getline(cin, userChoice);
    }

    switch(userChoice[0]) {
        case '1':
            cout << "Enter the name of the position: ";
            getline(cin, pos_name);

            cout << "Enter a skill required for the position:";
            getline(cin, skill);

            do {
                cout << "Enter the preference score for that skill (1-10):";
                getline(cin, pref);

                while (stoi(pref) < 1 or stoi(pref) > 10) {
                    cout << "Enter a valid preference score (1-10):";
                    getline(cin, pref);
                }

                pos_skills.push_back(skill);
                skill_pref.push_back(stoi(pref));

                cout << "Enter a skill required for the position (Enter 0 when you finish):";
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
            cout << "Enter the name of the job file (Ex: job.txt):";
            getline(cin, jobFileName);
            jobFileName = "jobs\\" + jobFileName;

            fstream jobFileRead(jobFileName);

            while(jobFileRead.fail()){
                cout << "Enter a valid file name (Ex: job.txt):";
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
    Job job1(pos_name, pos_skills, skill_pref);
    return job1;
}