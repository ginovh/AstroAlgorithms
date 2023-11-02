#ifndef CHAPTER36_H
#define CHAPTER36_H

#include <map>
#include <string>
#include <vector>

#include <iostream>
#include <cmath>

// Table 36.A
class table36aRow {
public:
    long double A;
    long double B;
    long double M0;
    long double M1;
};

std::map<std::string, std::vector<table36aRow > > table36a =
    {
        {"Mercury", { {2451612.023, 115.8774771, 63.5867, 114.2088742}, {2451554.084, 115.8774771, 6.4822, 114.2088742} } },
        {"Venus", { {2451996.706, 583.921361, 82.7311, 215.513058}, {2451704.746, 583.921361, 154.9745, 215.513058} } },
        {"Mars", { {2451996.706, 583.921361, 82.7311, 215.513058}, {2451704.746, 583.921361, 154.9745, 215.513058} } },
        {"Jupiter", { {2451996.706, 583.921361, 82.7311, 215.513058}, {2451704.746, 583.921361, 154.9745, 215.513058} } }
};

// Table 36.B
std::vector<std::vector<std::vector<long double > > > MercPeriodicTerms = {
    {
        { 0.0545,  0.0002,  0.00000},
        {-6.2008,  0.0074,  0.00003},
        {-3.2750, -0.0197,  0.00001},
        { 0.4737, -0.0052, -0.00001},
        { 0.8111,  0.0033, -0.00002},
        { 0.0037,  0.0018,  0.00000},
        {-0.1768,  0.0000,  0.00001},
        {-0.0211, -0.0004,  0.00000},
        { 0.0326, -0.0003,  0.00000},
        { 0.0083,  0.0001,  0.00000},
        {-0.0040,  0.0001,  0.00000}
    },
    {
        {-0.0548, -0.0002,  0.00000},
        { 7.3894, -0.0100, -0.00003},
        { 3.2200,  0.0197, -0.00001},
        { 0.8383, -0.0064, -0.00001},
        { 0.9666,  0.0039, -0.00003},
        { 0.0770, -0.0026,  0.00000},
        { 0.2758,  0.0002, -0.00002},
        {-0.0128, -0.0008,  0.00000},
        { 0.0734, -0.0004, -0.00001},
        {-0.0122, -0.0002,  0.00000},
        { 0.0173, -0.0002,  0.00000}
    }
};

enum InferiorEvent {Inferior=0, Superior};
enum SuperiorEvent {Opposition=0, Conjunction};

// return: JDE of event
long double calc36(int year, int month, int event) {
    long double Y = year + (month/12.);
    long double A = table36a["Mercury"][event].A;
    long double B = table36a["Mercury"][event].B;
    long double M0 = table36a["Mercury"][event].M0;
    long double M1 = table36a["Mercury"][event].M1;
    int k = round((365.2425 * Y + 1721060 - A) / B);
    std::cout << "k     = " << k << std::endl;
    long double JDE0 = A + k*B;
    long double M = (M0 + k*M1)*M_PI/180; // in radians
    long double T = (JDE0 - 2451545)/36525;
    std::cout << "T     = " << T << std::endl;
    long double T2 = T*T;
    long double correction = MercPeriodicTerms[event][0][0] + MercPeriodicTerms[event][0][1]*T + MercPeriodicTerms[event][0][2]*T2;
    for(int i=1; i<6; i++){
        correction += (MercPeriodicTerms[event][2*i-1][0] + MercPeriodicTerms[event][2*i-1][1]*T + MercPeriodicTerms[event][2*i-1][2]*T2) * sin(i*M);
        correction += (MercPeriodicTerms[event][2*i][0] + MercPeriodicTerms[event][2*i][1]*T + MercPeriodicTerms[event][2*i][2]*T2) * cos(i*M);
    }
    std::cout << "correction     = " << correction << std::endl;
    return JDE0 + correction;
}

#endif // CHAPTER36_H
