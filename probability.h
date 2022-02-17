#ifndef PROBABILITY_H
#define PROBABILITY_H

#include <cmath>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <vector>

double getMean(const std::vector<double> &data);
double getStdDev(const std::vector<double> &data, const double &mean);
double getVariance(const std::vector<double> &data, const double &mean);
double getProbability(const double &val, const double &mean, const double &stdDev);
double getConditionalProbability(const double &val, const double &mean, const double &variance);

#endif