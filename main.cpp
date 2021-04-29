#include <iostream>
#include <fstream>
#include <vector>
#include "Interface.h"

using namespace std;

int main() {
    Interface UI;

    //UI
    UI.getJobInfo();
    UI.getResumeInfo();

    return 0;
}
