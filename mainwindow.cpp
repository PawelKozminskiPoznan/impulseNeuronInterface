#include "Mainwindow.h"
#include "ui_Mainwindow.h"

#include <iostream>
#include <algorithm>
#include <vector>

#include <stdio.h>
#include <stdlib.h>

#include <sstream>
#include <iomanip>

#include <cstdlib>
#include <ctime>

#include "Network.h"
#include "genetic_agorithm.hpp"
#include "dna_tsp.hpp"

#include <memory>

#include <QtConcurrent/QtConcurrent>
#include <QThread>

#include <dirent.h>
#include <string>

//using std::unique_ptr;

#include <iomanip>
using std::left;
using std::setw;
using std::fixed;
using std::setprecision;

using namespace std;

#define GEN_NEXT  0 //ok, print and continue
#define GEN_TERM  1 //ok, terminate
#define GEN_EMPTY 2 //ok, print EMPTY SET and continue
#define GEN_ERROR 3 //an error occured, print an error message and terminate

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   // ui->plot->setMinimumSize(QSize(1250,750));
    //this->setMinimumSize(1310,800);
    //this->showFullScreen();

    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(start()));
    connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadButtonClicked()));

    ui->plot->xAxis->setLabel("Czas [ms]");
    ui->plot->yAxis->setLabel("Napięcie neuronu [mV] / Prąd neuronu [pA]");
    ui->plot->yAxis->setRange(-100, 100);
    ui->plot->xAxis->setRange(0, 6500);
    ui->plot->addGraph();
    ui->plot->graph(0)->setName(QString::fromStdString("Vy"));
    ui->plot->graph(0)->setPen(QPen(Qt::GlobalColor(7)));
    ui->plot->addGraph();
    ui->plot->graph(1)->setName(QString::fromStdString("Iy"));
    ui->plot->graph(1)->setPen(QPen(Qt::GlobalColor(8)));
    ui->plot->legend->setVisible(true);
    ui->plot_2->xAxis->setLabel("Czas [ms]");
    ui->plot_2->yAxis->setLabel("Napięcie neuronu [mV] / Prąd neuronu [pA]");
    ui->plot_2->yAxis->setRange(-100, 100);
    ui->plot_2->xAxis->setRange(0, 6500);
    ui->plot_2->addGraph();
    ui->plot_2->graph(0)->setName(QString::fromStdString("Vy"));
    ui->plot_2->graph(0)->setPen(QPen(Qt::GlobalColor(7)));
    ui->plot_2->addGraph();
    ui->plot_2->graph(1)->setName(QString::fromStdString("Iy"));
    ui->plot_2->graph(1)->setPen(QPen(Qt::GlobalColor(8)));
    ui->plot_2->legend->setVisible(true);
    ui->plot_3->xAxis->setLabel("Czas [ms]");
    ui->plot_3->yAxis->setLabel("Napięcie neuronu [mV] / Prąd neuronu [pA]");
    ui->plot_3->yAxis->setRange(-100, 100);
    ui->plot_3->xAxis->setRange(0, 6500);
    ui->plot_3->addGraph();
    ui->plot_3->graph(0)->setName(QString::fromStdString("Vy"));
    ui->plot_3->graph(0)->setPen(QPen(Qt::GlobalColor(7)));
    ui->plot_3->addGraph();
    ui->plot_3->graph(1)->setName(QString::fromStdString("Iy"));
    ui->plot_3->graph(1)->setPen(QPen(Qt::GlobalColor(8)));
    ui->plot_3->legend->setVisible(true);
    ui->plot_4->xAxis->setLabel("Czas [ms]");
    ui->plot_4->yAxis->setLabel("Napięcie neuronu [mV] / Prąd neuronu [pA]");
    ui->plot_4->yAxis->setRange(-100, 100);
    ui->plot_4->xAxis->setRange(0, 6500);
    ui->plot_4->addGraph();
    ui->plot_4->graph(0)->setName(QString::fromStdString("Vy"));
    ui->plot_4->graph(0)->setPen(QPen(Qt::GlobalColor(7)));
    ui->plot_4->addGraph();
    ui->plot_4->graph(1)->setName(QString::fromStdString("Iy"));
    ui->plot_4->graph(1)->setPen(QPen(Qt::GlobalColor(8)));
    ui->plot_4->legend->setVisible(true);
    ui->plot_5->xAxis->setLabel("Czas [ms]");
    ui->plot_5->yAxis->setLabel("Napięcie neuronu [mV] / Prąd neuronu [pA]");
    ui->plot_5->yAxis->setRange(-100, 100);
    ui->plot_5->xAxis->setRange(0, 6500);
    ui->plot_5->addGraph();
    ui->plot_5->graph(0)->setName(QString::fromStdString("Vy"));
    ui->plot_5->graph(0)->setPen(QPen(Qt::GlobalColor(7)));
    ui->plot_5->addGraph();
    ui->plot_5->graph(1)->setName(QString::fromStdString("Iy"));
    ui->plot_5->graph(1)->setPen(QPen(Qt::GlobalColor(8)));
    ui->plot_5->legend->setVisible(true);
    ui->plot_6->xAxis->setLabel("Czas [ms]");
    ui->plot_6->yAxis->setLabel("Napięcie neuronu [mV] / Prąd neuronu [pA]");
    ui->plot_6->yAxis->setRange(-100, 100);
    ui->plot_6->xAxis->setRange(0, 6500);
    ui->plot_6->addGraph();
    ui->plot_6->graph(0)->setName(QString::fromStdString("Vy"));
    ui->plot_6->graph(0)->setPen(QPen(Qt::GlobalColor(7)));
    ui->plot_6->addGraph();
    ui->plot_6->graph(1)->setName(QString::fromStdString("Iy"));
    ui->plot_6->graph(1)->setPen(QPen(Qt::GlobalColor(8)));
    ui->plot_6->legend->setVisible(true);
    ui->saveButton->setEnabled(false);
    //ui->inputNeuronNumber->setFocus();
    connect(ui->helpButton, SIGNAL(clicked()), this, SLOT(on_helpClick()));
    connect(ui->help2Button, SIGNAL(clicked()), this, SLOT(on_help2Click()));
    connect(ui->helpPlotButton, SIGNAL(clicked()), this, SLOT(on_plotHelpClick()));
    connect(ui->helpArchButton, SIGNAL(clicked()), this, SLOT(on_archHelpClick()));
    ui->help->setVisible(false);
    ui->help2->setVisible(false);
    ui->helpPlot->setVisible(false);
    ui->helpArch->setVisible(false);

    //QString fileName = QFileDialog::getOpenFileName(this,"Open Image File",QDir::currentPath());
    QImage image("C:/Users/pawelkoz/Desktop/sieci_impulsujace/2-4-1.png");

    QGraphicsScene* scene = new QGraphicsScene();
   // QGraphicsView* view = new QGraphicsView(scene);
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    scene->addItem(item);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    ui->graphicsView->setVisible(false);

    //input date check box
    connect(ui->checkBox, SIGNAL(clicked()), this, SLOT(on_smallImageClick()));
    connect(ui->checkBox_2, SIGNAL(clicked()), this, SLOT(on_smallImageClick()));
    connect(ui->checkBox_3, SIGNAL(clicked()), this, SLOT(on_smallImageClick()));
    connect(ui->checkBox_4, SIGNAL(clicked()), this, SLOT(on_smallImageClick()));
    connect(ui->checkBox_5, SIGNAL(clicked()), this, SLOT(on_smallImageClick()));

    connect(ui->checkBox_6, SIGNAL(clicked()), this, SLOT(on_MNISTImageClick()));
    connect(ui->checkBox_7, SIGNAL(clicked()), this, SLOT(on_MNISTImageClick()));
    connect(ui->checkBox_8, SIGNAL(clicked()), this, SLOT(on_MNISTImageClick()));
    connect(ui->checkBox_9, SIGNAL(clicked()), this, SLOT(on_MNISTImageClick()));

    //test date check box
    connect(ui->checkBox_19, SIGNAL(clicked()), this, SLOT(on_reverseCheck1Click()));
    connect(ui->checkBox_20, SIGNAL(clicked()), this, SLOT(on_reverseCheck2Click()));
    connect(ui->checkBox_21, SIGNAL(clicked()), this, SLOT(on_reverseCheck3Click()));
    connect(ui->checkBox_22, SIGNAL(clicked()), this, SLOT(on_reverseCheck4Click()));
    connect(ui->checkBox_23, SIGNAL(clicked()), this, SLOT(on_reverseCheck5Click()));

    connect(ui->checkBox_24, SIGNAL(clicked()), this, SLOT(on_reverseCheck6Click()));
    connect(ui->checkBox_25, SIGNAL(clicked()), this, SLOT(on_reverseCheck7Click()));
    connect(ui->checkBox_26, SIGNAL(clicked()), this, SLOT(on_reverseCheck8Click()));
    connect(ui->checkBox_27, SIGNAL(clicked()), this, SLOT(on_reverseCheck9Click()));

    connect(ui->searchButton, SIGNAL(released()), this, SLOT(browseButtonPress()));

    ui->startButton->setEnabled(false);
    ui->loadButton->setEnabled(false);

    ui->tabWidget->setTabEnabled(1,false);
    ui->tabWidget->setTabEnabled(2,false);
    ui->tabWidget->setTabEnabled(3,false);
    ui->tabWidget->setTabEnabled(4,false);
    ui->tabWidget->setTabEnabled(5,false);

    savePath = QDir::currentPath();
    ui->loadPath->setText(savePath);
    savePath += "/results";
    ui->savePath->setText(savePath);
    ui->savePath_2->setText(savePath);

    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(on_saveButtonClick()));

    load = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::exsistFolder(string path)
{
    DIR *dir;
    char* p= new char[path.size()+1];
    strcpy(p,path.c_str());
    if ((dir = opendir (p)) != nullptr)
        return true;
    else
        return false;
}


