//Copyright Grigory Ponomarenko 2016 (c)

#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <bitset>
#include "BalashException.h"

#define MAX_N 1024

class Balash {
  /* Balash method for set cover problem solving. */
  public:
    Balash();
    ~Balash();

    /* Initializing the class. */
    void initialize(char*, char*);

    /* Main function to find a solution. */
    void compute();

  private:
    /* Parse datas from input file*/
    void getToolsCount();
    void getCostVector();
    void getThreatsCount();
    void getCoverageMatrix();

    /* Check and confirm input data. */
    void checkInputCostString(std::string);
    void checkInputCoverageString(std::string);
    
    /* Sort costs by order. */
    void sortByCost();
    
    /* Find zero lines or rows in coverage matrix. */
    void checkCoverageMatrix();
   
    /* Solving functions. */
    /* Main branching function. */
    void branch(std::bitset<MAX_N> value);
    /* Checking solution is permissible funstion. */
    bool checkSolutionPermissible(std::bitset<MAX_N> value);
    /* Computing cost computing function. */
    int getResultFunction(std::bitset<MAX_N> value);

    /* Printing solution. */
    void printResult(std::bitset<MAX_N> result);

    /* Input and output paths and streams. */
    std::string inputPath;
    std::string outputPath;
    std::fstream inFile;
    std::fstream outFile;

    /* Count of threats and tools. */
    int threats;
    int tools;

    /* Array of product indexes before sorting. */
    int* oldOrder;

    /* Cost vector. */
    int* cost;
    
    /* Coverage Matrix. */
    int** cov;

    int record;
    std::bitset<MAX_N> recordSet;
};
