#include "NaiveBayesClassifier.h"

meanVariance NaiveBayesClassifier::getMeanVariance(const vector<vector<double>> &dataset, const double &classLabel)
{
    // need to run once for class = 0, once for class = 1
    vector<vector<double>> split = splitDataByClass(dataset, classLabel);

    meanVariance tempOut;

    tempOut.classLabel = classLabel;

    double classMean = getMean(dataset[11]);
    // double classStdDev = getStdDev(dataset[11], classMean);

    // cout << "Mean: " << classMean << " StdDev: " << classStdDev << endl;

    if (classLabel == 0)
    {
        tempOut.classProbability = 1 - classMean;
    }
    else if (classLabel == 1)
    {
        tempOut.classProbability = classMean;
    }

    // tempOut.classProbability = getProbability(classLabel, classMean, classStdDev);

    // cout << "Prob C = " << classLabel << ": " << tempOut.classProbability << endl;

    // have dataset with only datapoints with class = 0 for example
    // get means for all 11 features of split
    vector<vector<double>>::const_iterator it = split.begin();

    vector<double> featureMeanVariance;

    double mean, variance;

    for (it = split.begin(); it != split.end(); it++)
    {
        featureMeanVariance.clear();
        // get mean for feature
        mean = getMean(*it);
        featureMeanVariance.push_back(mean);
        // get variance for feature
        variance = getVariance(*it, mean);
        featureMeanVariance.push_back(variance);
        // add mean variance pair to mean variance vector
        tempOut.meanVarVector.push_back(featureMeanVariance);
    }

    return tempOut;
}

void NaiveBayesClassifier::fit(const vector<vector<double>> &trainingData)
{
    // determine mean and standard deviation for all features given c == 0 and c == 1
    // store them in meanStdDev vector vector
    pairs.push_back(getMeanVariance(trainingData, 0.0));
    pairs.push_back(getMeanVariance(trainingData, 1.0));
}

vector<double> NaiveBayesClassifier::predict(const vector<vector<double>> &testData)
{
    // then to predict values, do this bit
    // p(C=c | x_1=x1, x_2=x2 ...) = p(c) * p(x_1=x1 | C=c) * p(x_2=x2 | C=c) ...
    vector<double> predicted;

    double probNeg = pairs[0].classProbability;
    double probPos = pairs[1].classProbability;

    // cout << probNeg << " " << probPos << endl;

    int element = 0;
    vector<double> conditionalProbabilities;

    for (vector<double>::const_iterator itr = testData[0].begin(); itr != testData[0].end(); ++itr)
    {
        // whenever looking at boolean variable, make sure to just use mean as probability i guess
        for (int i = 0; i < 11; i++)
        {
            // calc p(C=0.0 | x_1 = testData[0][i], x_2 = testData[1][i]...)
            probNeg *= getConditionalProbability(testData[i][element], pairs[0].meanVarVector[i][0], pairs[0].meanVarVector[i][1]);
            // calc p(C=1.0 | x_1 = testData[0][i], x_2 = testData[1][i]...) = p(C=1.0) * p(x_1 = testData[0][i] | C=1.0) ...
            probPos *= getConditionalProbability(testData[i][element], pairs[1].meanVarVector[i][0], pairs[1].meanVarVector[i][1]);
        }

        if (probPos >= probNeg)
        {
            predicted.push_back(1);
        }
        else
        {
            predicted.push_back(0);
        }

        probNeg = pairs[0].classProbability;
        probPos = pairs[1].classProbability;
        element++;
    }

    // append max to predicted
    return predicted;
}