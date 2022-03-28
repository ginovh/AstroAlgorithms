#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

#include "libmeeus.h"

long INT(long double value)
{
    if (value >= 0)
        return static_cast<long>(value);
    else
        return static_cast<long>(value - 1);
}

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
long double getSideralTime(long double JD, bool apparent) {
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
// This is messy for now ... need to cleanup handling of angles in general.
long double toDecimal(long double angleInhms) {
    int degrees = trunc(angleInhms);
    int min = (angleInhms - degrees)*100;
    long double sec = (angleInhms - degrees - (min / 100.))*10000;
    // Note: don't take abs value of min and sec if angleInhms<0 as everything is added mathematically, so if they are negative this is correct.
    return degrees + min/60.0 + sec/3600;
}

std::string toHmsString(long double hour) {
    std::string tmp;
    int hour_str = trunc(hour);
    int min = (hour - hour_str)*60;
    long double sec = (hour - hour_str -(min)/60.0)*60*60;
    tmp = to_string(hour_str)+"h"+to_string(min)+"m"+to_string(sec);
    return tmp;
}

std::string toDmsString(long double angleInDegrees) {
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

// TODO: acos, atan2 en asin geven radian terug. Om die *180.0/M_PI niet te vergeten Dit ergens aanpassen? asin overload?
// Of nieuwe acos_d() ? Of Angle constructor die radians als arg neemt?

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

// Arguments in degrees
void fromEquatorialToHorizontal(long double L, long double Phi, long double Alpha, long double Delta, long double Theta0, long double& A, long double& h) {
    long double  H = Theta0 - L - Alpha;
    // Convert to radians
    H = H *M_PI/180;
    Phi = Phi *M_PI/180;
    Delta = Delta *M_PI/180;
    A = atan2(sin(H), ((cos(H)*sin(Phi))-(tan(Delta)*cos(Phi)))) *180.0/M_PI;
    h = asin(sin(Phi)*sin(Delta) + cos(Phi)*cos(Delta)*cos(H)) *180.0/M_PI;
}
