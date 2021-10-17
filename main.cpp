#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

long INT(long double value)
{
    if (value >= 0)
        return static_cast<long>(value);
    else
        return static_cast<long>(value - 1);
}

class Date {
    long double JD;

public:
    Date(): JD(2400000.5) {}
    Date(long double jd): JD(jd) {}
    Date(int year, int month, long double day) {
        if ( month < 3 ) {
            month +=12;
            year--;
        }
        int A=0;
        int B=0;
        if ( ( year > 1582 ) || ( ( year == 1582 ) && ( month > 10 ) ) || ( ( year == 1582 ) && ( month == 10 ) && (day >=15)) ) {
            A = INT( year / 100.0);
            B = 2 - A + INT(A / 4.0);
        }
        JD =  0.0 + INT(365.25 * ( year + 4716.0)) + INT(30.6001 * ( month + 1.0)) + day + B - 1524.5;
    }

    // use delegating constructor, C++11 needed
    Date(int year, int month, int day, int hour, int min, long double sec): Date(year, month, (day+(hour/24.0)+(min/(24.0*60))+(sec/(24.0*60*60)))) {
    }
    long double get_JD() const {
        return JD;
    }
    void get_ymd(int& year, int& month, long double& day) const {
        long double Z;
        long double A, B, alpha;
        int C, D, E;
        long double F = std::modf((JD + 0.5), &Z);
        if (Z<2299161) {
            A = Z;
        } else {
            alpha = INT((Z-1867216.25)/36524.25);
            A = Z + 1 + alpha - INT(alpha/4);
        }
        B = A + 1524;
        C = INT((B - 122.1)/365.25);
        D = INT(365.25 * C);
        E = INT((B - D)/30.6001);
        day = B - D - INT(30.6001 * E) + F;
        if (E < 14) {
            month = E - 1;
        } else {
            month = E - 13;
        }
        if (month>2) {
            year = C - 4716;
        } else {
            year = C - 4715;
        }
    }
    int get_dayOfWeek() const {
        return (static_cast<long>(JD + 1.5) % 7);
    }
};

ostream& operator<<(ostream& os, const Date& d) {
    return os << d.get_JD();
}

// TODO: method(s) below should go to Angle class?
long double to360(long double d) {
    long double tmp = fmod(d, 360);
    if (tmp<0) tmp+=360;
    return tmp;
}

