#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {

    string pos_name;
    vector<int> skill_pref;
    vector<string> pos_skills;
    string skill;
    string pref;
    int skillCounter = 0;
    string userChoice;
    string jobFileName;
    ofstream jobFile;
    string resumeFileName;
    string line;
    int lineCounter = 0;
    string currentWord;
    int spaceCounter = 0;

    cout << "Options:" << endl << "a. Make a Job File" << endl << "b. Choose a Job File" << endl;
    cout << "Choose an option:";
    getline(cin, userChoice);

    while(toupper(userChoice[0]) != 'A' and toupper(userChoice[0]) != 'B'){
        cout << "Choose a valid option: ";
        getline(cin, userChoice);
    }

    switch(toupper(userChoice[0])) {
        case 'A':
            cout << "Enter the name of the position: ";
            getline(cin, pos_name);

            cout << "Enter a skill required for the position: ";
            getline(cin, skill);

            do {

                skillCounter++;

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

        case 'B':
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


    cout << "Enter the file name of the resume (Ex: resume.txt):";
    getline(cin, resumeFileName);

    resumeFileName = "resumes\\" + resumeFileName;

    fstream resumeFile(resumeFileName);

    while(resumeFile.fail()){
        cout << "Enter a valid file name (Ex: resume.txt):";
        getline(cin, resumeFileName);
        resumeFileName = "resumes\\" + resumeFileName;
        resumeFile.open(resumeFileName);
    }

    return 0;
}