void MainWindow::plotNeuron()
{
    Neuron *neuron = new Neuron();

    //input vertical lines
    QCPItemLine *line = new QCPItemLine(ui->plot);
    line->start->setCoords(200, -300);
    line->end->setCoords(200, 100);
    QCPItemLine *line2 = new QCPItemLine(ui->plot);
    line2->start->setCoords(700, -300);
    line2->end->setCoords(700, 100);

    //output neuron
    int current = 290;
    for(int i = 0; i<1; ++i)
    {
        double *v = neuron->work(current);
        //double *v = neuron->getVoltage();
        int T = neuron->getTime();
        double dt = neuron->getDt();
        string currentText = "Iapp = "+ to_string(current);
        makePlot(v, T, dt, i, currentText, current);
        current -= 1;
    }
    ui->plot->legend->setVisible(true);
    ui->plot->replot();
}

void MainWindow::plot(double *d, double *i)//dla wykresu pradu i napiecia
{
    verticalLine(500,1000);
    verticalLine(1500,2000);
    verticalLine(2500,3000);
    verticalLine(3500,4000);
    verticalLine(4500,5000);
    verticalLine(5500,6000);

   // ui->plot->clearGraphs();

    int dt = 13000;

    QVector<double> x(dt), y(dt);
    double dx = 0;
    for (int i=0; i<dt; ++i)
    {
        y[i] = d[i];
        x[i] = dx;
        dx += 0.5;
    }
    ui->plot->graph(0)->setData(x, y);
    dx = 0;
    for (int j=0; j<dt; ++j)
    {
        y[j] = i[j];
        x[j] = dx;
        dx += 0.5;
    }
    ui->plot->graph(1)->setData(x, y);

    ui->plot->yAxis->setRange(-100, 100);
    ui->plot->xAxis->setRange(0, dt/2);
    ui->plot->replot();
}

void MainWindow::plot2(double *d, double *i)//dla wykresu pradu i napiecia
{
    verticalLine2(500,1000);
    verticalLine2(1500,2000);
    verticalLine2(2500,3000);
    verticalLine2(3500,4000);
    verticalLine2(4500,5000);
    verticalLine2(5500,6000);

   // ui->plot->clearGraphs();

    int dt = 13000;
    QVector<double> x(dt), y(dt);
    double dx = 0;
    for (int i=0; i<dt; ++i)
    {
        y[i] = d[i];
        x[i] = dx;
        dx += 0.5;
    }
    ui->plot_2->graph(0)->setData(x, y);
    dx = 0;
    for (int j=0; j<dt; ++j)
    {
        y[j] = i[j];
        x[j] = dx;
        dx += 0.5;
    }
    ui->plot_2->graph(1)->setData(x, y);

    ui->plot_2->yAxis->setRange(-100, 100);
    ui->plot_2->xAxis->setRange(0, dt/2);
    ui->plot_2->replot();
}

void MainWindow::plot3(double *d, double *i)//dla wykresu pradu i napiecia
{
    verticalLine3(500,1000);
    verticalLine3(1500,2000);
    verticalLine3(2500,3000);
    verticalLine3(3500,4000);
    verticalLine3(4500,5000);
    verticalLine3(5500,6000);

   // ui->plot->clearGraphs();

    int dt = 13000;
    QVector<double> x(dt), y(dt);
    double dx = 0;
    for (int i=0; i<dt; ++i)
    {
        y[i] = d[i];
        x[i] = dx;
        dx += 0.5;
    }
    ui->plot_3->graph(0)->setData(x, y);
    dx = 0;
    for (int j=0; j<dt; ++j)
    {
        y[j] = i[j];
        x[j] = dx;
        dx += 0.5;
    }
    ui->plot_3->graph(1)->setData(x, y);

    ui->plot_3->yAxis->setRange(-100, 100);
    ui->plot_3->xAxis->setRange(0, dt/2);
    ui->plot_3->replot();
}

void MainWindow::plot4(double *d, double *i)//dla wykresu pradu i napiecia
{
    verticalLine4(500,1000);
    verticalLine4(1500,2000);
    verticalLine4(2500,3000);
    verticalLine4(3500,4000);
    verticalLine4(4500,5000);
    verticalLine4(5500,6000);

   // ui->plot->clearGraphs();

    int dt = 13000;
    QVector<double> x(dt), y(dt);
    double dx = 0;
    for (int i=0; i<dt; ++i)
    {
        y[i] = d[i];
        x[i] = dx;
        dx += 0.5;
    }
    ui->plot_4->graph(0)->setData(x, y);
    dx = 0;
    for (int j=0; j<dt; ++j)
    {
        y[j] = i[j];
        x[j] = dx;
        dx += 0.5;
    }
    ui->plot_4->graph(1)->setData(x, y);

    ui->plot_4->yAxis->setRange(-100, 100);
    ui->plot_4->xAxis->setRange(0, dt/2);
    ui->plot_4->replot();
}

void MainWindow::plot5(double *d, double *i)//dla wykresu pradu i napiecia
{
    verticalLine5(500,1000);
    verticalLine5(1500,2000);
    verticalLine5(2500,3000);
    verticalLine5(3500,4000);
    verticalLine5(4500,5000);
    verticalLine5(5500,6000);

   // ui->plot->clearGraphs();

    int dt = 13000;
    QVector<double> x(dt), y(dt);
    double dx = 0;
    for (int i=0; i<dt; ++i)
    {
        y[i] = d[i];
        x[i] = dx;
        dx += 0.5;
    }
    ui->plot_5->graph(0)->setData(x, y);
    dx = 0;
    for (int j=0; j<dt; ++j)
    {
        y[j] = i[j];
        x[j] = dx;
        dx += 0.5;
    }
    ui->plot_5->graph(1)->setData(x, y);

    ui->plot_5->yAxis->setRange(-100, 100);
    ui->plot_5->xAxis->setRange(0, dt/2);
    ui->plot_5->replot();
}