void getNutationAndObliquity(long double JDE, long double& deltaPsi, long double& deltaEpsilon, long double& Epsilon0, long double& Epsilon) {
    long double T = (JDE - 2451545)/36525;
    long double factor[5];
    factor[0] = 297.85036 + 445267.111480 * T - 0.0019142 * T * T + (T * T * T)/189474;
    factor[1] = 357.52772 + 35999.050340 * T - 0.0001603 * T * T - (T * T * T)/300000;
    factor[2] = 134.96298 + 477198.867398 * T + 0.0086972 * T * T + (T * T * T)/56250;
    factor[3] = 93.27191 + 483202.017538 * T - 0.0036825 * T * T + (T * T * T)/327270;
    factor[4] = 125.04452 - 1934.136261 * T + 0.0020708 * T * T + (T * T * T)/450000;
    int arguments[][5] = {{0,0,0,0,1},
                          {-2,0,0,2,2},
                          {0,0,0,2,2},
                          {0,0,0,0,2},
                          {0,1,0,0,0},
                          {0,0,1,0,0},
                          {-2,1,0,2,2},
                          {0,0,0,2,1},
                          {0,0,1,2,2},
                          {-2,-1,0,2,2},
                          {-2,0,1,0,0},
                          {-2,0,0,2,1},
                          {0,0,-1,2,2},
                          {2,0,0,0,0},
                          {0,0,1,0,1},
                          {2,0,-1,2,2},
                          {0,0,-1,0,1},
                          {0,0,1,2,1},
                          {-2,0,2,0,0},
                          {0,0,-2,2,1},
                          {2,0,0,2,2},
                          {0,0,2,2,2},
                          {0,0,2,0,0},
                          {-2,0,1,2,2},
                          {0,0,0,2,0},
                          {-2,0,0,2,0},
                          {0,0,-1,2,1},
                          {0,2,0,0,0},
                          {2,0,-1,0,1},
                          {-2,2,0,2,2},
                          {0,1,0,0,1},
                          {-2,0,1,0,1},
                          {0,-1,0,0,1},
                          {0,0,2,-2,0},
                          {2,0,-1,2,1},
                          {2,0,1,2,2},
                          {0,1,0,2,2},
                          {-2,1,1,0,0},
                          {0,-1,0,2,2},
                          {2,0,0,2,1},
                          {2,0,1,0,0},
                          {-2,0,2,2,2},
                          {-2,0,1,2,1},
                          {2,0,-2,0,1},
                          {2,0,0,0,1},
                          {0,-1,1,0,0},
                          {-2,-1,0,2,1},
                          {-2,0,0,0,1},
                          {0,0,2,2,1},
                          {-2,0,2,0,1},
                          {-2,1,0,2,1},
                          {0,0,1,-2,0},
                          {-1,0,1,0,0},
                          {-2,1,0,0,0},
                          {1,0,0,0,0},
                          {0,0,1,2,0},
                          {0,0,-2,2,2},
                          {-1,-1,1,0,0},
                          {0,1,1,0,0},
                          {0,-1,1,2,2},
                          {2,-1,-1,2,2},
                          {0,0,3,2,2},
                          {2,-1,0,2,2} };
    long double coeffs[][4] = {{-171996, -174.2, 92025,8.9},
                               {-13187, -1.6, 5736, -3.1},
                               {-2274, -0.2, 977, -0.5},
                               {2062, 0.2, -895, 0.5},
                               {1426, -3.4, 54, -0.1},
                               {712, 0.1, -7, 0},
                               {-517, 1.2, 224, -0.6},
                               {-386, -0.4, 200, 0},
                               {-301,0.0, 129,-0.1},
                               {217,-0.5, -95, 0.3},
                               {-158,0, 0,0},
                               {129, 0.1, -70,0},
                               {123,0,-53,0},
                               {63,0,0,0},
                               {63,0.1,-33,0},
                               {-59,0,26,0},
                               {-58,-0.1,32,0},
                               {-51,0,27,0},
                               {48,0,0,0},
                               {46,0,-24,0},
                               {-38,0,16,0},
                               {-31,0,13,0},
                               {29,0,0,0},
                               {29,0-12,0},
                               {26,0,0,0},
                               {-22,0,0,0},
                               {21,0,-10,0},
                               {17,-0.1,0,0},
                               {16,0,-8,0},
                               {-16,0.1,7,0},
                               {-15,0,9,0},
                               {-13,0,7,0},
                               {-12,0,6,0},
                               {11,0,0,0},
                               {-10,0,5,0},
                               {-8,0,3,0},
                               {7,0,-3,0},
                               {-7,0,0,0},
                               {-7,0,3,0},
                               {-7,0,3,0},
                               {6,0,0,0},
                               {6,0,-3,0},
                               {6,0,-3,0},
                               {-6,0,3,0},
                               {-6,0,3,0},
                               {5,0,0,0},
                               {-5,0,3,0},
                               {-5,0,3,0},
                               {-5,0,3,0},
                               {4,0,0,0},
                               {4,0,0,0},
                               {4,0,0,0},
                               {-4,0,0,0},
                               {-4,0,0,0},
                               {-4,0,0,0},
                               {3,0,0,0},
                               {-3,0,0,0},
                               {-3,0,0,0},
                               {-3,0,0,0},
                               {-3,0,0,0},
                               {-3,0,0,0},
                               {-3,0,0,0},
                               {-3,0,0,0} };
    deltaPsi = 0;
    deltaEpsilon = 0;
    for (int i=0; i<63; i++) {
        long double arg = 0.0;
        for (int j=0; j<5; j++) {
            arg = arg + arguments[i][j]*factor[j];
        }
        deltaPsi = deltaPsi + (coeffs[i][0] + coeffs[i][1]*T) * sin(arg*M_PI/180);
        deltaEpsilon = deltaEpsilon + (coeffs[i][2] + coeffs[i][3]*T) * cos(arg*M_PI/180);
    }
    deltaPsi = deltaPsi * 0.0001;
    deltaEpsilon = deltaEpsilon * 0.0001;

    long double U = T/100;
    Epsilon0 = 23.4392911111 - 4680.93/3600*U - 1.55/3600*U*U + 1999.25/3600*U*U*U - 51.38/3600*U*U*U*U - 249.67/3600*U*U*U*U*U;
    Epsilon = Epsilon0 + deltaEpsilon/3600;
}

