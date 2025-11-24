#include "ODEpoint.h"
using namespace std;

Xvar::Xvar(int a){
    x.resize(a);
}
Xvar::Xvar(vector<double> v){
    x = v;
}

Xvar::Xvar(const Xvar& P){
    x = P.x;
}
Xvar& Xvar::operator=(const Xvar& P){

    for(int i=0;i<P.x.size();i++){
        x[i] = P.x[i];
    }

    return *this;
}

Xvar Xvar::operator+(const Xvar& P){

    Xvar P1(P);
    for(int i=0;i<P.x.size();i++){
        P1.x[i] += P.x[i];
    }
    return P1;

}
double& Xvar::operator[](int i){
    return x[i];
}

Xvar operator*(double a, const Xvar& P){

    Xvar P1(P);
    for(int i=0;i<P.x.size();i++){
        P1.x[i] *= a;
    }
    return P1;

}

ostream& operator<< (std::ostream& s, const Xvar& P){

    s << "[";
    for(int i=0;i<P.x.size();i++){
        if(i!=P.x.size()-1){
            s << P.x[i] << ",";
        }
        else{
            s << P.x[i] << "]";
        }
    }
    return s;

}

vector<double>& Xvar::X(){
    return x;
}

void ODEpoint::SetODEpoint(double t_, Xvar& p){
    time = t_;
    x = p.X();
}

void ODEpoint::SetODEpoint(double t_, const std::initializer_list<double>& v){
    time = t_;
    x = v;
}

void ODEpoint::SetODEpoint(double t_, std::vector<double> v){
    time = t_;
    x = v;
}