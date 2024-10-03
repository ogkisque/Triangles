#include <hayai.hpp>
#include <iostream>

BENCHMARK(MyCoreTests, TestSqrt, 10, 100)
{
    
    int a = 4567;
    double b = sqrt(a);
    for (int i = 0; i < 1000)
    {
        b = sqrt(a * i);
        std::cout << b << std::endl;
    }
}

int main()
{
    hayai::MainRunner runner;
    return runner.Run();
}