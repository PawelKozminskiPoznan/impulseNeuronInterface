#include "Neuron.h"

#include <cmath>

#include<iostream>
using namespace std;

//Neuron::Neuron(int start_one, int end_one,  int start_second, int end_second,  int start_third, int end_third, int T, double a, double b, double c, double d, double dt)
//{
//    this->a = a;
//    this->b = b;
//    this->c = c;
//    this->d = d;
//    this->dt = dt;
//    this->start_one = start_one;
//    this->end_one = end_one;
//    this->start_second = start_second;
//    this->end_second = end_second;
//    this->start_third = start_third;
//    this->end_third = end_third;
//    this->T = T/dt;//ceil(T/dt);
//    v = new double[this->T];
//    u = new double[this->T];
//    //v[0] = (( rand() % 10 ) + 65);
//    v[0] = -70;
//    //u[0] = (( rand() % 6 ) - 17);
//    u[0] = -14;
////    cout<<v[0]<<endl;
////    cout<<u[0]<<endl;
//    I = new double[this->T];
//    iapp = 0;
//    capacity = 0.0083;
//}


Neuron::Neuron(int start_one, int end_one,  int start_second, int end_second,  int start_third, int end_third, int start_fourth, int end_fourth, int start_fifth, int end_fifth, int start_sixth, int end_sixth, int T, double a, double b, double c, double d, double dt)
//{
{
    this->a = a;
    this->b = 0.2;
    this->c = -65;
    this->d = d;
    this->dt = 0.5;
    this->start_one = start_one;
    this->end_one = end_one;
    this->start_second = start_second;
    this->end_second = end_second;
    this->start_third = start_third;
    this->end_third = end_third;
    this->start_fourth = start_fourth;
    this->end_fourth = end_fourth;
    this->start_fifth = start_fifth;
    this->end_fifth = end_fifth;
    this->start_sixth = start_sixth;
    this->end_sixth = end_sixth;
    this->T = T/dt;//ceil(T/dt);
    v = new double[this->T];
    u = new double[this->T];
    //v[0] = (( rand() % 10 ) + 65);
    v[0] = -70;
    //u[0] = (( rand() % 6 ) - 17);
    u[0] = -14;
//    cout<<v[0]<<endl;
//    cout<<u[0]<<endl;
    I = new double[this->T];
    iapp = 0;
    capacity = 0.0083;
}

Neuron::~Neuron()
{
    delete [] v;
    delete [] u;
    delete [] I;
}


//double* Neuron::work(int current)
//{
//    for(unsigned int t=0; t<T; ++t)
//    {
//        if(t*dt>start_one && t*dt<end_one)
//            iapp = current;
//        else if(t*dt>start_second && t*dt<end_second)
//            iapp = current;
//        else if(t*dt>start_third && t*dt<end_third)
//            iapp = current;
//        else
//            iapp = 0;

//        if(v[t]<35)
//        {
//            dv = (0.04*v[t]+5)*v[t]+140-u[t];
//            v[t+1] = v[t]+(dv+iapp)*dt;
//            du = a*(b*v[t]-u[t]);
//            u[t+1] = u[t]+dt*du;
//        }
//        else
//        {
//            v[t] = 35;
//            v[t+1] = c;
//            u[t+1] = u[t] + d;
//        }
//    }
//    return v;
//}

double* Neuron::work(int current1, int current2, int current3, int current4, int current5, int current6)
{
    for(unsigned int t=0; t<T; ++t)
    {
        if(t*dt>start_one && t*dt<end_one)
            iapp = current1;
        else if(t*dt>start_second && t*dt<end_second)
            iapp = current2;
        else if(t*dt>start_third && t*dt<end_third)
            iapp = current3;
        else if(t*dt>start_fourth && t*dt<end_fourth)
            iapp = current4;
        else if(t*dt>start_fifth && t*dt<end_fifth)
            iapp = current5;
        else if(t*dt>start_sixth && t*dt<end_sixth)
            iapp = current6;
        else
            iapp = 0;

        if(v[t]<35)
        {
            dv = (0.04*v[t]+5)*v[t]+140-u[t];
            v[t+1] = v[t]+(dv+iapp)*dt;
            du = a*(b*v[t]-u[t]);
            u[t+1] = u[t]+dt*du;
        }
        else
        {
            v[t] = 35;
            v[t+1] = c;
            u[t+1] = u[t] + d;
        }
    }
    return v;
}


