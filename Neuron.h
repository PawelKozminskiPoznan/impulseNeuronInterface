#ifndef NEURON_H
#define NEURON_H


class Neuron
{
public:
    Neuron(int start_one = 200, int end_one = 700, int start_second = 0, int end_second = 0, int start_third = 0, int end_third = 0, int start_fourth = 0, int end_fourth = 0, int start_fifth = 0, int end_fifth = 0, int start_sixth = 0, int end_sixth = 0, int T = 4000, double a = 0.02, double b = 0.2, double c = -65, double d = 8, double dt = 0.5);
    ~Neuron();
    // Neuron(int start_one = 200, int end_one = 700, int start_second = 0, int end_second = 0, int start_third = 0, int end_third = 0, int start_fourth = 0, int end_fourth = 0, int start_fifth = 0, int end_fifth = 0, int start_sixth = 0, int end_sixth = 0, int T = 4000, double a = 0.02, double d = 8);
    //double *work(int current = 7);
    double *work(int current1 = 7, int current2 = 0, int current3 = 0, int current4 = 0, int current5 = 0, int current6 = 0);
    double *work(const double *x, const double *x2, double R1 = 1, double R2 = 1);
    double *work(const double *x, const double *x2, const double *x3, const double *x4, double R1 = 1, double R2 = 1, double R3 = 1, double R4 = 1);
    double* work(double* inputNeuronsVoltage[], double* R, int sizeTable);
    double *getVoltage();
    int getTime();
    double getDt();
    double *getI();
private:
    double a,b,c,d,dt;
    int T;
    double *v;
    double *u;
    double iapp;
    double* I;
    double dv,du;
    int start_one, end_one;
    int start_second, end_second;
    int start_third, end_third;
    int start_fourth, end_fourth;
    int start_fifth, end_fifth;
    int start_sixth, end_sixth;
    double capacity;
};

#endif // NEURON_H
