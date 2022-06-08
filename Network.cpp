#include "Network.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <math.h>

#include <QDir>
#include <QImage>


using namespace std;


Network::Network(int amountNumbers, int inhibitoryNeuron, int numberInputNeurons)
{
    neuronY = nullptr;
//    neuron1 = new Neuron(0,500, 1000,1500, 2000,2500);
//    neuron2 = new Neuron(0,500, 1500,1700, 2000,2500);
    neuron1 = new Neuron(0,500, 1000,1500, 3000,3500);
    neuron2 = new Neuron(0,500, 2000,2500, 3000,3500);
    neuron3 = new Neuron(200,700, 0,0, 0,0, 4000, 0.1, 0.2, -65, 2, 0.5); // inhibitory neuron
    neuron4 = new Neuron(); //excitatory neurons
    neuron5 = new Neuron();
    neuron6 = new Neuron();
    neuron7 = new Neuron();
    this->inhibitoryNeuron = inhibitoryNeuron;

    //x = new double[amountNumbers];
    this->numberInputNeurons = numberInputNeurons;

    for(int i=0; i<numberInputNeurons; i++)
        inputNeurons[i] = new Neuron(500,1000, 1500,2000, 2500,3000, 3500,4000, 4500,5000, 5500,6000, 6500);
    neuronYout = new Neuron(0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 6500);
}

Network::~Network()
{
//    delete neuron1;
//    delete neuron2;
//    delete neuron3;
//    delete neuron4;
//    delete neuron5;
//    delete neuron6;
//    delete neuron7;
//    for(int i=0; i<numberInputNeurons; i++)
//        delete inputNeurons[i];
//    delete neuronYout;
}

int Network::architecture_2_1(double* r)
{
     double *neuronX1 = neuron1->work();
     double *neuronX2 = neuron2->work();

     double* R = r;
     neuronY = neuron3->work(neuronX1, neuronX2, R[0], R[1]);

     int count = 0;
     int count2 = 0;
     int count3 = 0;
     int count4 = 0;
     int count5 = 0;
     int count6 = 0;
     int count7 = 0;
     for(int i = 6000; i<7000; i++) //(1,1)
     {
         if(neuronY[i] == 35.0)
         {
             count++;
           cout<<i<<endl;
         }
     }
     for(int i = 2000; i<2500; i++) //(0,1)a
     {
         if(neuronY[i] == 35.0)
         {
             count2++;
           cout<<i<<endl;
         }
     }
     for(int i = 2500; i<3000; i++) //(0,1)b
     {
         if(neuronY[i] == 35.0)
         {
             count3++;
           cout<<i<<endl;
         }
     }
     for(int i = 4000; i<4500; i++) //(1,0)a
     {
         if(neuronY[i] == 35.0)
         {
             count4++;
           cout<<i<<endl;
         }
     }
     for(int i = 4500; i<4750; i++) //(1,0)b1
     {
         if(neuronY[i] == 35.0)
         {
             count5++;
           cout<<i<<endl;
         }
     }
     for(int i = 4750; i<4850; i++) //(1,0)b2a
     {
         if(neuronY[i] == 35.0)
         {
             count6++;
           cout<<i<<endl;
         }
     }
     for(int i = 4850; i<5000; i++) //(1,0)b2b
     {
         if(neuronY[i] == 35.0)
         {
             count7++;
           cout<<i<<endl;
         }
     }
     iY = neuron3->getI();
     int result = pow((8-(count)),2)+pow(((2-count2)),2)+pow(((2-count3)),2)+pow(((2-count4)),2)+pow(((1-count5)),2)+pow(((1-count6)),2); //AND
     //int result = pow((24-(count+count2+count3+count4+count5)),2);  //OR
     if(count == 0 or count7 > 0)
         result = 200;
     return result;
}


int Network::architecture_2_4_1(double* r)
{
    double *neuronX1 = neuron1->work();
    double *neuronX2 = neuron2->work();

    double* R = r;

    double *neuronZ3 = neuron3->work(neuronX1, neuronX2, R[0], R[1]);
    double *neuronZ4 = neuron4->work(neuronX1, neuronX2, R[2], R[3]);
    double *neuronZ5 = neuron5->work(neuronX1, neuronX2, R[4], R[5]);
    double *neuronZ6 = neuron6->work(neuronX1, neuronX2, R[6], R[7]);

    neuronY = neuron7->work(neuronZ3, neuronZ4, neuronZ5, neuronZ6, R[8], R[9], R[10], R[11]);

    int count = 0;
    int count2 = 0;
    int count3 = 0;
    int count4 = 0;
    int countA = 0;
    int countB = 0;
    int countC = 0;
    int countD = 0;
    int countE = 0;
    int countF = 0;
    int countG = 0;
    int countH = 0;
//    for(int i = 5950; i<7050; i++) //(1,1)
//    {
//        if(neuronY[i] == 35.0)
//            count++;
//    }
    for(int i = 5990; i<6125; i++) //(1,1)
    {
        if(neuronY[i] == 35.0)
            countA++;
    }
    for(int i = 6126; i<6250; i++) //(1,1)
    {
        if(neuronY[i] == 35.0)
            countB++;
    }
    for(int i = 6251; i<6375; i++) //(1,1)
    {
        if(neuronY[i] == 35.0)
            countC++;
    }
    for(int i = 6375; i<6500; i++) //(1,1)
    {
        if(neuronY[i] == 35.0)
            countD++;
    }
    for(int i = 6501; i<6625; i++) //(1,1)
    {
        if(neuronY[i] == 35.0)
            countE++;
    }
    for(int i = 6626; i<6750; i++) //(1,1)
    {
        if(neuronY[i] == 35.0)
            countF++;
    }
    for(int i = 6751; i<6875; i++) //(1,1)
    {
        if(neuronY[i] == 35.0)
            countG++;
    }
    for(int i = 6876; i<7010; i++) //(1,1)
    {
        if(neuronY[i] == 35.0)
            countH++;
    }
    ////////
    for(int i = 2000; i<3000; i++) //(0,1)
    {
        if(neuronY[i] == 35.0)
            count2++;
    }
    for(int i = 4000; i<5000; i++) //(1,0)
    {
        if(neuronY[i] == 35.0)
            count3++;
    }

    for(int i = 1000; i<2000; i++)
    {
        if(neuronY[i] == 35.0)
            count4++;
    }
    for(int i = 3000; i<4000; i++)
    {
        if(neuronY[i] == 35.0)
            count4++;
    }
    for(int i = 5000; i<6000; i++)
    {
        if(neuronY[i] == 35.0)
            count4++;
    }

    iY = neuron7->getI();
    //cout<<count<<" %%%%% "<<count2<<" "<<endl;
    int result = pow((8-count3),2) + pow((8-count2),2) + pow(count4,2) + pow(4-(4*countA),2) + pow(countB*4,2) + pow(4-(4*countC),2) + pow(countD*4,2) + pow(4-(4*countE),2) + pow(countF*4,2) + pow(4-(4*countG),2) + pow(countH*4,2); //XOR  dla zero 2x mniejsze Hz //pow((8-(2*count)),2)
//    if(result == 0)
//        cout<<"a "<<result<<endl;
    //int result = pow((16-(count2+count3)),2) + pow((count),2); //XOR  dla zero brak pulsowania
    if(result == 0)
    {
        for(int i = 2000; i<3000; i++) //(0,1)
        {
            if(neuronY[i] == 35.0){
                count2++;
            cout<<i<<endl;}
        }
        for(int i = 4000; i<5000; i++) //(1,0)
        {
            if(neuronY[i] == 35.0){
                count3++;
                cout<<i<<endl;
            cout<< pow((8-count3),2)<<endl;}
        }
    }
    if(count2 == 0)
        result = 200;
    return result;
}

