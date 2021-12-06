#include "delta.h"
#include <cmath>
#include <iostream>

Delta::Delta()
{
}

double Delta::delta_equation(double a, double b, double c){
    return (pow(b, 2) - 4*a*c);
}

double Delta::solution(double a, double b, double c){
    this->a = a;
    this->b = b;
    this->c = c;
    this->dlt = delta_equation(a, b, c);
    if (a == 0){
        return (-c/b);
    } else if (dlt == 0){
        return (-b/(2*a));
    } else if (dlt > 0){
/*delta ma 2 rozwiązania, wykorzystuję jedno,
  żeby nie tworzyć dodatkowych funkcji - zadanie wyłącznie
  na potrzeby ćwiczenia testów*/
        return (-b-sqrt(dlt))/(2*a);
    } else {
        throw "No solution to this equation";
    }
}
