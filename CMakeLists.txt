cmake_minimum_required(VERSION 3.10)
project(TOV_HPC_Solver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find if source-installed Boost
set(Boost_NO_SYSTEM_PATHS OFF) 
find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenMP REQUIRED)

add_executable(tov_solver main.cpp)

target_link_libraries(tov_solver PRIVATE 
    Boost::boost 
    OpenMP::OpenMP_CXX
)

target_compile_options(tov_solver PRIVATE -O3 -march=native)