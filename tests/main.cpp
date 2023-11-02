#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>
#include <map>

using namespace std;

#include "libmeeus.h"
#include "Chapter36.h"

void chap44(long double JDE, long double& x, long double& y, long double& z, long double& delta, long double& tau) {
    long double correctedJDE = JDE;

    long double L=0.0;
    long double B=0.0;
    long double R=0.0;
    getHeliocentric(JDE, "ear", L, B, R);
    cout << "L = " << L << endl;
    cout << "B = " << B << endl;
    cout << "R = " << R << endl;

    long double sunlongitude = L+180;
    long double Beta = -B;
    cout << "sunlongitude = " << sunlongitude << endl;
    cout << "Beta = " << Beta << endl;
    cout << "R = " << R << endl << endl;

    long double l=0.0;
    long double b=0.0;
    long double r=0.0;
    delta = 5.0;
    long double olddelta;

    do {
        olddelta = delta;
        tau = 0.0057755183 * delta;
        correctedJDE = JDE - tau;

        getHeliocentric(correctedJDE, "jup", l, b, r);

        x = r * cos(b*M_PI/180) * cos(l*M_PI/180) + R * cos(sunlongitude*M_PI/180);
        y = r * cos(b*M_PI/180) * sin(l*M_PI/180) + R * sin(sunlongitude*M_PI/180);
        z = r * sin(b*M_PI/180)                   + R * sin(Beta*M_PI/180);

        delta = sqrt(pow(x,2) + pow(y,2) + pow(z,2));
    } while (abs(delta-olddelta) > 1.0e-6);

    cout << "l = " << l << endl;
    cout << "b = " << b << endl;
    cout << "r = " << r << endl;
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

        long double L=0.0;
        long double B=0.0;
        long double R=0.0;
        long double JDE = Date(1992,10,13, 0,0,0).get_JD();
        getHeliocentric(JDE, "ear", L, B, R);
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

        long double L=0.0;
        long double B=0.0;
        long double R=0.0;
        getHeliocentric(Date(1992,12,20, 0,0,0).get_JD(), "ven", L, B, R);
        cout << "L = " << L << endl;
        cout << "B = " << B << endl;
        cout << "R = " << R << endl;
    }

    // Ex. 44b
    {
        cout << endl << "Ex. 44b" << endl;
        // see also https://aas.aanda.org/articles/aas/abs/1998/08/contents/contents.html J.H. Lieske
        // https://aas.aanda.org/articles/aas/abs/1998/08/ds6503/ds6503.html

        long double JDE = Date(1992,12,16, 0,0,0).get_JD();
        cout << "JDE = " << JDE << endl << endl;
        // JDE is not corrected with delta T, so add ET-UT=.00068 day(58s) for 1992
        // TODO: fix this later by using formula (10.2) or similar formula from chapter 10?
        // JDE hardcoded for testing
        JDE = 2448972.50068;
        cout << "JDE = " << JDE << endl << endl;

        long double x=0.0;
        long double y=0.0;
        long double z=0.0;
        long double delta=5.0;
        long double tau=0.0; // unit: days
        chap44(JDE, x, y, z, delta, tau);
        cout << "x = " << x << endl;
        cout << "y = " << y << endl;
        cout << "z = " << z << endl;
        cout << "delta = " << delta << endl;
        cout << "tau = " << tau << endl << endl;

        long double lambda0 = 0.0;
        long double beta0 = 0.0;
        lambda0 = atan2(y,x);
        beta0 = atan2(z, sqrt(pow(x,2) + pow(y,2)) );
        cout << "lambda0 = " << lambda0 << endl;
        cout << "beta0 = " << beta0 << endl;

        long double t = 0.0;
        t = JDE - 2443000.5 - tau;
        cout << "t = " << t << endl << endl;

        long double l1 = 0.0;
        long double l2 = 0.0;
        long double l3 = 0.0;
        long double l4 = 0.0;
        l1 = 106.07719 + 203.488955790 * t;
        l2 = 175.73161 + 101.374724735 * t;
        l3 = 120.55883 +  50.317609207 * t;
        l4 =  84.44459 +  21.571071177 * t;
        cout << "l1 = " << l1 << endl;
        cout << "l2 = " << l2 << endl;
        cout << "l3 = " << l3 << endl;
        cout << "l4 = " << l4 << endl;

        long double pi1 = 0.0;
        long double pi2 = 0.0;
        long double pi3 = 0.0;
        long double pi4 = 0.0;
        pi1 =  97.0881 + 0.16138586 * t;
        pi2 = 154.8663 + 0.04726307 * t;
        pi3 = 188.1840 + 0.00712734 * t;
        pi4 = 335.2868 + 0.00184000 * t;
        cout << "pi1 = " << pi1 << endl;
        cout << "pi2 = " << pi2 << endl;
        cout << "pi3 = " << pi3 << endl;
        cout << "pi4 = " << pi4 << endl;

        long double omega1 = 0.0;
        long double omega2 = 0.0;
        long double omega3 = 0.0;
        long double omega4 = 0.0;
        omega1 = 312.3346 - 0.13279386 * t;
        omega2 = 100.4411 - 0.03263064 * t;
        omega3 = 119.1942 - 0.00717703 * t;
        omega4 = 322.6186 - 0.00175934 * t;
        cout << "omega1 = " << omega1 << endl;
        cout << "omega2 = " << omega2 << endl;
        cout << "omega3 = " << omega3 << endl;
        cout << "omega4 = " << omega4 << endl;

        long double Gamma = 0.0;
        Gamma = 0.33033 * sin( (163.679 + 0.0010512 * t) * M_PI/180 )
                + 0.03439 * sin( (34.486 - 0.0161731 * t) * M_PI/180 );
        cout << "Gamma = " << Gamma << endl;

        long double Phi = 0.0;
        Phi = 199.6766 + 0.17379190 * t;
        cout << "Phi = " << Phi << endl;

        long double Psi = 0.0;
        Psi = 316.5182 - 0.00000208 * t;
        cout << "Psi = " << Psi << endl;

        long double G = 0.0;
        G = 30.23756 + 0.0830925701 * t + Gamma;
        cout << "G = " << G << endl;
        long double Gac = 0.0;
        Gac = 31.97853 + 0.0334597339 * t;
        cout << "Gac = " << Gac << endl;

        long double Pi = 13.469942;
        cout << "Pi = " << Pi << endl;

        long double Sigma1 = 0.0;
        Sigma1 =  0.47259 * sin(                 2*(l1 - l2) * M_PI/180 )
            - 0.03478 * sin(                 (pi3 - pi4) * M_PI/180 )
            + 0.01081 * sin(           (l2 - 2*l3 + pi3) * M_PI/180 )
            + 0.00738 * sin(                         Phi * M_PI/180 )
            + 0.00713 * sin(           (l2 - 2*l3 + pi2) * M_PI/180 )
            - 0.00674 * sin(    (pi1 + pi3 - 2*Pi - 2*G) * M_PI/180 )
            + 0.00666 * sin(           (l2 - 2*l3 + pi4) * M_PI/180 )
            + 0.00445 * sin(                  (l1 - pi3) * M_PI/180 )
            - 0.00354 * sin(                   (l1 - l2) * M_PI/180 )
            - 0.00317 * sin(              (2*Psi - 2*Pi) * M_PI/180 )
            + 0.00265 * sin(                  (l1 - pi4) * M_PI/180 )
            - 0.00186 * sin(                           G * M_PI/180 )
            + 0.00162 * sin(                 (pi2 - pi3) * M_PI/180 )
            + 0.00158 * sin(                 4*(l1 - l2) * M_PI/180 )
            - 0.00155 * sin(                   (l1 - l3) * M_PI/180 )
            - 0.00138 * sin( (Psi + omega3 - 2*Pi - 2*G) * M_PI/180 )
            - 0.00115 * sin(      2*(l1 - 2*l2 + omega2) * M_PI/180 )
            + 0.00089 * sin(                 (pi2 - pi4) * M_PI/180 )
            + 0.00085 * sin(     (l1 + pi3 - 2*Pi - 2*G) * M_PI/180 )
            + 0.00083 * sin(           (omega2 - omega3) * M_PI/180 )
            + 0.00053 * sin(              (Psi - omega2) * M_PI/180 );
        cout << "Sigma1     = " << Sigma1 << endl;
        cout << "Sigma1 Ref = -0.00654" << endl << endl;

        long double Sigma2 = 0.0;
        Sigma2 =  1.06476 * sin(                 2*(l2 - l3) * M_PI/180 )
                 + 0.04256 * sin(           (l1 - 2*l2 + pi3) * M_PI/180 )
                 + 0.03581 * sin(                  (l2 - pi3) * M_PI/180 )
                 + 0.02395 * sin(           (l1 - 2*l2 + pi4) * M_PI/180 )
                 + 0.01984 * sin(                  (l2 - pi4) * M_PI/180 )
                 - 0.01778 * sin(                         Phi * M_PI/180 )
                 + 0.01654 * sin(                  (l2 - pi2) * M_PI/180 )
                 + 0.01334 * sin(           (l2 - 2*l3 + pi2) * M_PI/180 )
                 + 0.01294 * sin(                 (pi3 - pi4) * M_PI/180 )
                 - 0.01142 * sin(                   (l2 - l3) * M_PI/180 )
                 - 0.01057 * sin(                           G * M_PI/180 )
                 - 0.00775 * sin(                2*(Psi - Pi) * M_PI/180 )
                 + 0.00524 * sin(                 2*(l1 - l2) * M_PI/180 )
                 - 0.00460 * sin(                   (l1 - l3) * M_PI/180 )
                 + 0.00316 * sin( (Psi - 2*G + omega3 - 2*Pi) * M_PI/180 )
                 - 0.00203 * sin(    (pi1 + pi3 - 2*Pi - 2*G) * M_PI/180 )
                 + 0.00146 * sin(              (Psi - omega3) * M_PI/180 )
                 - 0.00145 * sin(                         2*G * M_PI/180 )
                 + 0.00125 * sin(              (Psi - omega4) * M_PI/180 )
                 - 0.00115 * sin(           (l1 - 2*l3 + pi3) * M_PI/180 )
                 - 0.00094 * sin(             2*(l2 - omega2) * M_PI/180 );
        cout << "Sigma2     = " << Sigma2 << endl;
        cout << "Sigma2 Ref = +1.10011" << endl << endl;
    }

    // Ex. 36a
    {
        cout << endl << "Ex. 36a" << endl;

        int k = calck("Mercury", 1993, 10, Inferior);
        long double JDE = calc36(k, Inferior);
        int year; int month; long double day; long double dummy;
        Date(JDE).get_ymd(year, month, day);
        std::cout << "JDE     = " << JDE << std::endl;
        cout << "     " << year << "/" << month << "/" << floor(day) << " " << floor(modf(day, &dummy)*24) << "h " << endl;
        cout << "Ref: 1993/11/6 3h" << endl << endl;

        cout << "Mercury Superior - " << endl << endl;
        k = calck("Mercury", 2023, 1, Superior);
        for(int kLoopVar=k; kLoopVar<(k+10); kLoopVar++){
            long double JDE = calc36(kLoopVar, Superior);
            int year; int month; long double day; long double dummy;
            Date(JDE).get_ymd(year, month, day);
            cout << "     " << year << "/" << month << "/" << floor(day) << " " << floor(modf(day, &dummy)*24) << "h " << endl;
        }

        cout << endl << "Jupiter opposition - "  << endl;
        k = calck("Jupiter", 2022, 3, Opposition);
        for(int kLoopVar=k; kLoopVar<(k+10); kLoopVar++){
            long double JDE = calc36Jup(kLoopVar, Opposition);
            int year; int month; long double day; long double dummy;
            Date(JDE).get_ymd(year, month, day);
            cout << "     " << year << "/" << month << "/" << floor(day) << " " << floor(modf(day, &dummy)*24) << "h " << endl;
        }

    }

    return 0;
}
