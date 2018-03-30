#include "Quat.h"

double dotProduct(const double x[3], const double y[3]){
    double s = 0;
    for (size_t i = 0; i < 3; i++)
        s += x[i] * y[i];
    return s;
}