void MainWindow::plot6(double *d, double *i)//dla wykresu pradu i napiecia
{
    verticalLine6(500,1000);
    verticalLine6(1500,2000);
    verticalLine6(2500,3000);
    verticalLine6(3500,4000);
    verticalLine6(4500,5000);
    verticalLine6(5500,6000);

   // ui->plot->clearGraphs();

    int dt = 13000;
    QVector<double> x(dt), y(dt);
    double dx = 0;
    for (int i=0; i<dt; ++i)
    {
        y[i] = d[i];
        x[i] = dx;
        dx += 0.5;
    }
    ui->plot_6->graph(0)->setData(x, y);
    dx = 0;
    for (int j=0; j<dt; ++j)
    {
        y[j] = i[j];
        x[j] = dx;
        dx += 0.5;
    }
    ui->plot_6->graph(1)->setData(x, y);

    ui->plot_6->yAxis->setRange(-100, 100);
    ui->plot_6->xAxis->setRange(0, dt/2);
    ui->plot_6->replot();
}

void MainWindow::plot(double *d)//dla wykresu rand()
{
    makePlot(d, 500, 1, 0, "Vy");
    ui->plot->xAxis->setLabel("Wylosowane liczby");//("Czas [ms]");
    ui->plot->yAxis->setLabel("Liczba wystąpień");//("Napięcie membrany [mV]");
    ui->plot->yAxis->setRange(120,280);
    ui->plot->xAxis->setRange(0, 500);
    ui->plot->replot();
}


void MainWindow::makePlot(const double* v, const int T, const double dt, int nrGraph, string text, int current)
{
    QVector<double> x(T), y(T);
    double dx = 0;
    for (int i=0; i<T; ++i)
    {
        y[i] = v[i];
        x[i] = dx;
        dx += dt;
    }

//    double meanHr = meanFreq(maxV, T, v, dt, nrGraph);
//    string meanHrString = to_string(meanHr);
//    if(meanHrString.size()>4)
//        meanHrString.erase(meanHrString.end()-4, meanHrString.end());

//    if(nrGraph == 0)
//    {
//        ui->label->setText("Iapp = "+QString::fromStdString(to_string(current)));
//        //ui->lineEdit->setText(QString::fromStdString(meanHrString));
//        ui->label_p1->setText("Iapp = "+QString::fromStdString(to_string(current)));
//    }
//    else if (nrGraph == 1)
//    {
//        ui->label_2->setText("Iapp = "+QString::fromStdString(to_string(current)));
//        //ui->lineEdit_2->setText(QString::fromStdString(meanHrString));
//        ui->label_p2->setText("Iapp = "+QString::fromStdString(to_string(current)));
//    }
//    else if (nrGraph == 2)
//    {
//        ui->label_3->setText("Iapp = "+QString::fromStdString(to_string(current)));
//        //ui->lineEdit_3->setText(QString::fromStdString(meanHrString));
//        ui->label_p3->setText("Iapp = "+QString::fromStdString(to_string(current)));
//    }

//    ui->plot->addGraph();
//    ui->plot->graph(nrGraph)->setName(QString::fromStdString(text));
//    ui->plot->graph(nrGraph)->setPen(QPen(Qt::GlobalColor(nrGraph+7)));

    ui->plot->graph(nrGraph)->setData(x, y);

    //ui->plot->yAxis->setRange(minV-abs(minV*0.1), maxV+abs(maxV*0.1));
    //ui->plot->yAxis->setRange(-100, 100);
}


double MainWindow::meanFreq(const int maxV, const int T, const double* v, const double dt, int nrGraph)
{
    int time = 0;
    vector<double> vecFreq;
    string periods= "     ";
    for (int i=0; i<T; ++i)
    {
        if(maxV == (int)v[i])
        {
            if(time == 0)
                time = i;
            else
            {
                int period = (int)((i - time) * dt);
                periods += to_string(period);
                periods += ", ";
                time = i;
                vecFreq.push_back(1000.0/period);
            }
        }
    }
    periods.erase(periods.end()-2,periods.end());
//    if(nrGraph == 0)
//    {
//        ui->periods_1->setText(QString::fromStdString(periods));
//    }
//    else if (nrGraph == 1)
//    {
//        ui->periods_2->setText(QString::fromStdString(periods));
//    }
//    else
//    {
//        ui->periods_3->setText(QString::fromStdString(periods));
//    }

    double sum = 0;
    int amountPeriod = (int)vecFreq.size();
    for(int i=0; i<(int)vecFreq.size(); ++i)
    {
        sum += vecFreq[i];
    }
    double meanFreq = sum/amountPeriod;
    stringstream tmp;
    tmp << setprecision(2) << fixed << meanFreq;
    meanFreq = stod(tmp.str());
    return meanFreq;
}

//int MainWindow::gen_vari_rep_lex_init(unsigned char *vector, const unsigned char m, const unsigned char n)
//{
//    int j; //index

//    //test for special cases
//    if(m == 0 || n == 0)
//     return(GEN_EMPTY);

//    //initialize: vector[0, ..., n - 1] are zero
//    for(j = 0; j < n; j++)
//     vector[j] = 0;

//    return(GEN_NEXT);
//}

//int MainWindow::gen_vari_rep_lex_next(unsigned char *vector, const unsigned char m, const unsigned char n)
//{
//    int j; //index

//    //easy case, increase rightmost element
//    if(vector[n - 1] < m - 1)
//     {
//     vector[n - 1]++;
//     return(GEN_NEXT);
//     }

//    //find rightmost element to increase and reset right-hand elements
//    for(j = n - 2; j >= 0; j--)
//     {
//     vector[j + 1] = 0;

//     if(vector[j] < m - 1)
//      break;
//     }

//    //terminate if all elements are m - 1
//    if(j < 0)
//     return(GEN_TERM);

//    //increase
//    vector[j]++;

//    return(GEN_NEXT);
//}

//vector<pair<int,vector<double>>> MainWindow::variances(int set, int subSet)
//{
//    unsigned char m           = set;    //length of alphabet
//    unsigned char n           = subSet;    //length of figures
//    unsigned char *vectorX     = NULL; //where the current figure is stored
//    int           gen_result;         //return value of generation functions
//    unsigned int  set_counter;        //counting generated sequences
//    int           x;                  //iterator

//    vector<pair<int,vector<double>>> result;

//    //alloc memory for vector
//    vectorX = (unsigned char *)malloc(sizeof(unsigned char) * n);
//    if(vectorX == NULL)
//     {
//     fprintf(stderr, "error: insufficient memory\n");
//     exit(EXIT_FAILURE);
//     }

//    set_counter = 0;
//    printf("vari_rep_lex(%u, %u)\n", m, n);

//    //initialize
//    gen_result = gen_vari_rep_lex_init(vectorX, m, n);

//    if(gen_result == GEN_EMPTY)
//     {
//     set_counter++;
//     //printf("{} (%u)\n", set_counter);
//     }

//    //generate all successors
//    while(gen_result == GEN_NEXT)
//     {
//     set_counter++;

//     vector<double> sekwencja;
//     for(x = 0; x < n; x++){
//      //printf("%u ", vectorX[x]);
//      double c;
//      if(vectorX[x]==0)
//          c = 0.7;
//      else if(vectorX[x]==3)
//          c = 1.5;
//      else
//          c = vectorX[x];
//      sekwencja.push_back(c);
//     }
//     pair<int,vector<double>> para;
//     para.first = set_counter;
//     para.second = sekwencja;
//     result.push_back(para);

//     //printf("\n", set_counter);

//     gen_result = gen_vari_rep_lex_next(vectorX, m, n);
//     }
//    return result;
//}

