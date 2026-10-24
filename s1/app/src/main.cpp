#include "calculator/Calculator.h"
#include <iostream>

using namespace std;

int main() {
    const double a = 6.0;
    const double b = 3.0;

    cout << a << " + " << b << " = " << Calculator::add(a, b) << '\n';
    cout << a << " * " << b << " = " << Calculator::multiply(a, b) << '\n';

    return 0;
}
