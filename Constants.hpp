#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <cmath>

namespace Constants {
    // Geometrized Unit Conversions
    // All internal calculations are G = c = 1.
    // L_unit = 1 km, M_unit = 1 km, T_unit = 1 km/c
    
    // 1 Solar Mass in km (G*M_sun / c^2)
    inline constexpr double MSUN_TO_KM = 1.4766; 

    // Density conversion: (km^-2) to (g/cm^3)
    // rho_cgs = rho_geo * RHO_CONV_CGS
    inline constexpr double RHO_CONV_CGS = 1.3467e18; 

    // Pressure conversion: (km^-2) to (dyn/cm^2)
    // P_cgs = P_geo * P_CONV_CGS
    inline constexpr double P_CONV_CGS = 1.2103e35;

    // Numerical Parameters
    inline constexpr double EPSILON_P = 1e-12; // Pressure floor (surface)
    inline constexpr double R_START = 1e-8;    // Initial radius to avoid 1/r
    inline constexpr double R_MAX = 40.0;      // Max integration radius in km
}

#endif