#include "ODEsolver.h"

ODEsolver::ODEsolver(vector<function<double(ODEpoint)> > functions){
    F = functions;
}

vector<ODEpoint> ODEsolver::Euler(ODEpoint P0, double step, double TIME){

    vector<ODEpoint> V;
    V.push_back(P0);

    for(double t=0;t<TIME-step;t+=step){
        ODEpoint P_current = V.back();
        vector<double> x_update;
        for(int i=0;i<F.size();i++){
            x_update.push_back(P_current.X()[i] + step*F[i](P_current));
        }
        V.push_back(ODEpoint(t+step,x_update));
    }

    MS["euler"] = V;

    return V;
}
ODEpoint ODEsolver::Euler(ODEpoint P0, double step){

    double previous_t = 0;
    if(!StepByStepSol.empty()){
        previous_t = StepByStepSol.back().T();
    }
    StepByStepSol.push_back(P0);
    ODEpoint P_current = StepByStepSol.back();
    vector<double> x_update;
    for(int i=0;i<F.size();i++){
        x_update.push_back(P_current.X()[i] + step*F[i](P_current));
    }
        StepByStepSol.push_back(ODEpoint(previous_t+step,x_update));

    return StepByStepSol.back();
}

vector<ODEpoint> ODEsolver::Trapezoidal(ODEpoint P0, double step, double TIME){

    vector<ODEpoint> V;
    V.push_back(P0);    

    for(double t=0;t<TIME-step;t+=step){
        ODEpoint P_current = V.back();

        vector<double> x_next;
        for(int i=0;i<F.size();i++){
            x_next.push_back(P_current.X()[i] + step*F[i](P_current));
        }
        ODEpoint P_next(t+step, x_next);
        
        vector<double> x_update;
        for(int i=0;i<F.size();i++){
            x_update.push_back(P_current.X()[i] + 0.5*step*(F[i](P_current)+F[i](P_next)));
        }

        V.push_back(ODEpoint(t+step,x_update));
    }

    MS["trapezoidal"] = V;

    return V;
}

vector<ODEpoint> ODEsolver::LeapFrog(ODEpoint P0, double step, double TIME){

    vector<ODEpoint> V;
    V.push_back(P0);

    vector<double> v_first;
    for(int i=0;i<F.size();i++){
        v_first.push_back(P0.X()[i]+step*F[i](P0));
    }
    V.push_back(ODEpoint(step, v_first));

    for(double t=0;t<TIME-step;t+=step){
        ODEpoint P_current = V.back();
        ODEpoint P_antes = V[V.size()-2];

        vector<double> x_update;
        for(int i=0;i<F.size();i++){
            x_update.push_back(P_antes.X()[i] + 2*step*F[i](P_current));
        }

        V.push_back(ODEpoint(t+step,x_update));
    }

    MS["LeapFrog"] = V;

    return V;
}

vector<ODEpoint> ODEsolver::RK2(ODEpoint P0, double step, double TIME){

    vector<ODEpoint> V;
    V.push_back(P0);    

    for(double t=0;t<TIME-step;t+=step){
        ODEpoint P_current = V.back();

        vector<double> x_int;
        for(int i=0;i<F.size();i++){
            x_int.push_back(P_current.X()[i] + (step/2)*F[i](P_current));
        }
        ODEpoint P_int(t+step/2, x_int);

        vector<double> x_update;
        for(int i=0;i<F.size();i++){
            x_update.push_back(P_current.X()[i] + step*(F[i](P_int)));
        }
        V.push_back(ODEpoint(t+step,x_update));
    }

    MS["RK2"] = V;

    return V;

}

ODEpoint ODEsolver::RK2(ODEpoint P0, double step){

    double previous_t = 0;
    if(!StepByStepSol.empty()){
        previous_t = StepByStepSol.back().T();
    }
    StepByStepSol.push_back(P0);
    ODEpoint P_current = StepByStepSol.back();
    vector<double> x_int;
    for(int i=0;i<F.size();i++){
        x_int.push_back(P_current.X()[i] + (step/2)*F[i](P_current));
    }
    ODEpoint P_int(previous_t+step/2, x_int);

    vector<double> x_update;
    for(int i=0;i<F.size();i++){
        x_update.push_back(P_current.X()[i] + step*(F[i](P_int)));
    }
    StepByStepSol.push_back(ODEpoint(previous_t+step,x_update));

    return StepByStepSol.back();

}

vector<ODEpoint> ODEsolver::RK4(ODEpoint P0, double step, double TIME){

    vector<ODEpoint> V;
    V.push_back(P0);    

    for(double t=0;t<TIME-step;t+=step){
        ODEpoint P_current = V.back();

        vector<double> x_int_1;
        for(int i=0;i<F.size();i++){
            x_int_1.push_back(P_current.X()[i] + (step/2)*F[i](P_current));
        }
        ODEpoint P_int_1(t+step/2, x_int_1);

        vector<double> x_int_2;
        for(int i=0;i<F.size();i++){
            x_int_2.push_back(P_current.X()[i] + (step/2)*F[i](P_int_1));
        }
        ODEpoint P_int_2(t+step/2, x_int_2);

        vector<double> x_int_3;
        for(int i=0;i<F.size();i++){
            x_int_3.push_back(P_current.X()[i] + step*(F[i](P_int_2)));
        }
        ODEpoint P_int_3(t+step, x_int_3);

        vector<double> x_update;
        for(int i=0;i<F.size();i++){
            x_update.push_back(P_current.X()[i] + (step/6)*(F[i](P_current)+2*F[i](P_int_1)+2*F[i](P_int_2)+F[i](P_int_3)));
        }
        V.push_back(ODEpoint(t+step,x_update));
    }

    MS["RK4"] = V;

    return V;
}

ODEpoint ODEsolver::RK4(ODEpoint P0, double step){

    double previous_t = 0;
    if(!StepByStepSol.empty()){
        previous_t = StepByStepSol.back().T();
    }
    StepByStepSol.push_back(P0);
    ODEpoint P_current = StepByStepSol.back();
    vector<double> x_int_1;
    for(int i=0;i<F.size();i++){
        x_int_1.push_back(P_current.X()[i] + (step/2)*F[i](P_current));
    }
    ODEpoint P_int_1(previous_t+step/2, x_int_1);

    vector<double> x_int_2;
    for(int i=0;i<F.size();i++){
        x_int_2.push_back(P_current.X()[i] + (step/2)*F[i](P_int_1));
    }
    ODEpoint P_int_2(previous_t+step/2, x_int_2);

    vector<double> x_int_3;
    for(int i=0;i<F.size();i++){
        x_int_3.push_back(P_current.X()[i] + step*(F[i](P_int_2)));
    }
    ODEpoint P_int_3(previous_t+step, x_int_3);

    vector<double> x_update;
    for(int i=0;i<F.size();i++){
        x_update.push_back(P_current.X()[i] + (step/6)*(F[i](P_current)+2*F[i](P_int_1)+2*F[i](P_int_2)+F[i](P_int_3)));
    }
    StepByStepSol.push_back(ODEpoint(previous_t+step,x_update));


    return StepByStepSol.back();
}

void ODEsolver::SetODEfunc(const vector<function<double(ODEpoint)>>& functions){
    F = functions;
}