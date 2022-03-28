#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

#include "libmeeus.h"

void GenVSOPLBR(string planet_name) {
    VSOPLBR planetLBR;
    string vsopInputFilename = "/home/ginovh/Programming/astro/VI_81/VSOP87D." + planet_name;
    ifstream vsopfile(vsopInputFilename);
    if (!vsopfile) {
        cout << "could not open file " << vsopInputFilename << endl;
    }
    string headerFilename = "VSOP87D_"+planet_name+".h";
    ofstream headerfile(headerFilename);
    if (!headerfile) {
        cout << "could not open file " << headerFilename << endl;
    }

    headerfile << "#ifndef VSOP87D_" << planet_name << "_H" << endl;
    headerfile << "#define VSOP87D_" << planet_name << "_H" << endl << endl;
    headerfile << "#include \"libmeeus.h\"" << endl << endl;

    string line;
    string dummy;
    int old_variable = 1; // 1:L, 2:B, 3:R
    int terms;
    string degree_of_T;
    while (getline(vsopfile, line)){
        stringstream ss(line);
        int variable;
        ss >> dummy >> dummy >> dummy >> dummy >> dummy >> variable >> dummy >> degree_of_T >> terms;
        cout << "var=" << variable << ", terms=" << terms << endl; // read var and #terms in the series

        if (old_variable != variable) {
            old_variable = variable;
            headerfile << "};" << endl << endl;
        }

        if (degree_of_T == "*T**0") {
            switch (variable) {
            case 1:
                headerfile << "vsop_var L_" << planet_name << " = {" << endl;
                break;
            case 2:
                headerfile << "vsop_var B_" << planet_name << " = {" << endl;
                break;
            case 3:
                headerfile << "vsop_var R_" << planet_name << " = {" << endl;
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
        headerfile << "    }," << endl;
    }
    // only when while(getline()) is finished, the last var, R, is completey read.
    headerfile << "};" << endl << endl;

    headerfile << "#endif // VSOP87D_" << planet_name << "_H" << endl << endl;
}

int main()
{
    // TODO:

    struct VSOPLBR planetLBR;
    string planet_name;
    string filename;

    planet_name = "ear";
    cout << endl << "Generate VSOP87 " << planet_name << endl;
//    getVSOPLBR(filename, planetLBR);
    GenVSOPLBR(planet_name);

    planet_name = "ven";
    cout << endl << "Generate VSOP87 " << planet_name << endl;
    GenVSOPLBR(planet_name);

    return 0;
}
