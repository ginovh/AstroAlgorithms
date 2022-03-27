#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

#include "libmeeus.h"

void GenVSOPLBR(string vsopInputFilename, string headerOutputFilename) {
    VSOPLBR planetLBR;
    ifstream vsopfile(vsopInputFilename);
    if (!vsopfile) {
        cout << "could not open file " << vsopInputFilename << endl;
    }
    ofstream headerfile(headerOutputFilename);
    if (!headerfile) {
        cout << "could not open file " << headerOutputFilename << endl;
    }

    headerfile << "#include \"libmeeus/libmeeus.h\"" << endl;

    string line;
    string dummy;
    int old_variable = 1; // 1:L, 2:B, 3:R
    int terms;
    string degree_of_T;
    VSOPterm term;
    vsop_series series_tmp;
    vsop_var tmp;
    while (getline(vsopfile, line)){
        stringstream ss(line);
        int variable;
        ss >> dummy >> dummy >> dummy >> dummy >> dummy >> variable >> dummy >> degree_of_T >> terms;
        cout << "var=" << variable << ", terms=" << terms << endl; // read var and #terms in the series

        if (degree_of_T == "*T**0") {
            switch (variable) {
            case 1:
                headerfile << "vsop_var L_temp = {" << endl;
                break;
            case 2:
                headerfile << "vsop_var B_temp = {" << endl;
                break;
            case 3:
                headerfile << "vsop_var R_temp = {" << endl;
                break;
            default: cout << "error";
                break;
            }
        }
        headerfile << "    // " << degree_of_T << endl;
        headerfile << "    {" << endl;

        for (int i=0; i<terms; i++) {
            getline(vsopfile, line);
            ss.str(line.substr(80));
            string A,B,C;
            ss >> A >> B >> C;
            headerfile << "        {" << A << "," << B << "," << C << "}," << endl;
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

    string genfilename("generated_VSOP87D_ear.h");
    GenVSOPLBR(filename, genfilename);

    return 0;
}
