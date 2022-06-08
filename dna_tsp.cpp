
// Copyright (C) by Tim Völcker. All rights reserved.

#include "dna_tsp.hpp"


DNA_TSP::DNA_TSP(int amountOfResistors, int maxResistans, Network* net, int hiddenLayerNeurons, int numberInputNeurons, int coding, int input_date)
{
    this->input_date = input_date;
    this->numberInputNeurons = numberInputNeurons;
    this->coding = coding;
    this->hiddenLayerNeurons = hiddenLayerNeurons;
    _net = net;
    resistors = new double[amountOfResistors];
    // Fill the route with all possible locations. In this case the genes
    // are indices for the location coordinates.
    this->amountOfResistors = amountOfResistors;
    this->maxResistans = maxResistans;
    _genes.resize(amountOfResistors);
    std::iota(_genes.begin(), _genes.end(), 1);

    // For the Travelling Salesman Problem the fitness value of the DNA
    // is represented by the total length of the route, which should be
    // minimized. It will be initialized with the worst possible value.
    _fitness = std::numeric_limits<double>::max();
}


DNA_TSP::DNA_TSP(const DNA_TSP& copyFrom)
{
//    _locationsX = copyFrom._locationsX;
//    _locationsY = copyFrom._locationsY;
    this->input_date = copyFrom.input_date;
    this->numberInputNeurons = copyFrom.numberInputNeurons;
    this->coding = copyFrom.coding;
    this->amountOfResistors = copyFrom.amountOfResistors;
    this->maxResistans = copyFrom.maxResistans;
    this->_net = copyFrom._net;
    this->resistors = copyFrom.resistors;
    this->hiddenLayerNeurons = copyFrom.hiddenLayerNeurons;
    _fitness = copyFrom._fitness;
    copyGenes(copyFrom);
}


DNA_TSP& DNA_TSP::operator = (const DNA_TSP& copyFrom)
{
//    _locationsX = copyFrom._locationsX;
//    _locationsY = copyFrom._locationsY;
    amountOfResistors = copyFrom.amountOfResistors;
    _fitness = copyFrom._fitness;
    copyGenes(copyFrom);
}


DNA_TSP::~DNA_TSP()
{
}


void DNA_TSP::initGenesWithRandomValues()
{
    // Randomly shuffle the genes (route indices).

//    double iGeneSwap = 0;
//    for (size_t iGene = 0; iGene < _genes.size(); iGene++)
//    {
//        //iGeneSwap = getRandomRealInRange<double>(0.1, maxResistans);
//        iGeneSwap = (( rand() % (maxResistans*100) ) + 1)/100.0;

//        _genes[iGene] = iGeneSwap;
//    }

    double iGeneSwap = 0;
    for (size_t iGene = 0; iGene < _genes.size(); iGene++)
    {
        iGeneSwap = 0;
        //iGeneSwap = getRandomRealInRange<double>(0.1, maxResistans);
        int maxResistansTemp = maxResistans*100;
        if(maxResistansTemp > RAND_MAX)//32767
        {
            do
            {
                iGeneSwap = 0;
                int timesRand = maxResistansTemp/RAND_MAX;
                int times = rand()%(timesRand*2);
                for(int i = 0; i<times; i++)
                    iGeneSwap += rand();
                int rest = maxResistansTemp - RAND_MAX*times;
                iGeneSwap += (rand()%rest+1);
            }while(iGeneSwap > maxResistansTemp);
        }
        else
        {
            iGeneSwap = (( rand() % (maxResistansTemp) ) + 1);
        }
        _genes[iGene] = iGeneSwap/100.0;
    }

}

void DNA_TSP::initGenesFromFile(vector<double> genes)
{
    _genes = genes;
}


void DNA_TSP::copyGenes(const DNA_TSP& copyFrom)
{
    _genes.resize(copyFrom.amountOfResistors);//(_locationsX->size());

    for (size_t iGene = 0; iGene < _genes.size(); iGene++)
        _genes[iGene] = copyFrom._genes[iGene];
}


void DNA_TSP::recombineGenes(
    const DNA_TSP& parent1,
    const DNA_TSP& parent2)
{
    // This DNA will become a child of both parent DNAs by copying some genes
    // of parent1 and some genes of parent2. This recombination is also called
    // crossover. The following methods are typically used as a
    // crossover operator:
    //
    // - Every gene has a 50% chance to be copied from parent1 and a 50%
    //   chance to be copied from parent2.
    //
    // - A fixed or random crossover point (index) will be set.
    //   All genes before the index will be copied from parent1 and all genes
    //   after the the index will be copied from parent2. Alternative crossover
    //   methods may use multiple crossover points to copy different sections
    //   from parent DNAs.
    //
    // Both methods can NOT be used for the Travelling Salesman Problem because
    // this way some of the genes might be duplicated. The same route location
    // (gene) can be inserted from parent1 and parent2 but the Travelling
    // Salesman Problem demands that every route location is unique!
    //
    // There are some special crossover methods for TSP:
    //
    // - Partially-mapped crossover (PMX)
    // - Cycle crossover (CX)
    // - Position-based crossover (PBX)
    // - Order-based crossover (OBX)
    // - Order crossover (OX)
    //
    // One of the best methods is the order crossover (OX) which is used here.

    orderCrossover_OX(parent1, parent2);
}