double* Neuron::work(const double* x, const double* x2, double R1, double R2)
{
    //double iapp1 = (( rand() % 5 ));
    double iapp1 = 0;
    //double iapp2 = (( rand() % 5 ));
    double iapp2 = 0;
    for(int t=0; t<T; ++t)
    {
        if(x[t]>v[t])
        {
            if(t==0)
                iapp1 = ((x[t]-v[t])/R1);
            else
                iapp1 = (((x[t]-v[t])/R1)+((x[t]-v[t])-(x[t-1]-v[t-1]))*capacity);
        }
        else
            iapp1 = 0;
        if(x2[t]>v[t])
        {
            if(t==0)
                iapp2 = ((x2[t]-v[t])/R2);
            else
                iapp2 = (((x2[t]-v[t])/R2)+((x2[t]-v[t])-(x2[t-1]-v[t-1]))*capacity);
        }
        else
            iapp2 = 0;
        iapp = iapp1 + iapp2;
        I[t]=iapp;
        if(v[t]<35)
        {
            dv = (0.04*v[t]+5)*v[t]+140-u[t];
            v[t+1] = v[t]+(dv+iapp)*dt;
            du = a*(b*v[t]-u[t]);
            u[t+1] = u[t]+dt*du;
        }
        else
        {
            v[t] = 35;
            v[t+1] = c;
            u[t+1] = u[t] + d;
        }
    }
    return v;
}

double* Neuron::work(const double* x, const double* x2, const double* x3, const double* x4, double R1, double R2, double R3, double R4)
{
    double iapp1 = 0;
    double iapp2 = 0;
    double iapp3 = 0;
    double iapp4 = 0;
    for(int t=0; t<T; ++t)
    {
        if(x[t]>v[t])
        {
            if(t==0)
                iapp1 = ((x[t]-v[t])/R1);
            else
                iapp1 = (((x[t]-v[t])/R1)+((x[t]-v[t])-(x[t-1]-v[t-1]))*capacity);
        }
        else
            iapp1 = 0;
        if(x2[t]>v[t])
        {
            if(t==0)
                iapp2 = ((x2[t]-v[t])/R2);
            else
                iapp2 = (((x2[t]-v[t])/R2)+((x2[t]-v[t])-(x2[t-1]-v[t-1]))*capacity);
        }
        else
            iapp2 = 0;
        if(x3[t]>v[t])
        {
            if(t==0)
                iapp3 = ((x3[t]-v[t])/R3);
            else
                iapp3 = (((x3[t]-v[t])/R3)+((x3[t]-v[t])-(x3[t-1]-v[t-1]))*capacity);
        }
        else
            iapp3 = 0;
        if(x4[t]>v[t])
        {
            if(t==0)
                iapp4 = ((x4[t]-v[t])/R4);
            else
                iapp4 = (((x4[t]-v[t])/R4)+((x4[t]-v[t])-(x4[t-1]-v[t-1]))*capacity);
        }
        else
            iapp4 = 0;
        iapp = iapp1 + iapp2 + iapp3 + iapp4;
        I[t]=iapp;
        if(v[t]<35)
        {
            dv = (0.04*v[t]+5)*v[t]+140-u[t];
            v[t+1] = v[t]+(dv+iapp)*dt;
            du = a*(b*v[t]-u[t]);
            u[t+1] = u[t]+dt*du;
        }
        else
        {
            v[t] = 35;
            v[t+1] = c;
            u[t+1] = u[t] + d;
        }
    }
    return v;
}

double* Neuron::work(double* inputNeuronsVoltage[], double* R, int sizeTable)
{
    //double iapp1 = (( rand() % 5 ));
    double iapp1 = 0;
    int sizeInputNeuronsVoltage = sizeTable;
    for(int t=0; t<T; ++t)
    {
        iapp = 0;
        for(int i=0; i<sizeInputNeuronsVoltage; i++)
        {
            double* actualNeuronVoltage = inputNeuronsVoltage[i];
            if(actualNeuronVoltage[t]>v[t])
            {
                if(t==0)
                    iapp1 = ((actualNeuronVoltage[t]-v[t])/R[i]);
                else
                    iapp1 = (((actualNeuronVoltage[t]-v[t])/R[i])+((actualNeuronVoltage[t]-v[t])-(actualNeuronVoltage[t-1]-v[t-1]))*capacity);
            }
            else
                iapp1 = 0;
            iapp += iapp1;
        }
        I[t]=iapp;
        if(v[t]<35)
        {
            dv = (0.04*v[t]+5)*v[t]+140-u[t];
            v[t+1] = v[t]+(dv+iapp)*dt;
            du = a*(b*v[t]-u[t]);
            u[t+1] = u[t]+dt*du;
        }
        else
        {
            v[t] = 35;
            v[t+1] = c;
            u[t+1] = u[t] + d;
        }
    }
    return v;
}


double* Neuron::getVoltage()
{
    return v;
}

int Neuron::getTime()
{
    return T;
}

double Neuron::getDt()
{
    return dt;
}

double* Neuron::getI()
{
    return I;
}
