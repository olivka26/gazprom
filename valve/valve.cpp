#include <iostream>
#include <cmath>
#define M 16
#define G 1.32
#define R 8.31
#define PI 3.1415926
#define RAD 20
using namespace std;

double AbsoluteTemperature(double celsius){
    return celsius+273.15;
}

double Outflow(double open, double temperature, double pressure_in, double pressure_out){
    double sq=2*G*R*temperature,ratio,p;
    sq/=(G-1);
    sq/=M;
    if(pressure_in>pressure_out){
        ratio=pressure_out/pressure_in;
        p=pow(ratio,2/G);
        p-=pow(ratio,(G+1)/G);
        sq*=p;
        return PI*open*open*sqrt(sq);
    }
    ratio=pressure_in/pressure_out;
    p=pow(ratio,2/G);
    p-=pow(ratio,(G+1)/G);
    sq*=p;
    return (-1)*PI*open*open*sqrt(sq);
}

int main(int argc, char *argv[]){
    double pressure_pipe,pressure_after,temperature,Absolute_Temperature, open_radius;
    cout<<"Enter the pressure in the pipe: ";
    cin>>pressure_pipe;
    if(pressure_pipe<0){
        cerr<<"The pressure in the pipe cannot be negative";
        return -1;
    }
    cout<<"Enter the pressure after the pipe: ";
    cin>>pressure_after;
    if(pressure_after<0){
        cerr<<"The pressure after the pipe cannot be negative";
        return -2;
    }
    cout<<"Enter the temperature: ";
    cin>>temperature;
    cout<<"Enter the radius of open area in the pipe: ";
    cin>>open_radius;
    if(open_radius<0){
        cerr<<"The radius of open area cannot be negative";
        return -3;
    }
    if(open_radius>RAD){
        cerr<<"The radius of open area cannot exceed "<<RAD;
        return -4;
    }
    Absolute_Temperature=AbsoluteTemperature(temperature);
    if(Absolute_Temperature<=0){
        cerr<<"Absolute Temperature cannot be non-positive";
        return -5;
    }
    cout<<Outflow(open_radius, Absolute_Temperature, pressure_pipe, pressure_after);
    return 0;
}
