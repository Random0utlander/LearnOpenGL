#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include "ODEpoint.h"

class ODEsolver{
    public:

    ODEsolver() = default;
    ODEsolver(vector<function<double(ODEpoint)> >);
    ~ODEsolver()= default;

    void SetODEfunc(const vector<function<double(ODEpoint)>>&);

    vector<ODEpoint> Euler(ODEpoint, double, double);
    ODEpoint Euler(ODEpoint, double);
    vector<ODEpoint> Trapezoidal(ODEpoint, double, double);
    vector<ODEpoint> LeapFrog(ODEpoint, double, double);
    vector<ODEpoint> RK2(ODEpoint, double, double);
    ODEpoint RK2(ODEpoint, double);
    vector<ODEpoint> RK4(ODEpoint, double, double);
    ODEpoint RK4(ODEpoint, double);


    private:
    vector<function<double(ODEpoint)> > F;
    map<string, vector<ODEpoint> > MS;
    vector<ODEpoint> StepByStepSol;
};