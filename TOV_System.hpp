#ifndef TOV_SYSTEM_HPP
#define TOV_SYSTEM_HPP

#include <vector>
#include <cmath>
#include "EoS.hpp"

typedef std::vector<double> state_type;

struct TOV_System {
    const EquationOfState& eos;

    TOV_System(const EquationOfState& e) : eos(e) {}

    // x[0] is Mass (m), x[1] is Pressure (P)
    void operator()(const state_type& x, state_type& dxdr, const double r) const {
        double m = x[0];
        double p = x[1];

        if (p <= 0.0) { // Outside the star
            dxdr[0] = 0.0;
            dxdr[1] = 0.0;
            return;
        }

        double rho = eos.get_rho(p);

        // dm/dr = 4 * pi * r^2 * rho
        dxdr[0] = 4.0 * M_PI * r * r * rho;

        // dP/dr = TOV Equation
        if (r < 1e-10) { // Origin singularity handling
            dxdr[1] = 0.0;
        } else {
            double num = -(rho + p) * (m + 4.0 * M_PI * std::pow(r, 3) * p);
            double den = r * (r - 2.0 * m);
            dxdr[1] = num / den;
        }
    }
};

#endif