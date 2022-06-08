
// Copyright (C) by Tim Völcker. All rights reserved.
// See the complete tutorial at www.timvoelcker.de/genetic_algorithm.html

// A DNA class implements a particular problem to be solved by a Genetic
// Algorithm. The class manages its own reproduction, mutation and fitness
// evaluation. There is no abstract base class for a DNA to inherit from.
// A user has to implement the class with its particular methods and inject
// it into a Genetic Algorithm by using templates. With this 'duck typing'
// approach there will be no performance overhead by runtime method binding
// (virtual functions). All types will be figured out at compile time.

// This DNA class implements a solution for a Travelling Salesman Problem.
// From the given route locations the shortest possible route should be found.
// The DNA represents a route. The genes of the DNA are the route locations.
// The fitness value of the DNA is defined by the total length of the route.
// In this specific case the objective is to minimize the fitness value.


#pragma once

#include <algorithm>
#include <numeric>

#include <array>
using std::array;

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <cmath>
using std::sqrt;
using std::pow;

//#include "randnumgen.hpp"
#include <iostream>

#include "Network.h"

class DNA_TSP
{
// Methods to be called by the GeneticAlgorithm class:
public:

    DNA_TSP(int amountOfResistors, int maxResistans, Network* net, int hiddenLayerNeurons, int numberInputNeurons, int coding, int input_date);

    DNA_TSP(const DNA_TSP& copyFrom);
    DNA_TSP& operator = (const DNA_TSP& copyFrom);
   ~DNA_TSP();

    void initGenesWithRandomValues();
    void initGenesFromFile(vector<double> genes);
    void copyGenes(const DNA_TSP& copyFrom);
    void recombineGenes(const DNA_TSP& parent1, const DNA_TSP& parent2);
    void mutateGenes(double probability);

    double calcFitness();
    double getFitness() const;

    string toString() const;

    bool isSolved() const;

    vector<double> _genes;

private:
    int input_date;
    int amountOfResistors;
    int maxResistans;

    Network* _net;
    double* resistors;
    int numberInputNeurons;
    int coding;
    int hiddenLayerNeurons;

    inline double calcRouteLength(const vector<double>& route);

    inline double euclidianDistance2D(
        double x1,
        double y1,
        double x2,
        double y2);

    inline void orderCrossover_OX(const DNA_TSP& dna1, const DNA_TSP& dna2);

    inline bool isGeneInSection(
        size_t gene,
        size_t iSectionStart,
        size_t iSectionEnd) const;

    inline void swapMutation();

    inline void twoOptLocalSearch();

    inline void twoOptSwap(
        const vector<double>& inGenes,
        vector<double>& outGenes,
        double iGene1,
        double iGene2);

private:
    const vector<double>* _locationsX;
    const vector<double>* _locationsY;
    double _routeLength;


    double _fitness;
};