// Formula 12.4
// returns degrees
long double getSideralTime(long double JD, bool apparent=false) {
    long double T = (JD - 2451545.0)/36525;
    long double theta0 = 280.46061837 + 360.98564736629 * (JD - 2451545.0) + 0.000387933 * T * T - T * T * T /38710000;
    if (apparent) {
        long double deltaPsi = 0;
        long double deltaEpsilon = 0;
        long double Epsilon0 = 0;
        long double Epsilon = 0;
        // neglect very small variation of deltaPsi during deltaT, so JD is fine, see Ex. 12a
        getNutationAndObliquity(JD, deltaPsi, deltaEpsilon, Epsilon0, Epsilon);
        theta0 = theta0 + ((deltaPsi*cos(Epsilon*M_PI/180))/(60*60));
    }
    return to360(theta0);
}

// toHms and toDms should be reused inside Angle?
std::string toHms(long double hour) {
    std::string tmp;
    int hour_str = trunc(hour);
    int min = (hour - hour_str)*60;
    long double sec = (hour - hour_str -(min)/60.0)*60*60;
    tmp = to_string(hour_str)+"h"+to_string(min)+"m"+to_string(sec);
    return tmp;
}

std::string toDms(long double angleInDegrees) {
    std::string tmp;
    int degrees_str = trunc(angleInDegrees);
    int min = (angleInDegrees - degrees_str)*60;
    long double sec = (angleInDegrees - degrees_str -(min)/60.0)*60*60;
    if (angleInDegrees<0){ // This can be done always ?
        min = abs(min);
        sec = abs(sec);
    }
    tmp = to_string(degrees_str)+" "+to_string(min)+" "+to_string(sec);
    return tmp;
}

class Angle {
public:
    enum AngleFormat {
        HMS,
        DMS
    };
    long double angleInDegrees;
    Angle(): angleInDegrees(0.0) {
    }
    Angle(long double a): angleInDegrees(a) { //assume this is always DMS format
    }
    Angle(int degree, int min, long double sec, AngleFormat a = Angle::DMS) {
        if (degree<0) { // see p. 9
            min = - abs(min);
            sec = - abs(sec);
        }
        if (a == Angle::DMS) {
            angleInDegrees = degree + min/60.0 + sec/(60.*60);
        } else {
            angleInDegrees = (degree + min/60.0 + sec/(60.*60))*15;
        }
    }
    // TODO: also add Angle operator-(long double a) ?
    Angle operator-(Angle a) {
        return Angle(angleInDegrees - a.angleInDegrees);
    }
    Angle operator+(Angle a) {
        return Angle(angleInDegrees + a.angleInDegrees);
    }
    std::string toHms() {
        std::string tmp;
        long double hour = angleInDegrees/15;
        int hour_str = trunc(hour);
        int min = (hour - hour_str)*60;
        long double sec = (hour - hour_str -(min)/60.0)*60*60;
        tmp = to_string(hour_str)+"h"+to_string(min)+"m"+to_string(sec);
        return tmp;
    }
    std::string toDms() {
        std::string tmp;
        int degrees_str = trunc(angleInDegrees);
        int min = (angleInDegrees - degrees_str)*60;
        long double sec = (angleInDegrees - degrees_str -(min)/60.0)*60*60;
        tmp = to_string(degrees_str)+" "+to_string(min)+" "+to_string(sec);
        return tmp;
    }
};

long double sin(Angle a) {
    return sin(a.angleInDegrees * M_PI / 180.0);
}
long double cos(Angle a) {
    return cos(a.angleInDegrees * M_PI / 180.0);
}
long double tan(Angle a) {
    return tan(a.angleInDegrees * M_PI / 180.0);
}

long double to_0_1_range(long double a) {
    if (a<0) {
        a +=1;
    }
    if (a>1) {
        a -=1;
    }
    return a;
}

struct VSOPterm {
    long double A;
    long double B;
    long double C;
};
typedef vector<VSOPterm> vsop_series;
typedef vector<vsop_series> var;
struct VSOPLBR{
    var L;
    var B;
    var R;
};

