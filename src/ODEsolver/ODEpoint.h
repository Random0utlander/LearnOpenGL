#include <iostream>
#include <vector>
#include <functional>

using namespace std;

#ifndef __ODEPOINT_H__
#define __ODEPOINT_H__

class Xvar{
    public:

    // Constructors
    Xvar() = default;
    Xvar(int);
    Xvar(vector<double>);
    ~Xvar() = default;

    Xvar(const Xvar&); // copy constructor
    Xvar& operator=(const Xvar&); // assignment operator
    Xvar operator+(const Xvar&); // operator+
    double& operator[](int);
    
    friend Xvar operator*(double, const Xvar&); // scalar*X
    friend ostream& operator<< (std::ostream&, const Xvar&);
    vector<double>& X();

    protected:
    vector<double> x;

};

class ODEpoint: public Xvar{

    public:

    ODEpoint() : time(-1) {;}
    ODEpoint(double t_, const std::vector<double>& v) : time(t_), Xvar(v){;}
    ODEpoint(double t_, Xvar a_) : time(t_), Xvar(a_) {;}
    ODEpoint(double t_, const std::initializer_list<double>& v) : time(t_), Xvar(v) {;}
    ~ODEpoint() = default;

    void SetODEpoint(double t_, Xvar& p);
    void SetODEpoint(double t_, const std::initializer_list<double>& v);
    void SetODEpoint(double t_, std::vector<double> v);

    double& T() { return time;} // accessor to time

    private:
    double time;
};

#endif