#ifndef LIBMEEUS_H
#define LIBMEEUS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

long INT(long double value);

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

ostream& operator<<(ostream& os, const Date& d);

// TODO: method(s) below should go to Angle class?
long double to360(long double d);

void getNutationAndObliquity(long double JDE, long double& deltaPsi, long double& deltaEpsilon, long double& Epsilon0, long double& Epsilon);

// Formula 12.4
// returns degrees
long double getSideralTime(long double JD, bool apparent=false);

// toHms and toDms should be reused inside Angle?
// This is messy for now ... need to cleanup handling of angles in general.
long double toDecimal(long double angleInhms);

std::string toHmsString(long double hour);

std::string toDmsString(long double angleInDegrees);

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

// TODO: acos, atan2 en asin geven radian terug. Om die *180.0/M_PI niet te vergeten Dit ergens aanpassen? asin overload?
// Of nieuwe acos_d() ? Of Angle constructor die radians als arg neemt?

long double sin(Angle a);
long double cos(Angle a);
long double tan(Angle a);

long double to_0_1_range(long double a);

void getHeliocentric(long double JDE, std::string planet, long double& L, long double& B, long double& R);

// Arguments in degrees
void fromEquatorialToEcliptical(long double Alpha, long double Delta, long double Epsilon, long double& Beta, long double& Lambda);

// Arguments in degrees
void fromEclipticalToEquatorial(long double& Alpha, long double& Delta, long double Epsilon, long double Beta, long double Lambda);

// Arguments in degrees
void fromEquatorialToHorizontal(long double L, long double Phi, long double Alpha, long double Delta, long double Theta0, long double& A, long double& h);

#endif // LIBMEEUS_H
