#include "probability.h"

// process to calculate mean taken from http://stackoverflow.com/questions/28574346/find-average-of-input-to-vector-c

double getMean(const std::vector<double> &data)
{
    if (data.empty())
        return 0;

    auto const count = static_cast<double>(data.size());
    return std::accumulate(data.begin(), data.end(), 0.0) / count;
}

// stddev calculation taken from http://stackoverflow.com/questions/7616511/calculate-mean-and-standard-deviation-from-a-vector-of-samples-in-c-using-boos

double getStdDev(const std::vector<double> &data, const double &mean)
{
    // double mean = getMean(data);

    auto const count = static_cast<double>(data.size());

    std::vector<double> diff(count);
    // lambda functions and std::transform are crazy man
    // use to calc x_i - mu
    std::transform(data.begin(), data.end(), diff.begin(), [mean](double x)
                   { return x - mean; });
    // get sum of squared differences
    double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
    // square root of sum of differences
    double stddev = std::sqrt(sq_sum / count);

    return stddev;
}

double getVariance(const std::vector<double> &data, const double &mean)
{
    // double mean = getMean(data);

    auto const count = static_cast<double>(data.size());

    std::vector<double> diff(count);
    // lambda functions and std::transform are crazy man
    // use to calc x_i - mu
    std::transform(data.begin(), data.end(), diff.begin(), [mean](double x)
                   { return x - mean; });
    // get sum of squared differences
    double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
    // sum of squared differences over N = variance
    double variance = sq_sum / count;

    return variance;
}

double getProbability(const double &val, const double &mean, const double &stdDev)
{
    double zscore = val - mean / stdDev;
    std::cout << zscore << std::endl;
    return 0.5 * (1 + std::erf(zscore * M_SQRT1_2));
}

double getConditionalProbability(const double &val, const double &mean, const double &variance)
{
    return (1 / std::sqrt(2 * M_PI * variance)) * std::exp(-((val - mean) * (val - mean)) / (2 * variance));
}