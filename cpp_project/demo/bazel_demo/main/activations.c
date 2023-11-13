#include "activations.h"
#include <math.h>

float relu(float x){
    if (x>=0) return x;
    return 0;
}

float sigmoid(float x){
    return 1.0f / (1.0f + exp(-x));
}