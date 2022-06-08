#ifndef NETWORK_H
#define NETWORK_H

#include "Neuron.h"

#include "randnumgen.hpp"
#include <QString>
#include <vector>

using namespace std;

class Network
{
public:
    Network(int amountNumbers, int inhibitoryNeuron, int numberInputNeurons);
    ~Network();
    double *getVoltagesOutput();
    double *simulatedAnnealing(int amountVariables);
    double* neuronY;
    Neuron *neuronYout;
    double* iY;
    double *simulatedAnnealingXOR(int amountVariables);
    void randGenerator();
    int architecture_2_4_1(double *r);
    int architecture_2_4_1_time_encoding(double *r);
    int architecture_X_N_1_time_encoding(double* R_input[], double* R_hide, int hideLayerNumber, int nrDataSet=1,
                                         int inputNeurons=15, bool show=false, int coding = 3, QString &textToTextBrowser = *new QString());
    vector<int>* imgConvertToCurrent(int imageNr, int nrDataSet, QString &textToTextBrowser = *new QString());
    double *neuronOut;
private:
    int numberInputNeurons;
    Neuron *neuron1;
    Neuron *neuron2;
    Neuron *neuron3;
    Neuron *neuron4;
    Neuron *neuron5;
    Neuron *neuron6;
    Neuron *neuron7;
    Neuron* inputNeurons[784];
    vector<Neuron*> hideNeurons;
    int inhibitoryNeuron;

    //double* x;
    int architecture_2_1(double *r);
    void randomNumbers(int amountNumbers, double *x);
};

#endif // NETWORK_H
