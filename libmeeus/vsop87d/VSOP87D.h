#ifndef VSOP87D_H
#define VSOP87D_H

#include <vector>

struct VSOPterm {
    long double A;
    long double B;
    long double C;
};
typedef std::vector<VSOPterm> vsop_series;
typedef std::vector<vsop_series> vsop_var;
struct VSOPLBR{
    vsop_var L;
    vsop_var B;
    vsop_var R;
};

#endif // VSOP87D_H