int Network::architecture_2_4_1_time_encoding(double* r)
{
    double *neuronX1 = neuron1->work();
    double *neuronX2 = neuron2->work();

    double* R = r;

    double *neuronZ3 = neuron3->work(neuronX1, neuronX2, R[0], R[1]);
    double *neuronZ4 = neuron4->work(neuronX1, neuronX2, R[2], R[3]);
    double *neuronZ5 = neuron5->work(neuronX1, neuronX2, R[4], R[5]);
    double *neuronZ6 = neuron6->work(neuronX1, neuronX2, R[6], R[7]);

    neuronY = neuron7->work(neuronZ3, neuronZ4, neuronZ5, neuronZ6, R[8], R[9], R[10], R[11]);

    int count = 0;
    int count2 = 0;
    int count3 = 0;
    int count4 = 0;

    for(int i = 2000; i<2050; i++) //(1,1)
    {
        if(neuronY[i] == 35.0)
            count++;
    }
    for(int i = 4000; i<4050; i++) //(1,1)
    {
        if(neuronY[i] == 35.0)
            count2++;
    }
    for(int i = 6050; i<6200; i++) //(1,1)
    {
        if(neuronY[i] == 35.0)
            count3++;
    }

    for(int i = 1000; i<2000; i++)
    {
        if(neuronY[i] == 35.0)
            count4++;
    }
    for(int i = 3000; i<4000; i++)
    {
        if(neuronY[i] == 35.0)
            count4++;
    }
    for(int i = 5000; i<6000; i++)
    {
        if(neuronY[i] == 35.0)
            count4++;
    }

    int count5 = 0;
    int count6 = 0;
    int count7 = 0;

    for(int i = 2100; i<3000; i++) //(0,1)
    {
        if(neuronY[i] == 35.0)
            count4++;
    }
    for(int i = 4100; i<5000; i++) //(1,0)
    {
        if(neuronY[i] == 35.0)
            count4++;
    }
    for(int i = 6200; i<7000; i++) //(1,1)
    {
        if(neuronY[i] == 35.0)
            count4++;
    }

    iY = neuron7->getI();
    int result = pow((1-count)*3,2) + pow((1-count2)*3,2) + pow((1-count3)*3,2) + pow(count4,2);
    if(count2 == 0)
        result = 200;
    return result;
}


double* Network::simulatedAnnealingXOR(int amountVariables)
{

    //double temperature = 0.9;
    //double temperatureMin = 0.656;
    double* variables = new double[amountVariables];
      // variables[0] = 25.5; variables[1] = 29.5;variables[2] = 2.1; variables[3] = 1.9;variables[4] = 20.2; variables[5] = 27.4;
      // variables[6] = 28.1; variables[7] = 47.2;variables[8] = 32.7; variables[9] = 4.3;variables[10] = 5.4; variables[11] = 18.8;
     variables[0] = 1; variables[1] = 1;variables[2] = 1.9; variables[3] = 1.9;variables[4] = 39.3; variables[5] = 36.4;
     variables[6] = 2.2; variables[7] = 1.2;variables[8] = 46.8; variables[9] = 5.6;variables[10] = 44.5; variables[11] = 44.2;
    double* variablesPrim = new double[amountVariables];
    int L = 1;
    //while(temperature >= temperatureMin)
    //{
        for(int i=0; i<L; i++)
        {
             randomNumbers(amountVariables, variablesPrim);

           // double x = rand()%1001 / 1000.0;
           // double y = exp(-(architecture_2_4_1(variablesPrim) - architecture_2_4_1(variables))/temperature);
            if(architecture_2_4_1(variablesPrim) <= architecture_2_4_1(variables))
            {
                for(int i=0; i < amountVariables; i++)
                    variables[i] = variablesPrim[i];
                cout<<architecture_2_4_1(variablesPrim)<<" prim vs  "<<architecture_2_4_1(variables)<<" ="<<i<<endl;
                for(int i =0; i<amountVariables; i++)
                    cout<<variables[i]<<endl;
            }
            //else if(x < y)
                //variables = variablesPrim;
            if(architecture_2_4_1(variables) == 0)
                break;
        }
     //   temperature = temperature * 0.9;
  //  }
    cout<<architecture_2_4_1(variables)<<endl;
    return variables;
}


double* Network::simulatedAnnealing(int amountVariables)
{

    //double temperature = 0.9;
    //double temperatureMin = 0.656;
    double* variables = new double[amountVariables]; variables[0] = 4; variables[1] = 4;//new double[amountVariables]; //new double[amountVariables]; variables[0] = 8.9; variables[1] = 8.7;//
    double* variablesPrim = new double[amountVariables];
    randomNumbers(amountVariables, variables);
    randomNumbers(amountVariables, variablesPrim);
    int L = 100000;
    //while(temperature >= temperatureMin)
    //{
        for(int i=0; i<L; i++)
        {
             randomNumbers(amountVariables, variablesPrim);

           // double x = rand()%1001 / 1000.0;
           // double y = exp(-(architecture_2_4_1(variablesPrim) - architecture_2_4_1(variables))/temperature);
            if(architecture_2_1(variablesPrim) <= architecture_2_1(variables))
            {
                for(int i=0; i < amountVariables; i++)
                    variables[i] = variablesPrim[i];
                cout<<architecture_2_1(variablesPrim)<<" prim vs  "<<architecture_2_1(variables)<<" ="<<i<<endl;
                for(int i =0; i<amountVariables; i++)
                    cout<<variables[i]<<endl;
            }
            //else if(x < y)
                //variables = variablesPrim;
            //cout<<architecture_2_1(variables)<<endl;
            if(architecture_2_1(variables) == 0)
                break;
        }
     //   temperature = temperature * 0.9;
  //  }
    return variables;
}

void Network::randomNumbers(int amountNumbers, double* b)
{
    for(int i=0; i < amountNumbers; i++)
        b[i] = getRandomIntegerInRange<size_t>(0, 501)/10.0;
        //b[i] = (( rand() % 500 ) + 1)/10.0;

}

