#include <stdlib.h>
#include <math.h>
#include "random.h"

/*
 * The function randomGaussian generates random numbers with a Gaussian distribution.
 * It takes mean and standard deviation as parameters and returns a double.
 */

double randomGaussian(int mean, int stddev) {
    // Calculate the mean and standard deviation as doubles
    double meanValue = (double) mean;
    double stdDev = fabs((double) stddev);

    // Generate two random values using the Box-Muller transform
    double rand1 = sqrt(-2.0 * log((double) rand() / (double) RAND_MAX));
    double rand2 = 2.0 * M_PI * (double) rand() / (double) RAND_MAX;

    // Combine the random values to get a Gaussian-distributed result
    double gaussianValue = meanValue + stdDev * cos(rand2) * rand1;

    return gaussianValue;
}