void MainWindow::verticalLine(int x1, int x2)
{
    QCPItemLine *line = new QCPItemLine(ui->plot);
    line->start->setCoords(x1, -500);
    line->end->setCoords(x1, 300);
    QCPItemLine *line2 = new QCPItemLine(ui->plot);
    line2->start->setCoords(x2, -500);
    line2->end->setCoords(x2, 300);
    line->setPen(QPen(Qt::blue, 0.5, Qt::DashLine));
    line2->setPen(QPen(Qt::darkBlue, 0.5, Qt::DashLine));
}

void MainWindow::verticalLine2(int x1, int x2)
{
    QCPItemLine *line = new QCPItemLine(ui->plot_2);
    line->start->setCoords(x1, -500);
    line->end->setCoords(x1, 300);
    QCPItemLine *line2 = new QCPItemLine(ui->plot_2);
    line2->start->setCoords(x2, -500);
    line2->end->setCoords(x2, 300);
    line->setPen(QPen(Qt::blue, 0.5, Qt::DashLine));
    line2->setPen(QPen(Qt::darkBlue, 0.5, Qt::DashLine));
}

void MainWindow::verticalLine3(int x1, int x2)
{
    QCPItemLine *line = new QCPItemLine(ui->plot_3);
    line->start->setCoords(x1, -500);
    line->end->setCoords(x1, 300);
    QCPItemLine *line2 = new QCPItemLine(ui->plot_3);
    line2->start->setCoords(x2, -500);
    line2->end->setCoords(x2, 300);
    line->setPen(QPen(Qt::blue, 0.5, Qt::DashLine));
    line2->setPen(QPen(Qt::darkBlue, 0.5, Qt::DashLine));
}

void MainWindow::verticalLine4(int x1, int x2)
{
    QCPItemLine *line = new QCPItemLine(ui->plot_4);
    line->start->setCoords(x1, -500);
    line->end->setCoords(x1, 300);
    QCPItemLine *line2 = new QCPItemLine(ui->plot_4);
    line2->start->setCoords(x2, -500);
    line2->end->setCoords(x2, 300);
    line->setPen(QPen(Qt::blue, 0.5, Qt::DashLine));
    line2->setPen(QPen(Qt::darkBlue, 0.5, Qt::DashLine));
}

void MainWindow::verticalLine5(int x1, int x2)
{
    QCPItemLine *line = new QCPItemLine(ui->plot_5);
    line->start->setCoords(x1, -500);
    line->end->setCoords(x1, 300);
    QCPItemLine *line2 = new QCPItemLine(ui->plot_5);
    line2->start->setCoords(x2, -500);
    line2->end->setCoords(x2, 300);
    line->setPen(QPen(Qt::blue, 0.5, Qt::DashLine));
    line2->setPen(QPen(Qt::darkBlue, 0.5, Qt::DashLine));
}

void MainWindow::verticalLine6(int x1, int x2)
{
    QCPItemLine *line = new QCPItemLine(ui->plot_6);
    line->start->setCoords(x1, -500);
    line->end->setCoords(x1, 300);
    QCPItemLine *line2 = new QCPItemLine(ui->plot_6);
    line2->start->setCoords(x2, -500);
    line2->end->setCoords(x2, 300);
    line->setPen(QPen(Qt::blue, 0.5, Qt::DashLine));
    line2->setPen(QPen(Qt::darkBlue, 0.5, Qt::DashLine));
}