double* Network::getVoltagesOutput()
{
    return neuronY;
}

void Network::randGenerator()
{
    int L = 100000;
    int* random = new int[L];
    for(int i=0; i<L; i++)
    {
        random[i] =  getRandomIntegerInRange<size_t>(0, 501);//( rand() % 501 );
    }
    neuronY = new double[500];
    int* osX = new int[500];
    for(int i=0; i<500; i++)
    {
        neuronY[i]=0;
        osX[i]=i;
    }
    int x;
    for(int i=0; i<L; i++)
    {
        x = random[i];
        neuronY[x]++;
    }
}


vector<int>* Network::imgConvertToCurrent(int imageNr, int nrDataSet, QString &textToTextBrowser)
{
    vector<int>* currentFromImage = new vector<int> ;
    string imageNrString = to_string(imageNr);
    string set;
    QString pathS;
    set = "Selected input data:\n ";
    string input = "Input date from = ";
    switch (nrDataSet)
    {
        case 1:
           set += "Liczby 1-6 w formacie 3x5\n";
           set += " czarno-białe\n";
           pathS = QDir::currentPath();
           pathS += QString::fromStdString("/numbers/3na5/czarno_biale/");
           input += pathS.toStdString();
           pathS += QString::fromStdString(imageNrString);
           pathS.append(".png");
           break;
        case 2:
           set += "Liczby 1-6 w formacie 3x5\n";
           set += " zestaw 1\n";
           pathS = QDir::currentPath();
           pathS += QString::fromStdString("/numbers/3na5/szare1/");
           input += pathS.toStdString();
           pathS += QString::fromStdString(imageNrString);
           pathS.append("_sz.png");
           break;
        case 4:
           set += "Liczby 1-6 w formacie 3x5\n";
           set += " zestaw 2\n";
           pathS = QDir::currentPath();
           pathS += QString::fromStdString("/numbers/3na5/szare2/");
           input += pathS.toStdString();
           pathS += QString::fromStdString(imageNrString);
           pathS.append("_sz.png");
           break;
        case 8:
           set += "Liczby 1-6 w formacie 3x5\n";
           set += " zestaw 3\n";
           pathS = QDir::currentPath();
           pathS += QString::fromStdString("/numbers/3na5/szare3/");
           input += pathS.toStdString();
           pathS += QString::fromStdString(imageNrString);
           pathS.append("_sz.png");
           break;
        case 16:
           set += "Liczby 1-6 w formacie 3x5\n";
           set += " zestaw 4\n";
           pathS = QDir::currentPath();
           pathS += QString::fromStdString("/numbers/3na5/szare4/");
           input += pathS.toStdString();
           pathS += QString::fromStdString(imageNrString);
           pathS.append("_sz.png");
           break;
        case 32:
           set += "Liczby 1-6 w formacie 28x28 MNIST\n";
           set += " zestaw 1\n";
           pathS = QDir::currentPath();
           pathS += QString::fromStdString("/numbers/MNIST/zestaw_1/");
           input += pathS.toStdString();
           pathS += QString::fromStdString(imageNrString);
           pathS.append(".png");
           break;
        case 64:
            set += "Liczby 1-6 w formacie 28x28 MNIST\n";
            set += " zestaw 2\n";
            pathS = QDir::currentPath();
            pathS += QString::fromStdString("/numbers/MNIST/zestaw_2/");
            input += pathS.toStdString();
            pathS += QString::fromStdString(imageNrString);
            pathS.append(".png");
            break;
        case 128:
            set += "Liczby 1-6 w formacie 28x28 MNIST\n";
            set += " zestaw 3\n";
            pathS = QDir::currentPath();
            pathS += QString::fromStdString("/numbers/MNIST/zestaw_3/");
            input += pathS.toStdString();
            pathS += QString::fromStdString(imageNrString);
            pathS.append(".png");
            break;
        case 256:
            set += "Liczby 1-6 w formacie 28x28 MNIST\n";
            set += " zestaw 4\n";
            pathS = QDir::currentPath();
            pathS += QString::fromStdString("/numbers/MNIST/zestaw_4/");
            input += pathS.toStdString();
            pathS += QString::fromStdString(imageNrString);
            pathS.append(".png");
            break;
    }
    set += "\n";
    QString path = QString::fromStdString(set);
    textToTextBrowser += path;
    path = QString::fromStdString(input);
    textToTextBrowser += path + "\n\n";
    path = pathS;
    cout<<path.toStdString()<<endl;
    QImage pix;
    pix.load(path);
    //cout<<pix.isNull()<<endl<<endl;
    if(!pix.isNull())
    {
        int x,y;
        x = pix.height();
        y = pix.width();
        for(int i=0; i<x; i++)
        {
            for(int j=0; j<y; j++)
            {
                QColor pixel(pix.pixel(j,i));
                int current = 0;
//                switch(pixel.red()) {
//                  case 255:
//                    current = 0;
//                    break;
//                  case 192:
//                    current = 10;
//                    break;
//                  case 128:
//                    current = 20;
//                    break;
//                  case 64:
//                     current = 30;
//                    break;
//                  case 0:
//                     current = 40;
//                    break;
//              }
                current = 40 - (pixel.red()/6.375);
                currentFromImage->push_back(current);
            }
        }
    }
    return currentFromImage;
}


