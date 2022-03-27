#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

#include "libmeeus.h"

void GenVSOPLBR(string filename) {
    VSOPLBR planetLBR;
    ifstream vsopfile(filename);
    string line;
    if (!vsopfile) {
        cout << "could not open file " << filename << endl;
    }

    string dummy;
    int old_variable = 1;
    int terms;
    VSOPterm term;
    vsop_series series_tmp;
    vsop_var tmp;
    while (getline(vsopfile, line)){
        stringstream ss(line);
        int variable;
        ss >> dummy >> dummy >> dummy >> dummy >> dummy >> variable >> dummy >> dummy >> terms;
        cout << "var=" << variable << ", terms=" << terms << endl;
        series_tmp.clear();
        for (int i=0; i<terms; i++) {
            getline(vsopfile, line);
            ss.str(line.substr(80));
            ss >> term.A >> term.B >> term.C;
            series_tmp.push_back(term);
        }
        if (old_variable == variable) {
            tmp.push_back(series_tmp);
        } else {
            switch (old_variable) {
            case 1: planetLBR.L=tmp;
                break;
            case 2: planetLBR.B=tmp;
                break;
            default: cout << "error";
                break;
            }
            old_variable = variable;
            tmp.clear();
            tmp.push_back(series_tmp);
        }
    }
    // only when while(getline()) is finished, the last var, R, is completey read.
    // That's also why switch above only goes to 2
    planetLBR.R=tmp;
}

#include "../VSOP87D_earth.h"

int main()
{
    cout << endl << "Generate VSOP87 Earth" << endl;
    struct VSOPLBR planetLBR;
    string filename("/home/ginovh/Programming/astro/VI_81/VSOP87D.ear");
    getVSOPLBR(filename, planetLBR);

    return 0;
}
