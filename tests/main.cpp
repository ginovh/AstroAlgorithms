#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

#include "libmeeus.h"

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

    // Ex. 7a & 7b
    cout << "Date(1957,10,4.81) = " << Date(1957,10,4.81) << endl;
    cout << "Date(333,1,27.5) = " << Date(333,1,27.5) << endl;
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
        long double L = toDecimal(77.0356);
        long double Phi = toDecimal(38.5517);
        long double Alpha = toDecimal(23.0916641)*15;
        long double Delta = toDecimal(-6.431161);
        long double Theta0 = getSideralTime(Date(1987,4,10, 19,21,0).get_JD());
        long double A;
        long double h;
        fromEquatorialToHorizontal(L, Phi, Alpha, Delta, Theta0, A, h);
        cout << "A = " << A << endl;
        cout << "h = " << h << endl;
    }

    // Ex. 13b
    {
        cout << endl << "Ex. 13b with Angle class" << endl;
        Angle L = Angle(77,3,56.0);
        Angle Phi = Angle(38,55,17);
        Angle Alpha = Angle(23,9,16.641, Angle::HMS);
        Angle Delta = Angle(-6,43,11.61);
        long double Theta0 = getSideralTime(Date(1987,4,10, 19,21,0).get_JD());
        long double A;
        long double h;
        fromEquatorialToHorizontal(L.angleInDegrees, Phi.angleInDegrees, Alpha.angleInDegrees, Delta.angleInDegrees, Theta0, A, h);
        cout << "A = " << A << endl;
        cout << "h = " << h << endl;
    }

    // Ex. 15a
    cout << endl << "Ex. 15a" << endl;
    Angle L = Angle(71,5,0);
    Angle Phi = Angle(42,20,0);
    long double Theta0 = getSideralTime(Date(1988,3,20, 0,0,0).get_JD());
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
        cout << "Rising  = " << toHmsString(24*m[1]) << endl;
        cout << "Transit = " << toHmsString(24*m[0]) << endl;
        cout << "Setting = " << toHmsString(24*m[2]) << endl;
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
        cout << "Epsilon0  = " << toDmsString(Epsilon0) << endl;
        cout << "Epsilon  = " << toDmsString(Epsilon) << endl;
        long double Lambda = sunlongitude + (deltaPsi/(60*60)) - ((20.4898/(60*60))/R);
        cout << "sunlongitude = " << Lambda << endl;
        cout << "sunlongitude = " << toDmsString(Lambda) << endl;

        long double Alpha;
        long double Delta;
        fromEclipticalToEquatorial(Alpha, Delta, Epsilon, Beta, Lambda);
        cout << "Alpha = " << Alpha << endl;
        cout << "Delta = " << Delta << endl;
        cout << "Alpha = " << toHmsString(Alpha/15) << endl;
        cout << "Delta = " << toDmsString(Delta) << endl;
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