void DNA_TSP::mutateGenes(double probability)
{
    // The DNA will be mutated by picking a single gene (point mutation) or
    // multiple genes (with a given rate / probability) and exchange them
    // with new genes from the set of all possible genes.
    //
    // This method can NOT be used for the Travelling Salesman Problem because
    // this way some of the genes will be duplicated. The same route location
    // may get inserted multiple times into the DNA but the Travelling Salesman
    // Problem demands that every route location is unique!
    //
    // Two of many possible solutions to solve this problem are:
    // 1) Pick one random gene in the DNA and swap it with its next neighbor.
    // 2) Pick two random genes in the DNA and swap them.
    // We are going to use the latter with a given probability:

    if (getRandomTrueWithProbability(probability))
    {
        int numberOfGene = rand() % amountOfResistors;
        _genes[numberOfGene] = (( rand() % (maxResistans*100) ) + 1)/100.0;//swapMutation();
    }

    // OPTIONAL:
    // There are specialized heuristics like the 2-opt local search algorithm
    // which tries to find better solutions for the Travelling Salesman Problem
    // by reordering the route locations when the route crosses over itself.
    // A Genetic Algorithm will find a global optimum solution much faster
    // when a local search algorithm will be used after the mutation.

    //twoOptLocalSearch();

    // When 2-opt search is used the population size can / should be very low!
    // Recommended parameters for the Genetic Algorithm when 2-opt is used:
    // populationCount = 100;
    // percentOfBestCanReproduce = 50.0;
    // recombinationProbability = 0.9;
    // mutationProbability = 0.02;

    // When 2-opt search is NOT used the population size has to be much higher!
    // Recommended parameters for the Genetic Algorithm when 2-opt is NOT used:
    // populationCount = 150000;
    // percentOfBestCanReproduce = 10.0;
    // recombinationProbability = 0.9;
    // mutationProbability = 0.02;
}


double DNA_TSP::calcFitness()
{
    // FITNESS FUNCTION

    // The fitness value of the DNA is defined by the total length of the
    // route. In this case of a Travelling Salesman Problem the objective
    // is to minimize the fitness value.
//    for(int i = 0; i < amountOfResistors; i++)
//        resistors[i] = _genes[i];
    double* R_input[hiddenLayerNeurons];
    for(int i = 0; i < hiddenLayerNeurons; i++)
    {
        double* r_in = new double[numberInputNeurons];
        for(int j = 0; j < numberInputNeurons; j++)
            r_in[j] = _genes[j+i*numberInputNeurons];
        R_input[i] = r_in;
    }
    double* r_out = new double[hiddenLayerNeurons];
    for(int i = 0; i < hiddenLayerNeurons; i++)
        r_out[i] = _genes[i+hiddenLayerNeurons*numberInputNeurons];
    //_fitness = _net->architecture_2_4_1(resistors);
   // _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,input_date,numberInputNeurons,false,coding);
//    _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,3,numberInputNeurons,false,coding);
//    _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,false,coding);
    switch( input_date )
    {
    case 1: case 2: case 4: case 8: case 16: case 32: case 64: case 128: case 256:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,input_date,numberInputNeurons,false,coding);
        break;
    case 3:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,false,coding);
        break;
    case 5:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,false,coding);
        break;
    case 6:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,false,coding);
        break;
    case 7:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,false,coding);
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,false,coding);
        break;
    case 9:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,false,coding);
        break;
    case 10:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,false,coding);
        break;
    case 11:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,false,coding);
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,false,coding);
        break;
    case 12:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,false,coding);
        break;
    case 13:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,false,coding);
        break;
    case 14:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,false,coding);
        break;
    case 15:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,false,coding);
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,false,coding);
        break;
    case 17:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,false,coding);
        break;
    case 18:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,false,coding);
        break;
    case 19:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,false,coding);
        break;
    case 20:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,false,coding);
        break;
    case 21:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,false,coding);
        break;
    case 22:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,false,coding);
        break;
    case 23:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,false,coding);
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,false,coding);
        break;
    case 24:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,false,coding);
        break;
    case 25:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,false,coding);
        break;
    case 26:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,false,coding);
        break;
    case 27:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,false,coding);
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,false,coding);
        break;
    case 28:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,false,coding);
        break;
    case 29:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,false,coding);
        break;
    case 30:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,false,coding);
        break;
    case 31:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,1,numberInputNeurons,false,coding);
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,2,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,4,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,8,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,16,numberInputNeurons,false,coding);
        break;

    case 96:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,32,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,64,numberInputNeurons,false,coding);
        break;
    case 160:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,32,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,128,numberInputNeurons,false,coding);
        break;
    case 192:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,64,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,128,numberInputNeurons,false,coding);
        break;
    case 288:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,32,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,256,numberInputNeurons,false,coding);
        break;
    case 320:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,64,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,256,numberInputNeurons,false,coding);
        break;
    case 352:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,128,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,256,numberInputNeurons,false,coding);
        break;
    case 384:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,32,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,64,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,256,numberInputNeurons,false,coding);
        break;
    case 416:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,32,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,128,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,256,numberInputNeurons,false,coding);
        break;
    case 448:
        _fitness = _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,64,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,128,numberInputNeurons,false,coding);
        _fitness += _net->architecture_X_N_1_time_encoding(R_input, r_out, hiddenLayerNeurons,256,numberInputNeurons,false,coding);
        break;
    default:
        //jakiś kod
        break;
    }

    //_fitness = calcRouteLength(_genes);

    // To get a better separation of different DNAs with a similar fitness,
    // the values can be squared to get exponential instead of linear results
    // (_fitness = _fitness * _fitness). Squared fitness values are not
    // beneficial in this case because the GeneticAlgorithm class uses a
    // rank based selection method for DNAs which sorts all fitness values.

    return _fitness;
}


