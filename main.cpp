#include "NaiveBayesClassifier.h"
#include "preprocessing.h"
#include "probability.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        return -1;
    }

    vector<vector<double>> trainingData = dataSetToVector(argv[1]);
    std::vector<std::vector<double>> testingData = dataSetToVector(argv[2]);

    NaiveBayesClassifier nbc = NaiveBayesClassifier();

    nbc.fit(trainingData);

    vector<double> predicted;

    predicted = nbc.predict(testingData);

    // cout << "Classifier had : " << getAccuracy(predicted, testingData[11]) << "\% accuracy on testing set" << endl;

    for (auto i : predicted)
    {
        cout << i << endl;
    }

    return 0;
}