void MainWindow::mainFunction()
{
    //qDebug() << "Function2: " << QThread::currentThread()<<QThread::currentThread()->objectName();
    srand( time(nullptr) );
//    double* z = net.simulatedAnnealingXOR(numbersOfResistors);
//    for(int i =0; i<numbersOfResistors; i++)
//        cout<<z[i]<<endl;
//    //w.plot(net.getVoltagesOutput());neuronY
//    w.plot(net.neuronY, net.iY);
    //rozkład funkcji rand()
//    net.randGenerator();
//    w.plot(net.neuronY);
    directorySave.clear();

    int numberInputNeurons = ui->inputNeuronNumber->value();
    int hiddenLayerNeurons = ui->spinBox_2->value();//6;
    int inhibatoryNeuron = ui->spinBox_3->value();
    int maxResistans = ui->spinBox_4->value();//10000;
    int maxGeneration = ui->spinBox_5->value();//10;
    int numbersOfResistors = (hiddenLayerNeurons*numberInputNeurons) + hiddenLayerNeurons;
    int coding;
    //Metoda kodowanie - wybór
    if(ui->radioButton_3->isChecked())
        coding = 3;
    else if(ui->radioButton_4->isChecked())
        coding = 4;
    cout<<"Coding = "<<coding<<endl;

    //Dane wejściowe - wybór
    int input_date = 0;
    if(ui->checkBox->isChecked())
        input_date += 1;
    if(ui->checkBox_2->isChecked())
        input_date += 2;
    if(ui->checkBox_3->isChecked())
        input_date += 4;
    if(ui->checkBox_4->isChecked())
        input_date += 8;
    if(ui->checkBox_5->isChecked())
        input_date += 16;

    if(ui->checkBox_6->isChecked())
        input_date += 32;
    if(ui->checkBox_7->isChecked())
        input_date += 64;
    if(ui->checkBox_8->isChecked())
        input_date += 128;
    if(ui->checkBox_9->isChecked())
        input_date += 256;

    cout<<"Input date = "<<input_date<<endl;

    Network net(numbersOfResistors,inhibatoryNeuron,numberInputNeurons);
    auto initialDNA = DNA_TSP(numbersOfResistors, maxResistans, &net, hiddenLayerNeurons,numberInputNeurons,coding,input_date);
    if(!load)
        initialDNA.initGenesWithRandomValues();
    else
        //initialDNA.initGenesFromFile(_genes);

    textToTextBrowser.clear();
    double* R_input[hiddenLayerNeurons];
    double* r_out = new double[hiddenLayerNeurons];
    if(!load)
    {
        const size_t populationSize = ui->spinBox_6->value();//60;
        const double percentOfBestCanReproduce = ui->spinBox_7->value();//50.0; //50.0;
        const double recombinationProbability = ui->spinBox_8->value()/100.0;//0.9;   // 90%
        const double mutationProbability = ui->spinBox_9->value()/100.0;//0.02;       //  2%

        auto ga = unique_ptr< GeneticAlgorithm<DNA_TSP> >(
            new GeneticAlgorithm<DNA_TSP> (
                &initialDNA,
                GeneticAlgorithmObjective::Minimization,
                populationSize,
                percentOfBestCanReproduce,
                recombinationProbability,
                mutationProbability) );

        cout << "\nOPTIMIZATION STARTED ...\n\n";
        textToTextBrowser += "\nOPTIMIZATION STARTED ...\n\n";

        cout << "Population size: " << ga->getPopulationSize() << "\n";
        textToTextBrowser  += "Population size: "+  QString::number(ga->getPopulationSize()) + "\n";
        cout << "Percent Of best DNA can reproduce: " << percentOfBestCanReproduce << "%\n";
        textToTextBrowser  += "Percent Of best DNA can reproduce: " + QString::number(percentOfBestCanReproduce) + "%\n";
        cout << "Recombination probability: " << recombinationProbability * 100.0 << "%\n";
        textToTextBrowser  += "Recombination probability: " + QString::number(recombinationProbability * 100.0) + "%\n";
        cout << "Mutation probability: " << mutationProbability * 100.0 << "%\n\n";
        textToTextBrowser  += "Mutation probability: " + QString::number(mutationProbability * 100.0) + "%\n";
        cout<<endl<<"hiddenLayerNeurons = "<<hiddenLayerNeurons<<endl;
        textToTextBrowser  += "hiddenLayerNeurons = " +  QString::number(hiddenLayerNeurons) + "\n\n\n";

        auto printGeneration = [&]()
        {
            cout << "Generation: "
                 << left << setw(5) << ga->getNumEvolvedGenerations()
                 << "   Best Fitness: "
                 << left << setw(10) << fixed
                 << setprecision(4)  << ga->getBestDNAfitness() << "\n";
            textToTextBrowser += "Generation:  "
                    + QString::number(ga->getNumEvolvedGenerations())
                    + "         Best Fitness: "
                    + QString::number(ga->getBestDNAfitness()) + "\n";
            ui->textBrowser->setText(textToTextBrowser);
        };

        printGeneration();

        int numberGeneration = 0;

        while (!ga->isProblemSolved() && numberGeneration < maxGeneration)
        {
            ga->evolveNextGeneration();
            numberGeneration++;
            printGeneration();
        }

        if (ga->isProblemSolved() || numberGeneration == maxGeneration)
        {
            cout << "\n\nSOLVED!\n\n";
            cout << "Number of evolved generations: "  << ga->getNumEvolvedGenerations() << "\n";
            textToTextBrowser  += "\n\n\nNumber of evolved generations: "  + QString::number(ga->getNumEvolvedGenerations()) + "\n";
            cout << "Number of improved generations: " << ga->getNumGenerationImprovements() << "\n";
            textToTextBrowser  +=  "Number of improved generations: " + QString::number(ga->getNumGenerationImprovements()) + "\n";
            cout << "Number of fitness evaluations: "  << ga->getNumFitnessEvaluations() << "\n";
            textToTextBrowser  += "Number of fitness evaluations: "  + QString::number(ga->getNumFitnessEvaluations()) + "\n";
            cout << "Number of fitness improvements: " << ga->getNumFitnessImprovements() << "\n";
            textToTextBrowser += "Number of fitness improvements: " + QString::number(ga->getNumFitnessImprovements()) + "\n";

            if (ga->getNumEvolvedGenerations())
            {
                const auto fitnessImprovementsPerGeneration =
                        static_cast<double>(ga->getNumFitnessImprovements()) /
                        static_cast<double>(ga->getNumEvolvedGenerations());

                cout << "Number of fitness improvements per generation: "
                     << fitnessImprovementsPerGeneration << "\n\n\n";
                textToTextBrowser += "Number of fitness improvements per generation: "
                        + QString::number(fitnessImprovementsPerGeneration) + "\n\n\n";
            }
        }

        resistors = "";
        for(int i =0; i<numbersOfResistors; i++)
        {
            resistors += to_string(ga->_bestDNA->_genes[i]);
            if(i+1<numbersOfResistors)
                resistors += "\n";
        }
        for(int i = 0; i < hiddenLayerNeurons; i++)
        {
            double* r_in = new double[numberInputNeurons];
            for(int j = 0; j < numberInputNeurons; j++)
                r_in[j] = ga->_bestDNA->_genes[j+i*numberInputNeurons];
            R_input[i] = r_in;
        }
        for(int i = 0; i < hiddenLayerNeurons; i++)
            r_out[i] = ga->_bestDNA->_genes[i+hiddenLayerNeurons*numberInputNeurons];
    }
    else
    {
        resistors = "";
        for(int i =0; i<numbersOfResistors; i++)
        {
            resistors += to_string(_genes[i]);
            if(i+1<numbersOfResistors)
                resistors += "\n";
        }
        for(int i = 0; i < hiddenLayerNeurons; i++)
        {
            double* r_in = new double[numberInputNeurons];
            for(int j = 0; j < numberInputNeurons; j++)
                r_in[j] = _genes[j+i*numberInputNeurons];
            R_input[i] = r_in;
        }
        for(int i = 0; i < hiddenLayerNeurons; i++)
            r_out[i] = _genes[i+hiddenLayerNeurons*numberInputNeurons];
    }


    ui->tabWidget->setTabEnabled(1,false);
    ui->tabWidget->setTabEnabled(2,false);
    ui->tabWidget->setTabEnabled(3,false);
    ui->tabWidget->setTabEnabled(4,false);
    ui->tabWidget->setTabEnabled(5,false);
    //directorySave = "/";
    switch( input_date )
    {
    case 1:
        directorySave += "3na5_czarno_biale";
        break;
    case 2:
        directorySave += "3na5_zestaw_1";
        break;
    case 4:
        directorySave += "3na5_zestaw_2";
        break;
    case 8:
        directorySave += "3na5_zestaw_3";
        break;
    case 16:
        directorySave += "3na5_zestaw_4";
        break;
    case 32:
        directorySave += "MNIST_zestaw_1";
        break;
    case 64:
        directorySave += "MNIST_zestaw_2";
        break;
    case 128:
        directorySave += "MNIST_zestaw_3";
        break;
    case 256:
        directorySave += "MNIST_zestaw_4";
        break;
    }
    switch( input_date )
    {
    case 1: case 2: case 4: case 8: case 16: case 32: case 64: case 128: case 256:
        cout<<"lala"<<endl;
        //cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,input_date,numberInputNeurons,true,coding)<<endl<<endl;
        //cout<<"baba"<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,input_date,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        //cout<<"dada"<<endl;
        plot(net.neuronOut, net.iY);
        break;
    case 3:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "3na5_czarno_biale";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_1";
        ui->tabWidget->setTabEnabled(1,true);
        break;
    case 5:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "3na5_czarno_biale";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_2";
        ui->tabWidget->setTabEnabled(1,true);
        break;
    case 6:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "3na5_zestaw_1";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_2";
        ui->tabWidget->setTabEnabled(1,true);
        break;
    case 7:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "3na5_czarno_biale";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_1";
        ui->tabWidget->setTabEnabled(1,true);
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot3(net.neuronOut, net.iY);
        directorySave += "_zestaw_2";
        ui->tabWidget->setTabEnabled(2,true);
        break;
    case 9:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "3na5_czarno_biale";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_3";
        ui->tabWidget->setTabEnabled(1,true);
        break;
    case 10:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "3na5_zestaw_1";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_3";
        ui->tabWidget->setTabEnabled(1,true);
        break;
    case 11:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "3na5_czarno_biale";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_1";
        ui->tabWidget->setTabEnabled(1,true);
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot3(net.neuronOut, net.iY);
        directorySave += "_zestaw_3";
        ui->tabWidget->setTabEnabled(2,true);
        break;
    case 12:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "3na5_zestaw_2";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_3";
        ui->tabWidget->setTabEnabled(1,true);
        break;
    case 13:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "3na5_czarno_biale";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_2";
        ui->tabWidget->setTabEnabled(1,true);
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot3(net.neuronOut, net.iY);
        directorySave += "_zestaw_3";
        ui->tabWidget->setTabEnabled(2,true);
        break;
    case 14:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "3na5_zestaw_1";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_2";
        ui->tabWidget->setTabEnabled(1,true);
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot3(net.neuronOut, net.iY);
        directorySave += "_zestaw_3";
        ui->tabWidget->setTabEnabled(2,true);
        break;
    case 15:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "3na5_czarno_biale";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_1";
        ui->tabWidget->setTabEnabled(1,true);
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot3(net.neuronOut, net.iY);
        directorySave += "_zestaw_2";
        ui->tabWidget->setTabEnabled(2,true);
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot4(net.neuronOut, net.iY);
        directorySave += "_zestaw_3";
        ui->tabWidget->setTabEnabled(3,true);
        break;
    case 17:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "3na5_czarno_biale";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_4";
        ui->tabWidget->setTabEnabled(1,true);
        break;
    case 18:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "3na5_zestaw_1";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_4";
        ui->tabWidget->setTabEnabled(1,true);
        break;
    case 19:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "3na5_czarno_biale";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_1";
        ui->tabWidget->setTabEnabled(1,true);
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot3(net.neuronOut, net.iY);
        directorySave += "_zestaw_4";
        ui->tabWidget->setTabEnabled(2,true);
        break;
    case 20:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "3na5_zestaw_2";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_4";
        ui->tabWidget->setTabEnabled(1,true);
        break;
    case 21:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "3na5_czarno_biale";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_2";
        ui->tabWidget->setTabEnabled(1,true);
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot3(net.neuronOut, net.iY);
        directorySave += "_zestaw_4";
        ui->tabWidget->setTabEnabled(2,true);
        break;
    case 22:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "3na5_zestaw_1";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_2";
        ui->tabWidget->setTabEnabled(1,true);
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot3(net.neuronOut, net.iY);
        directorySave += "_zestaw_4";
        ui->tabWidget->setTabEnabled(2,true);
        break;
    case 23:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "3na5_czarno_biale";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_1";
        ui->tabWidget->setTabEnabled(1,true);
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot3(net.neuronOut, net.iY);
        directorySave += "_zestaw_2";
        ui->tabWidget->setTabEnabled(2,true);
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot4(net.neuronOut, net.iY);
        directorySave += "_zestaw_4";
        ui->tabWidget->setTabEnabled(3,true);
        break;
    case 24:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "3na5_zestaw_3";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_4";
        ui->tabWidget->setTabEnabled(1,true);
        break;
    case 25:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "3na5_czarno_biale";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_3";
        ui->tabWidget->setTabEnabled(1,true);
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot3(net.neuronOut, net.iY);
        directorySave += "_zestaw_4";
        ui->tabWidget->setTabEnabled(2,true);
        break;
    case 26:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "3na5_zestaw_1";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_3";
        ui->tabWidget->setTabEnabled(1,true);
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot3(net.neuronOut, net.iY);
        directorySave += "_zestaw_4";
        ui->tabWidget->setTabEnabled(2,true);
        break;
    case 27:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "3na5_czarno_biale";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_1";
        ui->tabWidget->setTabEnabled(1,true);
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot3(net.neuronOut, net.iY);
        directorySave += "_zestaw_3";
        ui->tabWidget->setTabEnabled(2,true);
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot4(net.neuronOut, net.iY);
        directorySave += "_zestaw_4";
        ui->tabWidget->setTabEnabled(3,true);
        break;
    case 28:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "3na5_zestaw_2";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_3";
        ui->tabWidget->setTabEnabled(1,true);
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot3(net.neuronOut, net.iY);
        directorySave += "_zestaw_4";
        ui->tabWidget->setTabEnabled(2,true);
        break;
    case 29:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "3na5_czarno_biale";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_2";
        ui->tabWidget->setTabEnabled(1,true);
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot3(net.neuronOut, net.iY);
        directorySave += "_zestaw_3";
        ui->tabWidget->setTabEnabled(2,true);
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot4(net.neuronOut, net.iY);
        directorySave += "_zestaw_4";
        ui->tabWidget->setTabEnabled(3,true);
        break;
    case 30:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "3na5_zestaw_1";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_2";
        ui->tabWidget->setTabEnabled(1,true);
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot3(net.neuronOut, net.iY);
        directorySave += "_zestaw_3";
        ui->tabWidget->setTabEnabled(2,true);
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot4(net.neuronOut, net.iY);
        directorySave += "_zestaw_4";
        ui->tabWidget->setTabEnabled(3,true);
        break;
    case 31:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "3na5_czarno_biale";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_1";
        ui->tabWidget->setTabEnabled(1,true);
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot3(net.neuronOut, net.iY);
        directorySave += "_zestaw_2";
        ui->tabWidget->setTabEnabled(2,true);
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot4(net.neuronOut, net.iY);
        directorySave += "_zestaw_3";
        ui->tabWidget->setTabEnabled(3,true);
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot5(net.neuronOut, net.iY);
        directorySave += "_zestaw_4";
        ui->tabWidget->setTabEnabled(4,true);
        break;

    case 96:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,32,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,32,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "MNIST_zestaw_1";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,64,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,64,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_2";
        ui->tabWidget->setTabEnabled(1,true);
        break;
    case 160:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,32,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,32,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "MNIST_zestaw_1";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,128,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,128,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_3";
        ui->tabWidget->setTabEnabled(1,true);
        break;
    case 192:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,64,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,64,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "MNIST_zestaw_2";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,128,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,128,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_3";
        ui->tabWidget->setTabEnabled(1,true);
        break;
    case 288:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,32,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,32,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "MNIST_zestaw_1";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,256,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,256,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_4";
        ui->tabWidget->setTabEnabled(1,true);
        break;
    case 320:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,64,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,64,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "MNIST_zestaw_2";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,256,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,256,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_4";
        ui->tabWidget->setTabEnabled(1,true);
        break;
    case 352:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,128,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,128,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "MNIST_zestaw_3";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,256,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,256,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_4";
        ui->tabWidget->setTabEnabled(1,true);
        break;
    case 384:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,32,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,32,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "MNIST_zestaw_1";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,64,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,64,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_2";
        ui->tabWidget->setTabEnabled(1,true);
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,256,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,256,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot3(net.neuronOut, net.iY);
        directorySave += "_zestaw_4";
        ui->tabWidget->setTabEnabled(2,true);
        break;
    case 416:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,32,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,32,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "MNIST_zestaw_1";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,128,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,128,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_3";
        ui->tabWidget->setTabEnabled(1,true);
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,256,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,256,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot3(net.neuronOut, net.iY);
        directorySave += "_zestaw_4";
        ui->tabWidget->setTabEnabled(2,true);
        break;
    case 448:
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,64,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,64,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot(net.neuronOut, net.iY);
        directorySave += "MNIST_zestaw_2";
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,128,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,128,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot2(net.neuronOut, net.iY);
        directorySave += "_zestaw_3";
        ui->tabWidget->setTabEnabled(1,true);
        cout<<"wynik= "<<net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,256,numberInputNeurons,true,coding)<<endl<<endl;
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,256,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot3(net.neuronOut, net.iY);
        directorySave += "_zestaw_4";
        ui->tabWidget->setTabEnabled(2,true);
        break;
    }

    int testingDate = 0;
    if(ui->checkBox_19->isChecked())
    {
        testingDate += 1;
        directorySave += "_tested_czarno_biale";
    }
    if(ui->checkBox_20->isChecked())
    {
        testingDate += 2;
        directorySave += "_tested_zestaw_1";
    }
    if(ui->checkBox_21->isChecked())
    {
        testingDate += 4;
        directorySave += "_tested_zestaw_2";
    }
    if(ui->checkBox_22->isChecked())
    {
        testingDate += 8;
        directorySave += "_tested_zestaw_3";
    }
    if(ui->checkBox_23->isChecked())
    {
        testingDate += 16;
        directorySave += "_tested_zestaw_4";
    }

    if(ui->checkBox_24->isChecked())
    {
        testingDate += 32;
        directorySave += "_tested_zestaw_1";
    }
    if(ui->checkBox_25->isChecked())
    {
        testingDate += 64;
        directorySave += "_tested_zestaw_2";
    }
    if(ui->checkBox_26->isChecked())
    {
        testingDate += 128;
        directorySave += "_tested_zestaw_3";
    }
    if(ui->checkBox_27->isChecked())
    {
        testingDate += 256;
        directorySave += "_tested_zestaw_4";
    }
    if(testingDate != 0)
    {
        textToTextBrowser += "&&&&&&&&&&&&&&&&&&&& Testing &&&&&&&&&&&&&&&&&&&&\n";
        textToTextBrowser += "Result = " + QString::number(net.architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,testingDate,numberInputNeurons,true,coding,textToTextBrowser)) + "\n\n";
        plot6(net.neuronOut, net.iY);
        ui->tabWidget->setTabEnabled(5,true);
    }
    ui->textBrowser->setText(textToTextBrowser);
    enable_window();
    load = false;
}

