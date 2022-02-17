#include "preprocessing.h"

using namespace std;

vector<vector<double>> dataSetToVector(const string &filename)
{
    ifstream inFile;
    string line;
    vector<vector<double>> dataSetVector; // = new vector<vector<double>>;

    // create 11 vectors, one for each feature + 1 for class
    vector<double> age;
    vector<double> gender;
    vector<double> height_cm;
    vector<double> weight_kg;
    vector<double> body_fat;
    vector<double> diastolic;
    vector<double> systolic;
    vector<double> grip_force;
    vector<double> sit_and_bend_forward_cm;
    vector<double> sit_up_count;
    vector<double> broad_jump_cm;
    vector<double> class_label;

    double ageF, height_cmF, weight_kgF, body_fatF, diastolicF, systolicF, grip_forceF, sit_and_bend_forward_cmF, sit_up_countF, broad_jump_cmF, class_labelF;
    string genderVal;

    // read in file
    inFile.open(filename);
    if (inFile.is_open())
    {
        while (getline(inFile, line))
        {
            replace(line.begin(), line.end(), ',', ' ');

            istringstream iss(line);

            iss >> ageF >> genderVal >> height_cmF >> weight_kgF >> body_fatF >> diastolicF >> systolicF >> grip_forceF >> sit_and_bend_forward_cmF >> sit_up_countF >> broad_jump_cmF >> class_labelF;

            age.push_back(ageF);
            // convert F/M to double 1.0/0.0
            if (genderVal.compare("F") == 0)
                gender.push_back(1.0);
            else
                gender.push_back(0.0);

            height_cm.push_back(height_cmF);
            weight_kg.push_back(weight_kgF);
            body_fat.push_back(body_fatF);
            diastolic.push_back(diastolicF);
            systolic.push_back(systolicF);
            grip_force.push_back(grip_forceF);
            sit_and_bend_forward_cm.push_back(sit_and_bend_forward_cmF);
            sit_up_count.push_back(sit_up_countF);
            broad_jump_cm.push_back(broad_jump_cmF);
            class_label.push_back(class_labelF);
        }

        dataSetVector.push_back(age);
        dataSetVector.push_back(gender);
        dataSetVector.push_back(height_cm);
        dataSetVector.push_back(weight_kg);
        dataSetVector.push_back(body_fat);
        dataSetVector.push_back(diastolic);
        dataSetVector.push_back(systolic);
        dataSetVector.push_back(grip_force);
        dataSetVector.push_back(sit_and_bend_forward_cm);
        dataSetVector.push_back(sit_up_count);
        dataSetVector.push_back(broad_jump_cm);
        dataSetVector.push_back(class_label);
    }

    return dataSetVector;
}

std::vector<std::vector<double>> splitDataByClass(const std::vector<std::vector<double>> &dataset, const double &classLabel)
{
    // make vector of 11 empty vectors
    vector<vector<double>> split(11, vector<double>(0));

    vector<double>::const_iterator datapoint;

    const vector<double> &classVector = dataset[11];

    int element = 0;

    // put dataset[0:10][x] in split[0:10] if classVector[x] == classLabel
    // iterate down class vector

    for (datapoint = classVector.begin(); datapoint != classVector.end(); ++datapoint)
    {
        // if class vector label matches
        if (*datapoint == classLabel)
        {
            for (int i = 0; i < 11; i++)
            {
                split[i].push_back(dataset[i][element]);
            }
        }
        element++;
    }

    return split;
}

double getAccuracy(const std::vector<double> &predicted, const std::vector<double> &actual)
{
    int element = 0;
    int correct = 0;
    for (vector<double>::const_iterator datapoint = predicted.begin(); datapoint != predicted.end(); ++datapoint)
    {
        if (predicted[element] == actual[element])
        {
            correct++;
        }
        element++;
    }

    return (double)correct / element;
}