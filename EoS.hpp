#ifndef EOS_HPP
#define EOS_HPP

#include <cmath>

class EquationOfState {
public:
    virtual ~EquationOfState() = default;
    virtual double get_pressure(double rho) const = 0;
    virtual double get_rho(double P) const = 0;
};

// Polytrope: P = K * rho^gamma
class Polytrope : public EquationOfState {
private:
    double K, gamma;
public:
    Polytrope(double K_val, double gamma_val) : K(K_val), gamma(gamma_val) {}
    
    double get_pressure(double rho) const override { 
        return K * std::pow(rho, gamma); 
    }
    
    double get_rho(double P) const override { 
        return std::pow(P / K, 1.0 / gamma); 
    }
};

#endif