double DNA_TSP::getFitness() const
{
    return _fitness;
}


string DNA_TSP::toString() const
{
    // This returns a string of all route locations which are represented
    // as indices of the coordinate arrays. The route is a loop and will be
    // shifted to always display index 0 as the first route location.
    //
    // The standard string has a move constructor, so returning long strings
    // by value is efficient.
    
    // Find the start of the route.

    size_t iRouteStart = 0;

    for (size_t iGene = 0; iGene < _genes.size(); iGene++)
        if (_genes[iGene] == 0)
        {
            iRouteStart = iGene;
            break;
        }

    // Get the elements from the route start index to the end of the array.

    string dnaStr = "[";

    for (size_t iGene = iRouteStart; iGene < _genes.size(); iGene++)
    {
        if (_genes[iGene] < 10)
            dnaStr += " ";

        dnaStr += std::to_string(_genes[iGene]) + ", ";
    }

    // Get the elements from the start of the array to the route start index.

    for (size_t iGene = 0; iGene < iRouteStart; iGene++)
    {
        if (_genes[iGene] < 10)
            dnaStr += " ";

        dnaStr += std::to_string(_genes[iGene]) + ", ";
    }

    return dnaStr + "]";
}


bool DNA_TSP::isSolved() const
{
    return _fitness == 0;//< _routeLength;
}


inline double DNA_TSP::calcRouteLength(const vector<double>& route)
{
    // This calculates the sum of all distances between successive
    // route locations.

    double totalLength = 0.0;

    for (size_t i = 0; i < route.size() - 1; i++)
        totalLength += euclidianDistance2D(
            _locationsX->at(route[i]),
            _locationsY->at(route[i]),
            _locationsX->at(route[i + 1]),
            _locationsY->at(route[i + 1]));

    // Add the distance from the last to the first route location.

    totalLength += euclidianDistance2D(
        _locationsX->at(route[route.size() - 1]),
        _locationsY->at(route[route.size() - 1]),
        _locationsX->at(route[0]),
        _locationsY->at(route[0]));

    return totalLength;
}


inline double DNA_TSP::euclidianDistance2D(
    double x1,
    double y1,
    double x2,
    double y2)
{
    return sqrt( pow(x1 - x2, 2.0) + pow(y1 - y2, 2.0) );
}


