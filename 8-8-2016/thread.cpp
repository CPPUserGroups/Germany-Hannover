#include <thread>
#include <iostream>

void calc_fac( int f, int& result )
{
    for ( result = 1; f; --f )
        result *= f;
}

int main()
{
    int fac3, fac5, fac7;

    std::thread calc_fac3( calc_fac, 3, std::ref( fac3 ) );
    std::thread calc_fac5( calc_fac, 5, std::ref( fac5 ) );
    calc_fac( 7, fac7 );

    calc_fac3.join();
    calc_fac5.join();

    std::cout << "3!: " << fac3 << std::endl;
    std::cout << "5!: " << fac5 << std::endl;
    std::cout << "7!: " << fac7 << std::endl;
}