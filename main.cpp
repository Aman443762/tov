#include <iostream>
#include <vector>
#include <fstream>
#include <omp.h>
#include <boost/numeric/odeint.hpp>

#include "Constants.hpp"
#include "EoS.hpp"
#include "TOV_System.hpp"

using namespace boost::numeric::odeint;

struct Result { 
    double p, r, m; 
};

int main() {
    // Setup EoS and Pressure Sweep
    Polytrope eos(200.0, 2.0);
    
    std::vector<double> p_centrals;
    for(double p = 1e-7; p < 1e-3; p *= 1.01) {
        p_centrals.push_back(p);
    }

    // Pre-allocate results vector for thread-safety
    std::vector<Result> results(p_centrals.size());

    std::cout << "Starting TOV solver on " << omp_get_max_threads() << " cores..." << std::endl;

    // Parallel Integration Loop
    #pragma omp parallel for
    for(size_t i = 0; i < p_centrals.size(); ++i) {
        TOV_System tov(eos);
        
        // Initial conditions
        state_type x = { 0.0, p_centrals[i] }; 
        double r = Constants::R_START;
        double dr = 0.01; 

        double final_r = 0.0;
        double final_m = 0.0;

        // Observer updates the local final_r and final_m
        auto observer = [&](const state_type &s, double current_r) {
            if (s[1] > Constants::EPSILON_P) {
                final_r = current_r;
                final_m = s[0];
            }
        };

        auto stepper = make_controlled(1e-10, 1e-10, runge_kutta_cash_karp54<state_type>());

        // Run the integration
        integrate_adaptive(stepper, tov, x, r, Constants::R_MAX, dr, observer);

        // Store results at the specific index (thread-safe, no critical section)
        results[i] = Result{ p_centrals[i], final_r, final_m / Constants::MSUN_TO_KM };
    }

    // 4. Sequential File Writing (Ensures sorted data for plotting)
    std::ofstream file("mr_curve.csv");
    if (file.is_open()) {
        file << "P_central,Radius_km,Mass_Msun\n";
        for(const auto& res : results) {
            file << res.p << "," << res.r << "," << res.m << "\n";
        }
        file.close();
        std::cout << "Successfully generated mr_curve.csv" << std::endl;
    } else {
        std::cerr << "Error: Could not open file for writing!" << std::endl;
    }

    return 0;
}