inline void DNA_TSP::orderCrossover_OX(
    const DNA_TSP& dna1,
    const DNA_TSP& dna2)
{
    // This crossover method will copy the genes of two parent DNAs
    // without creating any duplicates and by preserving their order. 
    // The result will be a valid route for the Travelling Salesman Problem.
    //
    // A section of genes from dna1 will be copied to this dna and the
    // remaining genes will be copied to this dna in the order in which they
    // appear in dna2.

    //  copy dna1._genes to _genes

    for (size_t iGene = 0; iGene <= dna1._genes.size(); iGene++)
        _genes[iGene] = dna1._genes[iGene];

    // Get a random start and end index for a section of dna1.

    size_t iSecStart = 0;
    size_t iSecEnd = 0;

    while (iSecStart >= iSecEnd)
    {
        iSecStart = rand() % amountOfResistors;//getRandomIntegerInRange<size_t>(0, dna1._genes.size() - 1);
        iSecEnd   = rand() % (amountOfResistors - iSecStart) + iSecStart;//getRandomIntegerInRange<size_t>(0, dna1._genes.size() - 1);
    }

    // Copy the section of dna2._genes to this _genes.

    for (size_t iGene = iSecStart; iGene <= iSecEnd; iGene++)
        _genes[iGene] = dna2._genes[iGene];

//    const size_t sectionSize = iSecEnd - iSecStart;

    // Copy the genes of dna2 without the genes found in the section of dna1.
    // The copying begins after the end index of the section. When the end of
    // dna2 is reached, copy the genes from the beginning of dna2 to the start
    // index of the section.

//    vector<double> dnaDifference;
//    dnaDifference.reserve(dna2._genes.size() - sectionSize);

//    if (iSecEnd + 1 <= dna2._genes.size() - 1)
//        for (size_t iGene = iSecEnd + 1; iGene < dna2._genes.size(); iGene++)
//            //if (!isGeneInSection(dna2._genes[iGene], iSecStart, iSecEnd))
//                dnaDifference.push_back(dna2._genes[iGene]);
//    if(iSecStart != 0)
//        for (size_t iGene = 0; iGene <= iSecStart; iGene++)//iGene <= iSecEnd
//            //if (!isGeneInSection(dna2._genes[iGene], iSecStart, iSecEnd))
//                dnaDifference.push_back(dna2._genes[iGene]);

    // The difference from dna1 and dna2 will be copied to this dna.
    // The insertion of genes into this dna begins after the end index of the
    // section. When the end of the dna is reached, insert the genes in the
    // beginning of the dna to the start index of the section.

//    size_t i = 0;

//    if (iSecEnd + 1 <= dna2._genes.size() - 1)
//        i = iSecEnd + 1;

//    for (size_t iGene = 0; iGene < dnaDifference.size(); iGene++)
//    {
//        _genes[i] = dnaDifference[iGene];
//        i++;
//        if (i > _genes.size() - 1)
//            i = 0;
//    }
}


inline bool DNA_TSP::isGeneInSection(
    size_t gene,
    size_t iSectionStart,
    size_t iSectionEnd) const
{
    for (size_t iGene = iSectionStart; iGene <= iSectionEnd; iGene++)
        if (gene == _genes[iGene])
            return true;

    return false;
}


inline void DNA_TSP::swapMutation()
{
    // This mutates the DNA in a minimal way by selecting two random genes
    // and swapping them with each other.

    const auto iGene1 = rand() % amountOfResistors;//getRandomIntegerInRange<size_t>(0, _genes.size() - 1);
    const auto iGene2 = rand() % amountOfResistors;//getRandomIntegerInRange<size_t>(0, _genes.size() - 1);

    const auto tempGene = _genes[iGene1];
    _genes[iGene1] = _genes[iGene2];
    _genes[iGene2] = tempGene;
}


inline void DNA_TSP::twoOptLocalSearch()
{
    // '2-opt' is a local search algorithm for optimizing a Travelling Salesman
    // Problem. It takes a route that crosses over itself and reorders the
    // locations to eliminate the cross over.

    // The reordering will be applied to all possible location pairs as long as
    // it can improve the total length of the route.

    bool hasImproved = true;
    double swappedGenesFitness = 0.0;
    vector<double> swappedGenes(_genes.size());

    while (hasImproved)
    {
        for (size_t iGene1 = 1; iGene1 < _genes.size() - 1; iGene1++)
        for (size_t iGene2 = iGene1 + 1; iGene2 < _genes.size(); iGene2++)
        {
            twoOptSwap(_genes, swappedGenes, iGene1, iGene2);
            swappedGenesFitness = calcRouteLength(swappedGenes);

            if (swappedGenesFitness < _fitness)
            {
                _genes.swap(swappedGenes);
                _fitness = swappedGenesFitness;
                hasImproved = true;
            }
            else { hasImproved = false; }
        }
    }
}


inline void DNA_TSP::twoOptSwap(
    const vector<double>& inGenes,
    vector<double>& outGenes,
    double iGene1,
    double iGene2)
{
    // Take inGenes[0] to inGenes[iGene1 - 1]
    // and add them in order to outGenes

    for (size_t iGene = 0; iGene <= iGene1 - 1; iGene++)
        outGenes[iGene] = inGenes[iGene];

    // Take inGenes[iGene1] to inGenes[iGene2] and
    // add them in reverse order to outGenes

    size_t iter = 0;
    for (size_t iGene = iGene1; iGene <= iGene2; iGene++)
    {
        outGenes[iGene] = inGenes[iGene2 - iter];
        iter++;
    }

    // Take inGenes[iGene2 + 1] to end of inGenes
    // and add them in order to outGenes

    for (size_t iGene = iGene2 + 1; iGene < inGenes.size(); iGene++)
        outGenes[iGene] = inGenes[iGene];
}

