//Copyright Grigory Ponomarenko 2016 (c)

#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
#include "BalashException.h"

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
    void branch(unsigned int value);
    /* Checking solution is permissible funstion. */
    bool checkSolutionPermissible(unsigned int value);
    /* Computing cost computing function. */
    int getResultFunction(unsigned int value);
    /* Cutting branches function. */
    void markBranchAsUnavailable(unsigned int value);
    /* Comparing solutions in tree with record function. */
    void checkSolutionsBiggerThenRecord(unsigned int value, int result);

    /* Printing solution. */
    void printResult(int);

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

    /* Subsets assert. */
    int* subsets;

    int record;
    unsigned int recordSet;
};
