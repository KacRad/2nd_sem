#ifndef DELTA_H
#define DELTA_H


class Delta
{
public:
    double a, b, c, dlt;
    Delta();
    double solution(double, double, double);
    double delta_equation(double, double, double);
};

#endif // DELTA_H
