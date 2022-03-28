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

extern vsop_var L_mer, B_mer, R_mer;
extern vsop_var L_ven, B_ven, R_ven;
extern vsop_var L_ear, B_ear, R_ear;
extern vsop_var L_mar, B_mar, R_mar;
extern vsop_var L_jup, B_jup, R_jup;
extern vsop_var L_sat, B_sat, R_sat;
extern vsop_var L_ura, B_ura, R_ura;
extern vsop_var L_nep, B_nep, R_nep;
#endif // VSOP87D_H
