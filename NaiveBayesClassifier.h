#ifndef NAIVE_BAYES_CLASSIFIER_H
#define NAIVE_BAYES_CLASSIFIER_H

#include <vector>
#include <iostream>
#include "probability.h"
#include "preprocessing.h"
#include "probability.h"

using namespace std;

typedef struct meanVariance
{
    vector<vector<double>> meanVarVector;
    double classLabel;
    double classProbability;
} meanVariance;

class NaiveBayesClassifier
{
private:
    // stores mean stddev pairs for a given feature and a given class
    vector<meanVariance> pairs;
    meanVariance getMeanVariance(const vector<vector<double>> &dataset, const double &classLabel);

public:
    void fit(const vector<vector<double>> &trainingData);
    vector<double> predict(const vector<vector<double>> &testData);
};

#endif