int Network::architecture_X_N_1_time_encoding(double* R_input[], double* R_hide, int hideLayerNumber, int nrDataSet, int inputNumberNeuron, bool show, int coding, QString &textToTextBrowser)
{
    textToTextBrowser += "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n";

    vector<int>* currentFromImage1 = imgConvertToCurrent(1, nrDataSet, textToTextBrowser);
    vector<int>* currentFromImage2 = imgConvertToCurrent(2, nrDataSet);
    vector<int>* currentFromImage3 = imgConvertToCurrent(3, nrDataSet);
    vector<int>* currentFromImage4 = imgConvertToCurrent(4, nrDataSet);
    vector<int>* currentFromImage5 = imgConvertToCurrent(5, nrDataSet);
    vector<int>* currentFromImage6 = imgConvertToCurrent(6, nrDataSet);

    //wartstwa wejściowa
    double* inputNeuronsVoltage[inputNumberNeuron];
    for(size_t i=0; i<inputNumberNeuron; i++)
        inputNeuronsVoltage[i] = inputNeurons[i]->work(currentFromImage1->at(i), currentFromImage2->at(i), currentFromImage3->at(i), currentFromImage4->at(i), currentFromImage5->at(i), currentFromImage6->at(i));

    //warstwa ukryta
    int numberLuckNeurons = 0;
    if(hideNeurons.size() < hideLayerNumber)
        numberLuckNeurons =  hideLayerNumber - hideNeurons.size();

    for(int i=0; i<numberLuckNeurons; i++)
    {
        Neuron* tempNeuron;
        if((i+1)%inhibitoryNeuron == 0)
            tempNeuron = new Neuron(0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 6500, 0.1, 0.2, -65, 2, 0.5);
        else
            tempNeuron = new Neuron(0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 6500);
        hideNeurons.push_back(tempNeuron);
    }
    if(show)
    {
        cout<<"Inhibitory to exicitatory neurons = 1/"<<inhibitoryNeuron<<endl;
        textToTextBrowser += "Inhibitory to exicitatory neurons = 1/" + QString::number(inhibitoryNeuron) + "\n\n";
    }
cout<<"610"<<endl;
    double* hideNeuronsVoltage[hideLayerNumber];
    for(size_t i=0; i<hideLayerNumber; i++)
        hideNeuronsVoltage[i] = hideNeurons[i]->work(inputNeuronsVoltage, R_input[i], inputNumberNeuron);

    //wyjście
    neuronOut = neuronYout->work(hideNeuronsVoltage, R_hide, hideLayerNumber);

    int count = 0;
    int count2 = 0;
    int count3 = 0;
    int count4 = 0;
    int count5 = 0;
    int count6 = 0;

    int onecount = 0;
    int onecount2 = 0;
    int onecount3 = 0;
    int onecount4 = 0;
    int onecount5 = 0;
    int onecount6 = 0;

    int countZero = 0;

//encoding by first impulse
    for(int i = 1000; i<2000; i++) //1
    {
        if(neuronOut[i] == 35.0)
        {
            count = i - 1000;
            onecount = i - 1000;
            break;
        }
    }
    for(int i = 3000; i<4000; i++) //2
    {
        if(neuronOut[i] == 35.0)
        {
            count2 = i - 3000;
            onecount2 = i - 3000;
            break;
        }
    }
    for(int i = 5000; i<6000; i++) //3
    {
        if(neuronOut[i] == 35.0)
        {
            count3 = i - 5000;
            onecount3 = i - 5000;
            break;
        }
    }
    for(int i = 7000; i<8000; i++)//4
    {
        if(neuronOut[i] == 35.0)
        {
            count4 = i - 7000;
            onecount4 = i - 7000;
            break;
        }
    }
    for(int i = 9000; i<10000; i++)//5
    {
        if(neuronOut[i] == 35.0)
        {
            count5 = i - 9000;
            onecount5 = i - 9000;
            break;
        }
    }
    for(int i = 11000; i<12000; i++)//6
    {
        if(neuronOut[i] == 35.0)
        {
            count6 = i - 11000;
            onecount6 = i - 11000;
            break;
        }
    }


//encoding by second impulse
    if(coding == 4)
    {
        int countTo2 = 0;
        for(int i = 1000; i<2000; i++) //1
        {
            if(neuronOut[i] == 35.0)
            {
                countTo2++;
                if(countTo2 == 2)
                {
                    count += i - 1000;
                    break;
                }
            }
        }
        countTo2 = 0;
        for(int i = 3000; i<4000; i++) //2
        {
            if(neuronOut[i] == 35.0)
            {
                countTo2++;
                if(countTo2 == 2)
                {
                    count2 += i - 3000;
                    break;
                }
            }
        }
        countTo2 = 0;
        for(int i = 5000; i<6000; i++) //3
        {
            if(neuronOut[i] == 35.0)
            {
                countTo2++;
                if(countTo2 == 2)
                {
                    count3 += i - 5000;
                    break;
                }
            }
        }
        countTo2 = 0;
        for(int i = 7000; i<8000; i++)//4
        {
            if(neuronOut[i] == 35.0)
            {
                countTo2++;
                if(countTo2 == 2)
                {
                    count4 += i - 7000;
                    break;
                }
            }
        }
        countTo2 = 0;
        for(int i = 9000; i<10000; i++)//5
        {
            if(neuronOut[i] == 35.0)
            {
                countTo2++;
                if(countTo2 == 2)
                {
                    count5 += i - 9000;
                    break;
                }
            }
        }
        countTo2 = 0;
        for(int i = 11000; i<12000; i++)//6
        {
            if(neuronOut[i] == 35.0)
            {
                countTo2++;
                if(countTo2 == 2)
                {
                    count6 += i - 11000;
                    break;
                }
            }
        }
    }


    for(int i = 0; i<1000; i++)
    {
        if(neuronOut[i] == 35.0)
            countZero++;
    }
    for(int i = 2000; i<3000; i++)
    {
        if(neuronOut[i] == 35.0)
            countZero++;
    }
    for(int i = 4000; i<5000; i++)
    {
        if(neuronOut[i] == 35.0)
            countZero++;
    }
    for(int i = 6000; i<7000; i++)
    {
        if(neuronOut[i] == 35.0)
            countZero++;
    }
    for(int i = 8000; i<9000; i++)
    {
        if(neuronOut[i] == 35.0)
            countZero++;
    }
    for(int i = 10000; i<11000; i++)
    {
        if(neuronOut[i] == 35.0)
            countZero++;
    }
    for(int i = 12000; i<13000; i++)
    {
        if(neuronOut[i] == 35.0)
            countZero++;
    }

    int result = 0;
    if(onecount == 0)
        result += 500;
    if(onecount3 == 0)
        result += 500;
    if(onecount5 == 0)
        result += 500;
    if(onecount2 == 0)
        result += 10000;
    if(onecount4 == 0)
        result += 10000;
    if(onecount6 == 0)
        result += 10000;

    if(coding == 4)
    {
        if(count == onecount)
            result += 500;
        if(count3 == onecount3)
            result += 500;
        if(count5 == onecount5)
            result += 500;
        if(count2 == onecount2)
            result += 1000;
        if(count4 == onecount4)
            result += 1000;
        if(count6 == onecount6)
            result += 1000;
    }

//    bool luckOfEvenImpulse = false;
//    if(count2 == 0 || count4 == 0 || count6 == 0)
//        luckOfEvenImpulse = true;

//    if(count == 0 && !luckOfEvenImpulse)
//        count = 1000;
//    if(count3 == 0 && !luckOfEvenImpulse)
//        count3 = 1000;
//    if(count5 == 0 && !luckOfEvenImpulse)
//        count5 = 1000;

    int minOdd;
    int maxEven;
    bool allOddZero = false;
    bool allEvenZero = false;
    if(coding == 3)
    {
        if(count == 0 && count3 == 0 && count5 == 0)
        {
            minOdd = 0;
            allOddZero = true;
        }
        else if(count == 0 && count3 == 0)
            minOdd = count5;
        else if(count3 == 0 && count5 == 0)
            minOdd = count;
        else if(count == 0 && count5 == 0)
            minOdd = count3;
        else if(count == 0)
            minOdd = min(count5, count3);
        else if(count3 == 0)
            minOdd = min(count, count5);
        else if(count5 == 0)
            minOdd = min(count, count3);
        else
            minOdd = min(min(count, count3),count5);
        if(count2 == 0 || count4 == 0 || count6 == 0)
        {
            allEvenZero = true;
            maxEven = 1000000;
        }
        else
            maxEven = max(max(count2, count4),count6);
    }
    else if(coding == 4)
    {
        if((count == 0 && count3 == 0 && count5 == 0) || (count == onecount && count3 == onecount3 && count5 == onecount5))
        {
            minOdd = 0;
            allOddZero = true;
        }
        else if((count == 0 && count3 == 0)||(count == onecount && count3 == onecount3))
            minOdd = count5;
        else if((count3 == 0 && count5 == 0)||(count3 == onecount3 && count5 == onecount5))
            minOdd = count;
        else if((count == 0 && count5 == 0)||(count == onecount && count5 == onecount5))
            minOdd = count3;
        else if(count == 0 || count == onecount)
            minOdd = min(count5, count3);
        else if(count3 == 0 || count3 == onecount3)
            minOdd = min(count, count5);
        else if(count5 == 0 || count5 == onecount5)
            minOdd = min(count, count3);
        else
            minOdd = min(min(count, count3),count5);
        if((count2 == 0 || count4 == 0 || count6 == 0) || (count2 == onecount2 || count4 == onecount4 || count6 == onecount6))
        {
            allEvenZero = true;
            maxEven = 1000000;
        }
        else
            maxEven = max(max(count2, count4),count6);
    }
    if(show)
    {
        cout<<"Time of first spike for numbers:"<<endl;
        if(onecount == 0)
            cout<<"1: "<<"- ms"<<endl;
        else
            cout<<"1: "<<onecount/2.0<<" ms"<<endl;
        if(onecount2 == 0)
            cout<<"2: "<<"- ms"<<endl;
        else
            cout<<"2: "<<onecount2/2.0<<" ms"<<endl;
        if(onecount3 == 0)
            cout<<"3: "<<"- ms"<<endl;
        else
            cout<<"3: "<<onecount3/2.0<<" ms"<<endl;
        if(onecount4 == 0)
            cout<<"4: "<<"- ms"<<endl;
        else
            cout<<"4: "<<onecount4/2.0<<" ms"<<endl;
        if(onecount5 == 0)
            cout<<"5: "<<"- ms"<<endl;
        else
            cout<<"5: "<<onecount5/2.0<<" ms"<<endl;
        if(onecount6 == 0)
            cout<<"6: "<<"- ms"<<endl<<endl;
        else
            cout<<"6: "<<onecount6/2.0<<" ms"<<endl;

        if(coding == 4)
        {
            cout<<"Sum time of first and second spike for numbers:"<<endl;
            if(onecount == count)
                cout<<"1: "<<"- ms"<<endl;
            else
                cout<<"1: "<<count/2.0<<" ms"<<endl;
            if(onecount2 == count2)
                cout<<"2: "<<"- ms"<<endl;
            else
                cout<<"2: "<<count2/2.0<<" ms"<<endl;
            if(onecount3 == count3)
                cout<<"3: "<<"- ms"<<endl;
            else
                cout<<"3: "<<count3/2.0<<" ms"<<endl;
            if(onecount4 == count4)
                cout<<"4: "<<"- ms"<<endl;
            else
                cout<<"4: "<<count4/2.0<<" ms"<<endl;
            if(onecount5 == count5)
                cout<<"5: "<<"- ms"<<endl;
            else
                cout<<"5: "<<count5/2.0<<" ms"<<endl;
            if(onecount6 == count6)
                cout<<"6: "<<"- ms"<<endl<<endl;
            else
                cout<<"6: "<<count6/2.0<<" ms"<<endl;
        }
        if(allOddZero)
            cout<<"Minimal time for odd numbers: - "<<endl;
        else
            cout<<"Minimal time for odd numbers: "<<minOdd/2.0<<endl;
        if(allEvenZero)
            cout<<"Maximal time for even numbers: - "<<endl;
        else
            cout<<"Maximal time for even numbers: "<<maxEven/2.0<<endl;

        //textBrowser
        textToTextBrowser += "Time of first spike for numbers:\n";
        if(count == 0)
            textToTextBrowser += "1: - ms\n";
        else
            textToTextBrowser += "1: " + QString::number(onecount/2.0) + " ms\n";
        if(count2 == 0)
            textToTextBrowser += "2: - ms\n";
        else
            textToTextBrowser += "2: " + QString::number(onecount2/2.0) + " ms\n";
        if(count3 == 0)
            textToTextBrowser += "3: - ms\n";
        else
            textToTextBrowser += "3: " + QString::number(onecount3/2.0) + " ms\n";
        if(count4 == 0)
            textToTextBrowser += "4: - ms\n";
        else
            textToTextBrowser += "4: " + QString::number(onecount4/2.0) + " ms\n";
        if(count5 == 0)
            textToTextBrowser += "5: - ms\n";
        else
            textToTextBrowser += "5: " + QString::number(onecount5/2.0) + " ms\n";
        if(count6 == 0)
            textToTextBrowser += "6: - ms\n";
        else
            textToTextBrowser += "6: " + QString::number(onecount6/2.0) + " ms\n\n";

        if(coding == 4)
        {
            textToTextBrowser += "Sum time of first and second spike for numbers:\n";
            if(onecount == count)
                textToTextBrowser += "1: - ms\n";
            else
                textToTextBrowser += "1: " + QString::number(count/2.0) + " ms\n";
            if(onecount2 == count2)
                textToTextBrowser += "2: - ms\n";
            else
                textToTextBrowser += "2: " + QString::number(count2/2.0) + " ms\n";
            if(onecount3 == count3)
                textToTextBrowser += "3: - ms\n";
            else
                textToTextBrowser += "3: " + QString::number(count3/2.0) + " ms\n";
            if(onecount4 == count4)
                textToTextBrowser += "4: - ms\n";
            else
                textToTextBrowser += "4: " + QString::number(count4/2.0) + " ms\n";
            if(onecount5 == count5)
                textToTextBrowser += "5: - ms\n";
            else
                textToTextBrowser += "5: " + QString::number(count5/2.0) + " ms\n";
            if(onecount6 == count6)
                textToTextBrowser += "6: - ms\n";
            else
                textToTextBrowser += "6: " + QString::number(count6/2.0) + " ms\n";
        }
        if(allOddZero)
            textToTextBrowser += "Minimal time for odd numbers: - ms\n";
        else
            textToTextBrowser += "Minimal time for odd numbers: " + QString::number(minOdd/2.0) + " ms\n";
        if(allEvenZero)
            textToTextBrowser += "Maximal time for even numbers: - ms\n\n";
        else
            textToTextBrowser += "Maximal time for even numbers: " + QString::number(maxEven/2.0) + " ms\n\n";

    }
    iY = neuronYout->getI();
    //int result = pow(count*2,2) + pow((1-count2)*3,2) + pow(count3*2,2) + pow((1-count4)*3,2) + pow(count5*2,2) + pow((1-count6)*3,2) + pow(countZero,2);
    if(onecount == 0)
        textToTextBrowser +=  "Luck of first impuls on number 1: result += 500\n";
    if(onecount2 == 0)
        textToTextBrowser += "Luck of first impuls on number 2: result += 10000\n";
    if(onecount3 == 0)
        textToTextBrowser += "Luck of first impuls on number 3: result += 500\n";
    if(onecount4 == 0)
        textToTextBrowser += "Luck of first impuls on number 4: result += 10000\n";
    if(onecount5 == 0)
        textToTextBrowser += "Luck of first impuls on number 5: result += 500\n";
    if(onecount6 == 0)
        textToTextBrowser += "Luck of first impuls on number 6: result += 10000\n";
    textToTextBrowser += "\n";
    if(coding == 4)
    {
        if(count == onecount)
            textToTextBrowser += "Luck of second impuls on number 1: result += 500\n";
        if(count2 == onecount2)
            textToTextBrowser += "Luck of second impuls on number 2: result += 1000\n";
        if(count3 == onecount3)
            textToTextBrowser += "Luck of second impuls on number 3: result += 500\n";
        if(count4 == onecount4)
            textToTextBrowser += "Luck of second impuls on number 4: result += 1000\n";
        if(count5 == onecount5)
            textToTextBrowser += "Luck of second impuls on number 5: result += 500\n";
        if(count6 == onecount6)
            textToTextBrowser += "Luck of second impuls on number 6: result += 1000\n";
        textToTextBrowser += "\n";
    }
    if(countZero > 0)
    {
        textToTextBrowser += "Number of impulses when no input: results += ";
        textToTextBrowser += QString::number(countZero);
        textToTextBrowser += " * 10000\n\n";
    }

    result += countZero*10000;
    if(!allEvenZero)
    {
        if(minOdd > maxEven+1)
        {
            double x = (minOdd - maxEven)/2.0;
            textToTextBrowser += "Correct (Minimal time for odd numbers > Maximal time for even), difference is equal = ";
            textToTextBrowser += QString::number(x);
            textToTextBrowser += " ms ";
        }
        else if(minOdd > maxEven)
        {
            result += 20;
            textToTextBrowser += "Correct (Minimal time for odd numbers > Maximal time for even), but difference is too small = 0.5 ms ";
            textToTextBrowser += "\nresults += 20\n\n";
        }
        else if(minOdd == maxEven)
        {
            result += 40;
            textToTextBrowser += "Incorrct (Minimal time for odd numbers == Maximal time for even)";
            textToTextBrowser += "\nresults += 40\n\n";
        }
        else if(minOdd < maxEven)
        {
            result += (maxEven - minOdd)*20+40;
            int y = (maxEven - minOdd)*20+40;
            double x = (maxEven - minOdd)/2.0;
            textToTextBrowser += "Incorrect (Maximal time for even > Minimal time for odd numbers), difference is equal = ";
            textToTextBrowser += QString::number(x);
            textToTextBrowser += " ms\n";
            textToTextBrowser += "dt = 0.5 ms";
            textToTextBrowser += "\nresults += ";
            textToTextBrowser += QString::number(x*2);
            textToTextBrowser += " * 20 + 40 (results += ";
            textToTextBrowser += QString::number(y);
            textToTextBrowser += ")\n\n";
        }

        if(count2+1 < count && count2+1 < count3)
            result += 0;
        else if(count2+1 < count && count2 < count3)
            result += 1;
        else if(count2 < count && count2+1 < count3)
            result += 1;
        else if(count2 < count && count2 < count3)
            result += 2;
        else if(count2 == count && count2+1 < count3)
            result += 2;
        else if(count2+1 < count && count2 == count3)
            result += 2;
        else if(count2 < count && count2 == count3)
            result += 3;
        else if(count2 == count && count2 < count3)
            result += 3;
        else if(count2+1 < count && count2 > count3)
            result += 3;
        else if(count2 > count && count2+1 < count3)
            result += 3;
        else if(count2 == count && count2 == count3)
            result += 4;
        else if(count2 < count && count2 > count3)
            result += 4;
        else if(count2 > count && count2 < count3)
            result += 4;
        else if(count2 > count && count2 == count3)
            result += 5;
        else if(count2 == count && count2 > count3)
            result += 5;
        else if(count2 > count && count2 > count3)
            result += 6;

        if(count4+1 < count3 && count4+1 < count5)
            result += 0;
        else if(count4+1 < count3 && count4 < count5)
            result += 1;
        else if(count4 < count3 && count4+1 < count5)
            result += 1;
        else if(count4 < count3 && count4 < count5)
            result += 2;
        else if(count4 == count3 && count4+1 < count5)
            result += 2;
        else if(count4+1 < count3 && count4 == count5)
            result += 2;
        else if(count4 < count3 && count4 == count5)
            result += 3;
        else if(count4+1 < count3 && count4 > count5)
            result += 3;
        else if(count4 > count3 && count4+1 < count5)
            result += 3;
        else if(count4 == count3 && count4 < count5)
            result += 3;
        else if(count4 == count3 && count4 == count5)
            result += 4;
        else if(count4 < count3 && count4 > count5)
            result += 4;
        else if(count4 > count3 && count4 < count5)
            result += 4;
        else if(count4 > count3 && count4 == count5)
            result += 5;
        else if(count4 == count3 && count4 > count5)
            result += 5;
        else if(count4 > count3 && count4 > count5)
            result += 6;

        if(count6+1 < count5)
            result += 0;
        else if(count6 < count5)
            result += 1;
        else if(count6 == count5)
            result += 2;
        else if(count6 > count5)
            result += 3;

        if(count2+1 < count && count2+1 < count3)
        {
            textToTextBrowser += "Correct (spike time 2 < spike time 1), difference >= 1 ms \n";
            textToTextBrowser += "Correct (spike time 2 < spike time 3), difference >= 1 ms \n\n";
        }
        else if(count2+1 < count && count2 < count3)
        {
            textToTextBrowser += "Correct (spike time 2 < spike time 1), difference >= 1 ms \n";
            textToTextBrowser += "Correct (spike time 2 < spike time 3), but difference < 1 ms \n";
            textToTextBrowser += "result += 1 \n\n";
        }
        else if(count2 < count && count2+1 < count3)
        {
            textToTextBrowser += "Correct (spike time 2 < spike time 1), but difference < 1 ms \n";
            textToTextBrowser += "result += 1 \n";
            textToTextBrowser += "Correct (spike time 2 < spike time 3), difference >= 1 ms \n\n";
        }
        else if(count2 < count && count2 < count3)
        {
            textToTextBrowser += "Correct (spike time 2 < spike time 1), but difference < 1 ms \n";
            textToTextBrowser += "result += 1 \n";
            textToTextBrowser += "Correct (spike time 2 < spike time 3), but difference < 1 ms \n";
            textToTextBrowser += "result += 1 \n";
        }
        else if(count2 == count && count2+1 < count3)
        {
            textToTextBrowser += "Incorrect (spike time 2 == spike time 1), difference = 0 ms \n";
            textToTextBrowser += "result += 2 \n";
            textToTextBrowser += "Correct (spike time 2 < spike time 3), difference >= 1 ms \n";
        }
        else if(count2+1 < count && count2 == count3)
        {
            textToTextBrowser += "Correct (spike time 2 < spike time 1), difference >= 1 ms \n";
            textToTextBrowser += "Incorrect (spike time 2 == spike time 3), difference = 0 ms \n";
            textToTextBrowser += "result += 2 \n";
        }
        else if(count2 < count && count2 == count3)
        {
            textToTextBrowser += "Correct (spike time 2 < spike time 1), but difference < 1 ms \n";
            textToTextBrowser += "result += 1 \n";
            textToTextBrowser += "Incorrect (spike time 2 == spike time 3), difference = 0 ms \n";
            textToTextBrowser += "result += 2 \n";
        }
        else if(count2 == count && count2 < count3)
        {
            textToTextBrowser += "Incorrect (spike time 2 < spike time 1), difference = 0 ms \n";
            textToTextBrowser += "result += 2 \n";
            textToTextBrowser += "Correct (spike time 2 == spike time 3), but difference < 1 ms \n";
            textToTextBrowser += "result += 1 \n";
        }
        else if(count2+1 < count && count2 > count3)
        {
            textToTextBrowser += "Correct (spike time 2 < spike time 1), difference >= 1 ms \n";
            textToTextBrowser += "Incorrect (spike time 2 > spike time 3)\n";
            textToTextBrowser += "result += 3 \n";
        }
        else if(count2 > count && count2+1 < count3)
        {
            textToTextBrowser += "Incorrect (spike time 2 > spike time 1)\n";
            textToTextBrowser += "result += 3 \n";
            textToTextBrowser += "Correct (spike time 2 < spike time 3), difference >= 1 ms \n";
        }
        else if(count2 == count && count2 == count3)
        {
            textToTextBrowser += "Incorrect (spike time 2 < spike time 1), difference = 0 ms \n";
            textToTextBrowser += "result += 2 \n";
            textToTextBrowser += "Incorrect (spike time 2 < spike time 3), difference = 0 ms \n";
            textToTextBrowser += "result += 2 \n";
        }
        else if(count2 < count && count2 > count3)
        {
            textToTextBrowser += "Correct (spike time 2 < spike time 1), but difference < 1 ms \n";
            textToTextBrowser += "result += 1 \n";
            textToTextBrowser += "Incorrect (spike time 2 > spike time 3)\n";
            textToTextBrowser += "result += 3 \n";
        }
        else if(count2 > count && count2 < count3)
        {
            textToTextBrowser += "Incorrect (spike time 2 > spike time 1)\n";
            textToTextBrowser += "result += 3 \n";
            textToTextBrowser += "Correct (spike time 2 == spike time 3), but difference < 1 ms \n";
            textToTextBrowser += "result += 1 \n";
        }
        else if(count2 > count && count2 == count3)
        {
            textToTextBrowser += "Incorrect (spike time 2 > spike time 1)\n";
            textToTextBrowser += "result += 3 \n";
            textToTextBrowser += "Incorrect (spike time 2 == spike time 3), difference = 0 ms \n";
            textToTextBrowser += "result += 2 \n";
        }
        else if(count2 == count && count2 > count3)
        {
            textToTextBrowser += "Incorrect (spike time 2 == spike time 1), difference = 0 ms \n";
            textToTextBrowser += "result += 2 \n";
            textToTextBrowser += "Incorrect (spike time 2 > spike time 3)\n";
            textToTextBrowser += "result += 3 \n";
        }
        else if(count2 > count && count2 > count3)
        {
            textToTextBrowser += "Incorrect (spike time 2 > spike time 1)\n";
            textToTextBrowser += "result += 3 \n";
            textToTextBrowser += "Incorrect (spike time 2 > spike time 3)\n";
            textToTextBrowser += "result += 3 \n";
        }

        textToTextBrowser += "\n";
        if(count4+1 < count3 && count4+1 < count5)
        {
            textToTextBrowser += "Correct (spike time 4 < spike time 3), difference >= 1 ms \n";
            textToTextBrowser += "Correct (spike time 4 < spike time 5), difference >= 1 ms \n\n";
        }
        else if(count4+1 < count3 && count4 < count5)
        {
            textToTextBrowser += "Correct (spike time 4 < spike time 3), difference >= 1 ms \n";
            textToTextBrowser += "Correct (spike time 4 < spike time 5), but difference < 1 ms \n";
            textToTextBrowser += "result += 1 \n\n";
        }
        else if(count4 < count3 && count4+1 < count5)
        {
            textToTextBrowser += "Correct (spike time 4 < spike time 3), but difference < 1 ms \n";
            textToTextBrowser += "result += 1 \n";
            textToTextBrowser += "Correct (spike time 4 < spike time 5), difference >= 1 ms \n\n";
        }
        else if(count4 < count3 && count4 < count5)
        {
            textToTextBrowser += "Correct (spike time 4 < spike time 3), but difference < 1 ms \n";
            textToTextBrowser += "result += 1 \n";
            textToTextBrowser += "Correct (spike time 4 < spike time 5), but difference < 1 ms \n";
            textToTextBrowser += "result += 1 \n";
        }
        else if(count4 == count3 && count4+1 < count5)
        {
            textToTextBrowser += "Incorrect (spike time 4 == spike time 3), difference = 0 ms \n";
            textToTextBrowser += "result += 2 \n";
            textToTextBrowser += "Correct (spike time 4 < spike time 5), difference >= 1 ms \n";
        }
        else if(count4+1 < count3 && count4 == count5)
        {
            textToTextBrowser += "Correct (spike time 4 < spike time 3), difference >= 1 ms \n";
            textToTextBrowser += "Incorrect (spike time 4 == spike time 5), difference = 0 ms \n";
            textToTextBrowser += "result += 2 \n";
        }
        else if(count4 < count3 && count4 == count5)
        {
            textToTextBrowser += "Correct (spike time 4 < spike time 3), but difference < 1 ms \n";
            textToTextBrowser += "result += 1 \n";
            textToTextBrowser += "Incorrect (spike time 4 == spike time 5), difference = 0 ms \n";
            textToTextBrowser += "result += 2 \n";
        }
        else if(count4 == count3 && count4 < count5)
        {
            textToTextBrowser += "Incorrect (spike time 4 < spike time 5), difference = 0 ms \n";
            textToTextBrowser += "result += 2 \n";
            textToTextBrowser += "Correct (spike time 4 == spike time 3), but difference < 1 ms \n";
            textToTextBrowser += "result += 1 \n";
        }
        else if(count4+1 < count3 && count4 > count5)
        {
            textToTextBrowser += "Correct (spike time 4 < spike time 3), difference >= 1 ms \n";
            textToTextBrowser += "Incorrect (spike time 4 > spike time 5)\n";
            textToTextBrowser += "result += 3 \n";
        }
        else if(count4 > count3 && count4+1 < count5)
        {
            textToTextBrowser += "Incorrect (spike time 4 > spike time 3)\n";
            textToTextBrowser += "result += 3 \n";
            textToTextBrowser += "Correct (spike time 4 < spike time 5), difference >= 1 ms \n";
        }
        else if(count4 == count3 && count4 == count5)
        {
            textToTextBrowser += "Incorrect (spike time 4 < spike time 3), difference = 0 ms \n";
            textToTextBrowser += "result += 2 \n";
            textToTextBrowser += "Incorrect (spike time 4 < spike time 5), difference = 0 ms \n";
            textToTextBrowser += "result += 2 \n";
        }
        else if(count4 < count3 && count4 > count5)
        {
            textToTextBrowser += "Correct (spike time 4 < spike time 3), but difference < 1 ms \n";
            textToTextBrowser += "result += 1 \n";
            textToTextBrowser += "Incorrect (spike time 4 > spike time 5)\n";
            textToTextBrowser += "result += 3 \n";
        }
        else if(count4 > count3 && count4 < count5)
        {
            textToTextBrowser += "Incorrect (spike time 4 > spike time 3)\n";
            textToTextBrowser += "result += 3 \n";
            textToTextBrowser += "Correct (spike time 4 == spike time 5), but difference < 1 ms \n";
            textToTextBrowser += "result += 1 \n";
        }
        else if(count4 > count3 && count4 == count5)
        {
            textToTextBrowser += "Incorrect (spike time 4 > spike time 3)\n";
            textToTextBrowser += "result += 3 \n";
            textToTextBrowser += "Incorrect (spike time 4 == spike time 5), difference = 0 ms \n";
            textToTextBrowser += "result += 2 \n";
        }
        else if(count4 == count3 && count4 > count5)
        {
            textToTextBrowser += "Incorrect (spike time 4 == spike time 3), difference = 0 ms \n";
            textToTextBrowser += "result += 2 \n";
            textToTextBrowser += "Incorrect (spike time 4 > spike time 5)\n";
            textToTextBrowser += "result += 3 \n";
        }
        else if(count4 > count3 && count4 > count5)
        {
            textToTextBrowser += "Incorrect (spike time 4 > spike time 3)\n";
            textToTextBrowser += "result += 3 \n";
            textToTextBrowser += "Incorrect (spike time 4 > spike time 5)\n";
            textToTextBrowser += "result += 3 \n";
        }

        textToTextBrowser += "\n";
        if(count6+1 < count5)
            textToTextBrowser += "Correct (spike time 6 < spike time 5), difference >= 1 ms \n";
        else if(count6 < count5)
        {
            textToTextBrowser += "Correct (spike time 6 < spike time 5), but difference < 1 ms \n";
            textToTextBrowser += "result += 1 \n\n";
        }
        else if(count6 == count5)
        {
            textToTextBrowser += "Incorrect (spike time 6 == spike time 5), difference = 0 ms \n";
            textToTextBrowser += "result += 2 \n";
        }
        else if(count6 > count5)
        {
            textToTextBrowser += "Incorrect (spike time 6 > spike time 5)\n";
            textToTextBrowser += "result += 3 \n";
        }
        textToTextBrowser += "\n\n";
    }


    int treshold = minOdd;
    bool tabResult[6];
    //macierz kofunzji
    double TP = 0.0;
    double TN = 0.0;
    double FP = 0.0;
    double FN = 0.0;
    if(count >= treshold)
    {
        tabResult[0] = true;
        TN += 1.0;
    }
    else
    {
        tabResult[0] = false;
        FP += 1.0;
    }
    if(count2 + 1 < treshold)
    {
        tabResult[1] = true;
        TP += 1.0;
    }
    else
    {
        tabResult[1] = false;
        FN += 1.0;
    }
    if(count3 >= treshold)
    {
        tabResult[2] = true;
        TN += 1.0;
    }
    else
    {
        tabResult[2] = false;
        FP += 1.0;
    }
    if(count4 + 1 < treshold)
    {
        tabResult[3] = true;
        TP += 1.0;
    }
    else
    {
        tabResult[3] = false;
        FN += 1.0;
    }
    if(count5 >= treshold)
    {
        tabResult[4] = true;
        TN += 1.0;
    }
    else
    {
        tabResult[4] = false;
        FP += 1.0;
    }
    if(count6 + 1 < treshold)
    {
        tabResult[5] = true;
        TP += 1.0;
    }
    else
    {
        tabResult[5] = false;
        FN += 1.0;
    }
    int numberOK = 0;
    for(int i = 0; i<6; i++)
        if(tabResult[i])
            numberOK++;
    double accuracy = numberOK/6.0;
    if(show)
    {
        cout<<"Accuracy: "<<accuracy<<endl;
        textToTextBrowser += "\nAccuracy: " + QString::number(accuracy) + "\n";
    }
    //result += 100-(accuracy * 100);

    if(show)
    {
        //macierz konfuzji
        double P = 0.0;
        double N = 0.0;
        P = TP + FN;
        N = TN + FP;
        double ACC = (TP+TN)/(P+N);
        double ERR = (FP+FN)/(P+N);
        cout<<"Quality of the classification: "<<ACC<<endl;
        cout<<"Error level: "<<ERR<<endl;
        double TPR = TP/(TP+FN);
        double TNR = TN/(TN+FP);
        double PPV = TP/(TP+FP);
        //int NPV = TN/(TN+FN);
        cout<<"Sensitiveness: "<<TPR<<endl;
        cout<<"Specificity: "<<TNR<<endl;
        cout<<"Precision: "<<PPV<<endl;
        textToTextBrowser += "Quality of the classification: : " + QString::number(ACC) + "\n";
        textToTextBrowser += "Error level: " + QString::number(ERR) + "\n";
        textToTextBrowser += "Sensitiveness: " + QString::number(TPR) + "\n";
        textToTextBrowser += "Specificity: " + QString::number(TNR) + "\n";
        textToTextBrowser += "Precision: " + QString::number(PPV) + "\n";
    }

//    delete currentFromImage1;
//    delete currentFromImage2;
//    delete currentFromImage3;
//    delete currentFromImage4;
//    delete currentFromImage5;
//    delete currentFromImage6;
cout<<"1538"<<endl;
    return result;
}
