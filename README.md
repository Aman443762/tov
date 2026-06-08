# Parallel TOV Solver for Relativistic Stellar Structure

[![C++](https://img.shields.io/badge/C++-17%2B-blue.svg)](https://isocpp.org/)
[![Boost](https://img.shields.io/badge/Boost-odeint-orange.svg)](https://www.boost.org/)
[![OpenMP](https://img.shields.io/badge/OpenMP-Parallel-green.svg)](https://www.openmp.org/)
[![Status: WIP](https://img.shields.io/badge/Status-Active_Development-yellow.svg)]()

A multi-threaded C++ computational engine designed to solve the Tolman-Oppenheimer-Volkoff (TOV) system of differential equations. This solver computes the macroscopic properties (Mass and Radius) of static, spherically symmetric compact objects (neutron stars) across broad central pressure sweeps using customizable Equations of State (EoS).

---

## Prerequisites

To build the solver from source, your system requires:
* **C++ Compiler** 
* **CMake** (v3.15 or higher)
* **Boost C++ Libraries** (Specifically `Boost.Numeric.Odeint`)
* **OpenMP**
* **Python & Related Library** 

---

**Currently the project is under active development to implement the file structure, dense QCD and thermodynamic boundaries**

**Contributions:** I am actively refining this architecture! Any suggestions, code reviews, or pull requests regarding Boost `odeint` optimizations or thermodynamic consistency enforcement are highly appreciated.

## Working

**Supported OS:** Linux, macOS, and Windows (via WSL).

1. Clone the repository:
```bash
   git clone https://github.com/Aman443762/tov_solver.git
   cd tov_solver
   mkdir build
   cd build
   cmake ..
   make 
   cd ..
   ./build/tov_solver
   python3 plot.py



