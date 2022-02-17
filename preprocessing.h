#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

std::vector<std::vector<double>> dataSetToVector(const std::string &filename);
std::vector<std::vector<double>> splitDataByClass(const std::vector<std::vector<double>> &dataset, const double &classLabel);
double getAccuracy(const std::vector<double> &predicted, const std::vector<double> &actual);

#endif