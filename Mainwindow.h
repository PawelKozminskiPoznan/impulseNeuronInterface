#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Neuron.h"
#include <fstream>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void plotNeuron();
    void plot(double*,double*);
    void plot(double *d);
    void plot2(double*,double*);
    void plot3(double*,double*);
    void plot4(double*,double*);
    void plot5(double*,double*);
    void plot6(double*,double*);
private:
    vector<double> _genes;
    QWidget *infoWindow;
    bool load;
    QString textToTextBrowser;
    string resistors;
    ofstream resultsFile;
    ofstream resistorsFile;
    QString savePath;
    string directorySave;
    double *neuronY;
    Ui::MainWindow *ui;
    double meanFreq(const int maxV, const int T, const double *v, const double dt, int nrGraph);
    vector<pair<int,vector<double>>> variances(int set, int subSet);
    int gen_vari_rep_lex_next(unsigned char *vector, const unsigned char m, const unsigned char n);
    int gen_vari_rep_lex_init(unsigned char *vector, const unsigned char m, const unsigned char n);
    void verticalLine(int x1, int x2);
    void verticalLine2(int x1, int x2);
    void verticalLine3(int x1, int x2);
    void verticalLine4(int x1, int x2);
    void verticalLine5(int x1, int x2);
    void verticalLine6(int x1, int x2);
    void mainFunction();
    void possibleStart();
    void fromFirstGroupCheckedOnly();
    void fromSecondGroupCheckedOnly();
    bool exsistFolder(string path);
    void errorCommunicate(string);
    void unenable_window();
    void enable_window();
private slots:
    void makePlot(const double *v, const int T, const double dt, int nrGraph, std::string text = " ", int current = 7);
    void on_helpClick();
    void on_help2Click();
    void on_plotHelpClick();
    void on_archHelpClick();
    void on_smallImageClick();
    void on_MNISTImageClick();
    void on_reverseCheck1Click();
    void on_reverseCheck2Click();
    void on_reverseCheck3Click();
    void on_reverseCheck4Click();
    void on_reverseCheck5Click();
    void on_reverseCheck6Click();
    void on_reverseCheck7Click();
    void on_reverseCheck8Click();
    void on_reverseCheck9Click();
    void on_saveButtonClick();
    void browseButtonPress();
    void closeWindow();
public slots:
    void start();
    void loadButtonClicked();
};

#endif // MAINWINDOW_H