void MainWindow::start()
{
    unenable_window();
    ui->textBrowser->clear();
//    qDebug() << "Function1: " << QThread::currentThread()<<QThread::currentThread()->objectName();
//    QFuture<void> future = QtConcurrent::run(this,&MainWindow::mainFunction);
    //QFuture<void> future = QtConcurrent::run(mainFunction);
//    future.waitForFinished();
    mainFunction();
    savePath.clear();
    savePath = QDir::currentPath();
    savePath += "/results";
    QString savePathTemp = savePath;
    savePathTemp += "/";
    savePathTemp += QString::fromStdString(directorySave) + "/" + QString::fromStdString(directorySave);
    QString savePathResistorsTemp = savePathTemp;
    savePathResistorsTemp = savePathTemp;
    savePathTemp += "_results.txt";
    savePathResistorsTemp += "_resistors.txt";
    ui->savePath->setText(savePathTemp);
    ui->savePath_2->setText(savePathResistorsTemp);
}

void MainWindow::unenable_window()
{
    //ui->centralWidget->setEnabled(false);
    ui->radioButton_3->setEnabled(false);
    ui->radioButton_4->setEnabled(false);
    ui->groupBox->setEnabled(false);
    ui->groupBox_2->setEnabled(false);
    ui->groupBox_3->setEnabled(false);
    ui->label_12->setEnabled(false);
    ui->label_13->setEnabled(false);
    ui->label_14->setEnabled(false);
    ui->label_15->setEnabled(false);
    ui->label_16->setEnabled(false);
    ui->label_17->setEnabled(false);
    ui->label_18->setEnabled(false);
    ui->label_19->setEnabled(false);
    ui->label_20->setEnabled(false);
    ui->label_21->setEnabled(false);
    ui->label_22->setEnabled(false);
    ui->label_23->setEnabled(false);
    ui->label_24->setEnabled(false);
    ui->label_25->setEnabled(false);
    ui->label_27->setEnabled(false);
    ui->startButton->setEnabled(false);
    ui->loadButton->setEnabled(false);
    //ui->inputNeuronNumber->setEnabled(false);
    ui->spinBox_2->setEnabled(false);
    ui->spinBox_3->setEnabled(false);
    ui->spinBox_4->setEnabled(false);
    ui->spinBox_5->setEnabled(false);
    ui->spinBox_6->setEnabled(false);
    ui->spinBox_7->setEnabled(false);
    ui->spinBox_8->setEnabled(false);
    ui->spinBox_9->setEnabled(false);
    ui->plot->setEnabled(false);
    ui->textBrowser->setEnabled(false);
    ui->groupBox_4->setEnabled(false);
    ui->groupBox_8->setEnabled(false);
    ui->groupBox_6->setEnabled(false);
    ui->helpPlotButton->setEnabled(false);
    ui->saveButton->setEnabled(false);
    ui->saveDesc->setEnabled(false);
    ui->saveLabel->setEnabled(false);
    ui->savePath->setEnabled(false);
    ui->savePath_2->setEnabled(false);
    ui->saveLabel_2->setEnabled(false);
    ui->groupBox_10->setEnabled(false);

    ui->plot->setBackground(QColor(230,230,230));

    QTime dieTime=QTime::currentTime().addSecs(1);

    while( QTime::currentTime() < dieTime )

    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
void MainWindow::enable_window()
{
    //ui->centralWidget->setEnabled(true);
    ui->plot->setBackground(Qt::white);
    ui->radioButton_3->setEnabled(true);
    ui->radioButton_4->setEnabled(true);
    ui->groupBox->setEnabled(true);
    ui->groupBox_2->setEnabled(true);
    ui->groupBox_3->setEnabled(true);
    ui->label_12->setEnabled(true);
    ui->label_13->setEnabled(true);
    ui->label_14->setEnabled(true);
    ui->label_15->setEnabled(true);
    ui->label_16->setEnabled(true);
    ui->label_17->setEnabled(true);
    ui->label_18->setEnabled(true);
    ui->label_19->setEnabled(true);
    ui->label_20->setEnabled(true);
    ui->label_21->setEnabled(true);
    ui->label_22->setEnabled(true);
    ui->label_23->setEnabled(true);
    ui->label_24->setEnabled(true);
    ui->label_25->setEnabled(true);
    ui->label_27->setEnabled(true);
    ui->startButton->setEnabled(true);
    ui->loadButton->setEnabled(true);
    //ui->inputNeuronNumber->setEnabled(true);
    ui->spinBox_2->setEnabled(true);
    ui->spinBox_3->setEnabled(true);
    ui->spinBox_4->setEnabled(true);
    ui->spinBox_5->setEnabled(true);
    ui->spinBox_6->setEnabled(true);
    ui->spinBox_7->setEnabled(true);
    ui->spinBox_8->setEnabled(true);
    ui->spinBox_9->setEnabled(true);
    ui->plot->setEnabled(true);
    ui->textBrowser->setEnabled(true);
    ui->groupBox_4->setEnabled(true);
    ui->groupBox_8->setEnabled(true);
    ui->groupBox_6->setEnabled(true);
    ui->helpPlotButton->setEnabled(true);
    ui->saveButton->setEnabled(true);
    ui->saveDesc->setEnabled(true);
    ui->saveLabel->setEnabled(true);
    ui->savePath->setEnabled(true);
    ui->savePath_2->setEnabled(true);
    ui->saveLabel_2->setEnabled(true);
    ui->groupBox_10->setEnabled(true);
}

void MainWindow::on_helpClick()
{
    bool visible = ui->help->isVisible();
    ui->help->setVisible(!visible);
}

void MainWindow::on_help2Click()
{
    bool visible = ui->help2->isVisible();
    ui->help2->setVisible(!visible);
}

void MainWindow::on_plotHelpClick()
{
    bool visible = ui->helpPlot->isVisible();
    ui->helpPlot->setVisible(!visible);
}

void MainWindow::on_archHelpClick()
{
    bool visible = ui->helpArch->isVisible();
    ui->helpArch->setVisible(!visible);
    ui->graphicsView->setVisible(!visible);
}

void MainWindow::on_smallImageClick()
{
    bool cliced = ui->checkBox->isChecked();
    cliced += ui->checkBox_2->isChecked();
    cliced += ui->checkBox_3->isChecked();
    cliced += ui->checkBox_4->isChecked();
    cliced += ui->checkBox_5->isChecked();
    if(cliced)
    {
        ui->groupBox_7->setEnabled(false);
        ui->groupBox_14->setEnabled(false);
        ui->inputNeuronNumber->setValue(15);
    }
    else
    {
        ui->groupBox_7->setEnabled(true);
        ui->groupBox_14->setEnabled(true);
    }
    possibleStart();
}

void MainWindow::on_MNISTImageClick()
{
    bool cliced = ui->checkBox_6->isChecked();
    cliced += ui->checkBox_7->isChecked();
    cliced += ui->checkBox_8->isChecked();
    cliced += ui->checkBox_9->isChecked();
    if(cliced)
    {
        ui->groupBox_5->setEnabled(false);
        ui->groupBox_12->setEnabled(false);
        ui->inputNeuronNumber->setValue(784);
    }
    else
    {
        ui->groupBox_5->setEnabled(true);
        ui->groupBox_12->setEnabled(true);
    }
    possibleStart();
}

void MainWindow::possibleStart()
{
    bool cliced = ui->checkBox->isChecked();
    cliced += ui->checkBox_2->isChecked();
    cliced += ui->checkBox_3->isChecked();
    cliced += ui->checkBox_4->isChecked();
    cliced += ui->checkBox_5->isChecked();

    cliced += ui->checkBox_6->isChecked();
    cliced += ui->checkBox_7->isChecked();
    cliced += ui->checkBox_8->isChecked();
    cliced += ui->checkBox_9->isChecked();

    ui->startButton->setEnabled(cliced);
    ui->loadButton->setEnabled(cliced);
}

void MainWindow::on_reverseCheck1Click()
{
    if(ui->checkBox_19->isChecked())
    {
        ui->checkBox_20->setChecked(false);
        ui->checkBox_21->setChecked(false);
        ui->checkBox_22->setChecked(false);
        ui->checkBox_23->setChecked(false);
    }
    fromFirstGroupCheckedOnly();
}

void MainWindow::on_reverseCheck2Click()
{
    if(ui->checkBox_20->isChecked())
    {
        ui->checkBox_19->setChecked(false);
        ui->checkBox_21->setChecked(false);
        ui->checkBox_22->setChecked(false);
        ui->checkBox_23->setChecked(false);
    }
    fromFirstGroupCheckedOnly();
}

void MainWindow::on_reverseCheck3Click()
{
    if(ui->checkBox_21->isChecked())
    {
        ui->checkBox_20->setChecked(false);
        ui->checkBox_19->setChecked(false);
        ui->checkBox_22->setChecked(false);
        ui->checkBox_23->setChecked(false);
    }
    fromFirstGroupCheckedOnly();
}

void MainWindow::on_reverseCheck4Click()
{
    if(ui->checkBox_22->isChecked())
    {
        ui->checkBox_20->setChecked(false);
        ui->checkBox_21->setChecked(false);
        ui->checkBox_19->setChecked(false);
        ui->checkBox_23->setChecked(false);
    }
    fromFirstGroupCheckedOnly();
}

void MainWindow::on_reverseCheck5Click()
{
    if(ui->checkBox_23->isChecked())
    {
        ui->checkBox_20->setChecked(false);
        ui->checkBox_21->setChecked(false);
        ui->checkBox_22->setChecked(false);
        ui->checkBox_19->setChecked(false);
    }
    fromFirstGroupCheckedOnly();
}

void MainWindow::on_reverseCheck6Click()
{
    if(ui->checkBox_24->isChecked())
    {
        ui->checkBox_25->setChecked(false);
        ui->checkBox_26->setChecked(false);
        ui->checkBox_27->setChecked(false);
    }
    fromSecondGroupCheckedOnly();
}

void MainWindow::on_reverseCheck7Click()
{
    if(ui->checkBox_25->isChecked())
    {
        ui->checkBox_24->setChecked(false);
        ui->checkBox_26->setChecked(false);
        ui->checkBox_27->setChecked(false);
    }
    fromSecondGroupCheckedOnly();
}

void MainWindow::on_reverseCheck8Click()
{
    if(ui->checkBox_26->isChecked())
    {
        ui->checkBox_25->setChecked(false);
        ui->checkBox_24->setChecked(false);
        ui->checkBox_27->setChecked(false);
    }
    fromSecondGroupCheckedOnly();
}

void MainWindow::on_reverseCheck9Click()
{
    if(ui->checkBox_27->isChecked())
    {
        ui->checkBox_25->setChecked(false);
        ui->checkBox_26->setChecked(false);
        ui->checkBox_24->setChecked(false);
    }
    fromSecondGroupCheckedOnly();
}

void MainWindow::fromFirstGroupCheckedOnly()
{
    bool cliced = ui->checkBox_19->isChecked();
    cliced += ui->checkBox_20->isChecked();
    cliced += ui->checkBox_21->isChecked();
    cliced += ui->checkBox_22->isChecked();
    cliced += ui->checkBox_23->isChecked();

    if(cliced)
    {
        ui->checkBox_24->setChecked(false);
        ui->checkBox_25->setChecked(false);
        ui->checkBox_26->setChecked(false);
        ui->checkBox_27->setChecked(false);
    }
}

void MainWindow::fromSecondGroupCheckedOnly()
{
    bool cliced = ui->checkBox_24->isChecked();
    cliced += ui->checkBox_25->isChecked();
    cliced += ui->checkBox_26->isChecked();
    cliced += ui->checkBox_27->isChecked();

    if(cliced)
    {
        ui->checkBox_19->setChecked(false);
        ui->checkBox_20->setChecked(false);
        ui->checkBox_21->setChecked(false);
        ui->checkBox_22->setChecked(false);
        ui->checkBox_23->setChecked(false);
    }
}

void MainWindow::on_saveButtonClick()
{
    //QString savePathSpecific = savePath + "/" + QString::fromStdString(directorySave);
    QString savePathSpecific = ui->savePath->text();
    string savePathSpecificString = savePathSpecific.toStdString();
    size_t lastSlash = savePathSpecificString.find_last_of("/");
    savePathSpecificString.erase(lastSlash,savePathSpecificString.size()-lastSlash);
    string directory;
    lastSlash = savePathSpecificString.find_last_of("/");
    directory.assign(savePathSpecificString,lastSlash+1,savePathSpecificString.size()-lastSlash);
    if(!exsistFolder(savePath.toStdString()))
    {
        string command = "results";
        command.insert(0, "mkdir ");
        command += " results\\" + directory;
        system(command.c_str());
    }
    else if(!exsistFolder(savePathSpecificString))
    {
        string command = "mkdir ";
        command += " results\\" + directory;
        system(command.c_str());
    }
    QString savePathTemp = ui->savePath->text();
    resultsFile.open(savePathTemp.toStdString());
    savePathTemp = ui->savePath_2->text();
    resistorsFile.open(savePathTemp.toStdString());
    directorySave.clear();

    resultsFile<<textToTextBrowser.toStdString();
    resistorsFile<<resistors;
    resultsFile.close();
    resistorsFile.close();
}

void MainWindow::browseButtonPress()
{
    string x;
    x = QDir::currentPath().toStdString();
    x += "/results/";
    if(exsistFolder(x))
        ui->loadPath->setText(QFileDialog::getOpenFileName(this, "Wybierz plik z wartościami rezystancji",QDir::currentPath()+"/results/"));
    else
        ui->loadPath->setText(QFileDialog::getOpenFileName(this, "Wybierz plik z wartościami rezystancji",QDir::currentPath()));
}

void MainWindow::loadButtonClicked()
{
    fstream resistorValues;
    string loadPath = ui->loadPath->text().toStdString();
    resistorValues.open (loadPath, ios::in);
    if(!resistorValues.is_open())
        errorCommunicate("Nie można otworzyć pliku!");
    else
    {
        int numberInputNeurons = ui->inputNeuronNumber->value();
        int hiddenLayerNeurons = ui->spinBox_2->value();
        int numbersOfResistors = (hiddenLayerNeurons*numberInputNeurons) + hiddenLayerNeurons;
        _genes.clear();
        string line;
        int row = 0;
        double iGene;
        while(getline(resistorValues, line))
        {
            iGene = stod(line);
            _genes.push_back(iGene);
            row++;
        }
        resistorValues.close();

        for (auto i: _genes)
            cout <<"vector: "<< i << endl;

        if(numbersOfResistors != row)
            errorCommunicate("Nie poprawna liczba wartości rezystancji!");
        else
        {
            load = true;
            start();
        }
    }
}

void MainWindow::errorCommunicate(string text)
{
    unenable_window();
    infoWindow = new QWidget;
    infoWindow->resize(240,200);

    QVBoxLayout* lDelete = new QVBoxLayout;
    QLabel* info = new QLabel();
    QLabel* info2 = new QLabel();
    QPushButton *ok = new QPushButton("Ok");
    QString t = QString::fromUtf8("Komunikat błedu ładowania pliku:");
    info->setText(t);
    const char * c = text.c_str();
    t = QString(QString::fromUtf8(c));
    connect(ok, SIGNAL(released()), this, SLOT(closeWindow()));
    infoWindow->setAttribute(Qt::WA_DeleteOnClose,true);
    connect(infoWindow , SIGNAL(destroyed()), this,SLOT(close()));
    info2->setText(t);
    lDelete->addWidget(info);
    lDelete->addWidget(info2);
    ok->setDefault(true);
    lDelete->addWidget(ok);
    infoWindow->setLayout(lDelete);
    infoWindow->show();
}

void MainWindow::closeWindow()
{
    enable_window();
    infoWindow->hide();
}