void getVSOPLBR(string filename, VSOPLBR& planetLBR) {
    ifstream vsopfile(filename);
    string line;
    if (!vsopfile) {
        cout << "could not open file " << filename << endl;
    }

    // TODO: write out vsop data to headers with struct containing all these terms?
    string dummy;
    int old_variable = 1;
    int terms;
    VSOPterm term;
    vsop_series series_tmp;
    var tmp;
    while (getline(vsopfile, line)){
        stringstream ss(line);
        int variable;
        ss >> dummy >> dummy >> dummy >> dummy >> dummy >> variable >> dummy >> dummy >> terms;
        //            cout << "var=" << variable << ", terms=" << terms << endl;
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

void getHeliocentric(long double JDE, VSOPLBR planetLBR, long double& L, long double& B, long double& R) {
    long double tau = (JDE - 2451545)/365250;
    vector<long double> Lx;
    for (auto var: planetLBR.L) {
        long double sum=0.0;
        for (auto term: var) {
            sum = sum + term.A * cos(term.B + term.C*tau);
        }
        //            cout << "Lsum = " << sum << endl;
        Lx.push_back(sum);
    }
    L = 0.0;
    for (int i=0; i<Lx.size(); i++) {
        L = L + Lx[i]*pow(tau,i);
    }
    // division by 10^8 is not needed as terms in vsop_file are already divided by 10^8
    L = to360(L * 180/M_PI);

    vector<long double> Bx;
    for (auto var: planetLBR.B) {
        long double sum=0.0;
        for (auto term: var) {
            sum = sum + term.A * cos(term.B + term.C*tau);
        }
        Bx.push_back(sum);
    }
    B = 0.0;
    for (int i=0; i<Bx.size(); i++) {
        B = B + Bx[i]*pow(tau,i);
    }
    // division by 10^8 is not needed as terms in vsop_file are already divided by 10^8
    B = (B * 180/M_PI);

    vector<long double> Rx;
    for (auto var: planetLBR.R) {
        long double sum=0.0;
        for (auto term: var) {
            sum = sum + term.A * cos(term.B + term.C*tau);
        }
        Rx.push_back(sum);
    }
    R = 0.0;
    for (int i=0; i<Rx.size(); i++) {
        R = R + Rx[i]*pow(tau,i);
    }
    // division by 10^8 is not needed as terms in vsop_file are already divided by 10^8

    // TODO: correction on p. 219
}

// Arguments in degrees
void fromEquatorialToEcliptical(long double Alpha, long double Delta, long double Epsilon, long double& Beta, long double& Lambda) {
    // Convert to radians
    Alpha = Alpha *M_PI/180;
    Delta = Delta *M_PI/180;
    Epsilon = Epsilon *M_PI/180;
    Lambda = atan2( (sin(Alpha)*cos(Epsilon)) + (tan(Delta)*sin(Epsilon)), cos(Alpha) ) *180.0/M_PI;
    Beta = asin( (sin(Delta)*cos(Epsilon)) - (cos(Delta)*sin(Epsilon)*sin(Alpha)) ) *180.0/M_PI;
}

// Arguments in degrees
void fromEclipticalToEquatorial(long double& Alpha, long double& Delta, long double Epsilon, long double Beta, long double Lambda) {
    // Convert to radians
    Epsilon = Epsilon *M_PI/180;
    Lambda = Lambda *M_PI/180;
    Beta = Beta *M_PI/180;
    Alpha = atan2( (sin(Lambda)*cos(Epsilon)) - (tan(Beta)*sin(Epsilon)), cos(Lambda) ) *180.0/M_PI;
    Delta = asin( (sin(Beta)*cos(Epsilon)) + (cos(Beta)*sin(Epsilon)*sin(Lambda)) ) *180.0/M_PI;
    Alpha = to360(Alpha);
}

int main()
{
    cout.precision(12);

    // Ex. 1a, p. 8
    Angle aa = Angle(9,14,55.8, Angle::HMS);
    cout << "aa = " << aa.toHms() << endl;
    cout << "aa = " << aa.angleInDegrees << endl;

    // Don't call constructor explicit
    Angle bb = 138.73250;
    cout << "bb = " << bb.toHms() << endl;
    cout << "bb = " << bb.angleInDegrees << endl;

    // p. 60
    // TODO: use floor i.o. INT? Or use floor inside INT() definition?
    // keep INT() as it is used in the book?
    cout << "INT(7/4) = " << INT(7/4) << endl;
    cout << "INT(8/4) = " << INT(8/4) << endl;
    cout << "INT(5.02) = " << INT(5.02) << endl;
    cout << "INT(5.9999) = " << INT(5.9999) << endl;
    cout << "INT(-7.83) = " << INT(-7.83) << endl;
    cout << "floor(7/4) = " << floor(7/4) << endl;
    cout << "floor(8/4) = " << floor(8/4) << endl;
    cout << "floor(5.02) = " << floor(5.02) << endl;
    cout << "floor(5.9999) = " << floor(5.9999) << endl;
    cout << "floor(-7.83) = " << floor(-7.83) << endl;

    // Chap. 7
    cout << "Date(1957,10,4.81) = " << Date(1957,10,4.81) << endl;
    cout << "Date(1957,10,4.81) = " << Date(333,1,27.5) << endl;
    cout << "Date(1957,10,4.81) = " << Date(1957,10,4.81).get_JD() << endl;

    cout.precision(4);

    int year=0;
    int month=0;
    long double day=0;
    Date(2436116.31).get_ymd(year, month, day);
    cout << year << " " << month << " " << day << endl;
    Date(1842713.0).get_ymd(year, month, day);
    cout << year << " " << month << " " << day << endl;
    Date(1507900.13).get_ymd(year, month, day);
    cout << year << " " << month << " " << day << endl;

    // Ex. 7e
    cout << "DayOfWeek = " << Date(1954,6,30.0).get_dayOfWeek() << endl;

    cout.precision(12);

    // Ex. 12a
    cout << endl << "Ex. 12a" << endl;
    cout << "Theta0 = " << Angle(getSideralTime(Date(1987,4,10, 0,0,0).get_JD(), true)).toHms() << endl;

    // Ex. 12b
    cout << endl << "Ex. 12b" << endl;
    cout << "Theta0 = " << getSideralTime(Date(1987,4,10, 19,21,0).get_JD()) << endl;
    cout << "Theta0 = " << Angle(getSideralTime(Date(1987,4,10, 19,21,0).get_JD())).toHms() << endl;

    // Ex. 13a
    {
        // private scope to hide variables defined here so I can use same names in other examples.
        cout << endl << "Ex. 13a" << endl;
        long double Alpha = 116.328942;
        long double Delta = 28.026183;
        long double Epsilon = 23.4392911;
        long double Beta;
        long double Lambda;

        fromEquatorialToEcliptical(Alpha, Delta, Epsilon, Beta, Lambda);
        cout << "Lambda = " << Lambda << endl;
        cout << "Beta = " << Beta << endl;

        fromEclipticalToEquatorial(Alpha, Delta, Epsilon, Beta, Lambda);
        cout << "Alpha = " << Alpha << endl;
        cout << "Delta = " << Delta << endl;
    }

    // Ex. 13b
    {
        cout << endl << "Ex. 13b" << endl;
        long double  L = 77.06555555556;
        long double  Phi = 38.9213888889;
        long double  Alpha = 347.3193375;
        long double  Delta = -6.71989166667;
        long double  H = getSideralTime(Date(1987,4,10, 19,21,0).get_JD()) - L - Alpha;
        cout << "H = " << H << endl;
        // Convert to radians
        H = H *M_PI/180;
        Phi = Phi *M_PI/180;
        Delta = Delta *M_PI/180;
        long double A;
        long double h;
        A = atan2(sin(H), ((cos(H)*sin(Phi))-(tan(Delta)*cos(Phi)))) *180.0/M_PI;
        h = asin(sin(Phi)*sin(Delta) + cos(Phi)*cos(Delta)*cos(H)) *180.0/M_PI;
        cout << "A = " << A << endl;
        cout << "h = " << h << endl;
    }

    // Ex. 13b
    {
        cout << endl << "Ex. 13b with Angle class" << endl;
        // TODO: acos, atan2 en asin geven radian terug. Om die *180.0/M_PI niet te vergeten Dit ergens aanpassen? asin overload?
        // Of nieuwe acos_d() ? Of Angle constructor die radians als arg neemt?
        Angle L = Angle(77,3,56.0);
        Angle Phi = Angle(38,55,17);
        Angle Alpha = Angle(23,9,16.641, Angle::HMS);
        Angle Delta = Angle(-6,43,11.61);
        Angle H = Angle(getSideralTime(Date(1987,4,10, 19,21,0).get_JD())) - L - Alpha;
        cout << "H = " << H.angleInDegrees << endl;
        cout << "A = " << atan2(sin(H), ((cos(H)*sin(Phi))-(tan(Delta)*cos(Phi)))) *180.0/M_PI << endl;
        cout << "h = " << asin(sin(Phi)*sin(Delta) + cos(Phi)*cos(Delta)*cos(H)) *180.0/M_PI << endl;
    }

    // Ex. 15a
    Angle L = Angle(71,5,0);
    Angle Phi = Angle(42,20,0);
    long double Theta0 = getSideralTime(Date(1988,3,20, 0,0,0).get_JD());
    cout << endl << "Ex. 15a" << endl;
    cout << "Theta0 = " << Theta0 << endl;
    Angle Alpha[3] = {Angle(40.68021), Angle(41.73129), Angle(42.78204)};
    Angle Delta[3] = {Angle(18.04761), Angle(18.44092), Angle(18.82742)};
    Angle h0 = Angle(-0.5667);
    long double deltaT = 56; // TODO: calculate? See Chap. 10
    long double secondMember = (sin(h0)-sin(Phi)*sin(Delta[1]))/(cos(Phi)*cos(Delta[1]));
    if (abs(secondMember)>1) { // acos() returns nan if >1 (or complex getal?)
        cout << "circumpolar!" << endl;
    } else {
        Angle H0 = acos(secondMember) *180.0/M_PI;
        cout << "H0 = " << H0.angleInDegrees << endl;
        long double m[3];
        long double Theta[3];
        long double n[3];
        m[0] = (Alpha[1].angleInDegrees + L.angleInDegrees - Theta0)/360;
        m[1] = m[0] - H0.angleInDegrees/360;
        m[2] = m[0] + H0.angleInDegrees/360;
        for (int i=0; i<3; i++) {
            m[i] = to_0_1_range(m[i]);
            Theta[i] = to360(Theta0 + 360.985647*m[i]);
            n[i] = m[i] + deltaT/86400;
        }
        for (int i=0; i<3; i++) {
            cout << "m[" << i << "] = " << m[i] << endl;
        }
        for (int i=0; i<3; i++) {
            cout << "Theta[" << i << "] = " << Theta[i] << endl;
        }
        for (int i=0; i<3; i++) {
            cout << "n[" << i << "] = " << n[i] << endl;
        }
        long double a=Alpha[1].angleInDegrees-Alpha[0].angleInDegrees;
        long double b=Alpha[2].angleInDegrees-Alpha[1].angleInDegrees;
        long double c=b-a;
        long double Alpha1=Alpha[1].angleInDegrees; // tmp store Alpha[1], otherwise it will be overwritten
        for (int i=0; i<3; i++) {
            Alpha[i] = Alpha1 + n[i]/2*(a+b+n[i]*c);
            cout << "Alpha[" << i << "] = " << Alpha[i].angleInDegrees << endl;
        }
        a=Delta[1].angleInDegrees-Delta[0].angleInDegrees;
        b=Delta[2].angleInDegrees-Delta[1].angleInDegrees;
        c=b-a;
        long double Delta1=Delta[1].angleInDegrees; // tmp store Delta[1], otherwise it will be overwritten
        for (int i=0; i<3; i++) {
            Delta[i] = Delta1 + n[i]/2*(a+b+n[i]*c);
            cout << "Delta[" << i << "] = " << Delta[i].angleInDegrees << endl;
        }

        Angle H[3];
        long double h[3];
        for (int i=0; i<3; i++) {
            H[i] = Angle(Theta[i]) - L - Alpha[i];
            h[i] = asin(sin(Phi)*sin(Delta[i]) + cos(Phi)*cos(Delta[i])*cos(H[i])) *180.0/M_PI;
        }
        for (int i=0; i<3; i++) {
            cout << "H[" << i << "] = " << H[i].angleInDegrees << endl;
        }
        for (int i=0; i<3; i++) {
            cout << "h[" << i << "] = " << h[i] << endl;
        }
        long double deltam[3];
        deltam[0] = -(H[0].angleInDegrees)/360; // TODO: assert -180 < H[0] < 180
        deltam[1] = (h[1] - h0.angleInDegrees)/(360*cos(Delta[1])*cos(Phi)*sin(H[1]));
        deltam[2] = (h[2] - h0.angleInDegrees)/(360*cos(Delta[2])*cos(Phi)*sin(H[2]));
        for (int i=0; i<3; i++) {
            cout << "deltam[" << i << "] = " << deltam[i] << endl;
        }
        for (int i=0; i<3; i++) {
            m[i] = m[i] + deltam[i];
            cout << "m[" << i << "] = " << m[i] << endl;
        }
        cout << "Rising  = " << toHms(24*m[1]) << endl;
        cout << "Transit = " << toHms(24*m[0]) << endl;
        cout << "Setting = " << toHms(24*m[2]) << endl;
    }

    // Ex. 22a
    {
        cout << endl << "Ex. 22a" << endl;
        long double JDE = Date(1987,4,10, 0,0,0).get_JD();
        long double deltaPsi = 0;
        long double deltaEpsilon = 0;
        long double Epsilon0 = 0;
        long double Epsilon = 0;
        getNutationAndObliquity(JDE, deltaPsi, deltaEpsilon, Epsilon0, Epsilon);
        cout << "deltaPsi  = " << deltaPsi << endl;
        cout << "deltaEpsilon  = " << deltaEpsilon << endl;
        cout << "Epsilon0  = " << Angle(Epsilon0).toDms() << endl;
        cout << "Epsilon  = " << Angle(Epsilon).toDms() << endl;
    }

    // Ex. 25b
    {
        cout << endl << "Ex. 25b" << endl;
        struct VSOPLBR planetLBR;
        string filename("/home/ginovh/Programming/astro/VI_81/VSOP87D.ear");
        getVSOPLBR(filename, planetLBR);

        long double L=0.0;
        long double B=0.0;
        long double R=0.0;
        long double JDE = Date(1992,10,13, 0,0,0).get_JD();
        getHeliocentric(JDE, planetLBR, L, B, R);
        cout << "L = " << L << endl;
        cout << "B = " << B << endl;
        cout << "R = " << R << endl;

        long double sunlongitude = L+180;
        long double Beta = -B;
        long double tau = (JDE - 2451545)/365250;
        long double T = 10*tau;
        long double lamdba_a = sunlongitude - 1.397*T - 0.00031*T*T;
        sunlongitude = sunlongitude - (0.09033/(60*60));
        long double deltaBeta = (0.03916/(60*60))*(cos(lamdba_a*M_PI/180)-sin(lamdba_a*M_PI/180));
        Beta = Beta + deltaBeta;
        cout << "sunlongitude = " << sunlongitude << endl;
        cout << "Beta = " << Beta << endl;
        long double deltaPsi = 0;
        long double deltaEpsilon = 0;
        long double Epsilon0 = 0;
        long double Epsilon = 0;
        getNutationAndObliquity(JDE, deltaPsi, deltaEpsilon, Epsilon0, Epsilon);
        cout << "deltaPsi  = " << deltaPsi << endl;
        cout << "deltaEpsilon  = " << deltaEpsilon << endl;
        cout << "Epsilon0  = " << toDms(Epsilon0) << endl;
        cout << "Epsilon  = " << toDms(Epsilon) << endl;
        long double Lambda = sunlongitude + (deltaPsi/(60*60)) - ((20.4898/(60*60))/R);
        cout << "sunlongitude = " << Lambda << endl;
        cout << "sunlongitude = " << toDms(Lambda) << endl;

        long double Alpha;
        long double Delta;
        fromEclipticalToEquatorial(Alpha, Delta, Epsilon, Beta, Lambda);
        cout << "Alpha = " << Alpha << endl;
        cout << "Delta = " << Delta << endl;
        cout << "Alpha = " << toHms(Alpha/15) << endl;
        cout << "Delta = " << toDms(Delta) << endl;
    }

    // Ex. 32a
    {
        cout << endl << "Ex. 32a" << endl;
        struct VSOPLBR planetLBR;
        string filename("/home/ginovh/Programming/astro/VI_81/VSOP87D.ven");
        getVSOPLBR(filename, planetLBR);

        long double L=0.0;
        long double B=0.0;
        long double R=0.0;
        getHeliocentric(Date(1992,12,20, 0,0,0).get_JD(), planetLBR, L, B, R);
        cout << "L = " << L << endl;
        cout << "B = " << B << endl;
        cout << "R = " << R << endl;

    }
    return 0;
}
