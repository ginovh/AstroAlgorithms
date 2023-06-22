#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

void GenVSOPLBR(string planet_name) {
    string vsopInputFilename = "/home/ginovh/Programming/astro/VI_81/VSOP87D." + planet_name;
    ifstream vsopfile(vsopInputFilename);
    if (!vsopfile) {
        cout << "could not open file " << vsopInputFilename << endl;
    }
    string outputFilename = "VSOP87D_"+planet_name+".cpp";
    ofstream headerfile(outputFilename);
    if (!headerfile) {
        cout << "could not open file " << outputFilename << endl;
    }

    headerfile << "#include \"VSOP87D.h\"" << endl << endl;

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
}

void GenVSOPLBR_allPlanets() {
    string outputFilename = "VSOP87D.cpp";
    ofstream sourcefile(outputFilename);
    if (!sourcefile) {
        cout << "could not open file " << outputFilename << endl;
    }

    sourcefile << "#include <map>" << endl;
    sourcefile << "#include <string>" << endl;
    sourcefile << "#include \"VSOP87D.h\"" << endl << endl;

    sourcefile << "std::map<std::string, VSOPLBR> VSOP87D_all_terms = {" << endl;

    vector<string> planets = { "mer", "ven", "ear", "mar", "jup", "sat", "ura", "nep"};
    for (auto planet_name: planets) {
        string vsopInputFilename = "/home/ginovh/Programming/astro/VI_81/VSOP87D." + planet_name;
        ifstream vsopfile(vsopInputFilename);
        if (!vsopfile) {
            cout << "could not open file " << vsopInputFilename << endl;
        }

        sourcefile << "    {\"" << planet_name << "\"," << endl; // key of map
        sourcefile << "     {   //" << planet_name << endl;      // data of map

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
            }

            if (degree_of_T == "*T**0") {
                switch (variable) {
                case 1:
                    sourcefile << "      {  // L" << endl;
                    break;
                case 2:
                    sourcefile << "      },  // end of L" << endl;
                    sourcefile << "      {  // B" << endl;
                    break;
                case 3:
                    sourcefile << "      },  // end of B" << endl;
                    sourcefile << "      {  // R" << endl;
                    break;
                default: cout << "error";
                    break;
                }
            }
            sourcefile << "       { // " << degree_of_T << endl;

            for (int i=0; i<terms; i++) {
                getline(vsopfile, line);
                ss.str(line.substr(80));
                string A,B,C;
                ss >> A >> B >> C;
                sourcefile << "        {" << A << "," << B << "," << C << "}," << endl;
            }
            sourcefile << "       }, // end of terms" << endl;
        }
        // only when while(getline()) is finished, the last var, R, is completey read.
        sourcefile << "      },  // end of R" << endl;
        sourcefile << "     }, // end of planet data" << endl;
        sourcefile << "    }, // end of planet " << planet_name << endl;
    }
    sourcefile << "};" << endl; // close VSOP87D_all_terms map
}

int main()
{
    // TODO:

    GenVSOPLBR_allPlanets();

    // First generate common header.
    string outputFilename = "VSOP87D.h";
    ofstream headerfile(outputFilename);
    if (!headerfile) {
        cout << "could not open file " << outputFilename << endl;
    }

    headerfile << "#ifndef VSOP87D_H" << endl;
    headerfile << "#define VSOP87D_H" << endl << endl;

    headerfile << "#include <vector>" << endl << endl;

    headerfile << "struct VSOPterm {" << endl;
    headerfile << "    long double A;" << endl;
    headerfile << "    long double B;" << endl;
    headerfile << "    long double C;" << endl;
    headerfile << "};" << endl;
    headerfile << "typedef std::vector<VSOPterm> vsop_series;" << endl;
    headerfile << "typedef std::vector<vsop_series> vsop_var;" << endl;
    headerfile << "struct VSOPLBR{" << endl;
    headerfile << "    vsop_var L;" << endl;
    headerfile << "    vsop_var B;" << endl;
    headerfile << "    vsop_var R;" << endl;
    headerfile << "};" << endl << endl;

    vector<string> planets = { "mer", "ven", "ear", "mar", "jup", "sat", "ura", "nep"};
    for (auto planet_name: planets) {
        headerfile << "extern vsop_var ";
        headerfile << "L_" << planet_name << ", B_" << planet_name << ", R_" << planet_name << ";" << endl;
    }
    headerfile << "#endif // VSOP87D_H" << endl;

    // Next generate .cpp files per planet
    for (auto planet_name: planets) {
        cout << endl << "Generate VSOP87 " << planet_name << endl;
        GenVSOPLBR(planet_name);
    }

    return 0;
}
