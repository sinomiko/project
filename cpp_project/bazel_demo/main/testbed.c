#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "activations.h"
#include "lib/timer.h"
#include "lib/random.h"


// return a random float in (s, t)
float get_random(float s, float t){
    float v = (float)(rand()) / RAND_MAX;
    v = v * (t-s) + s;
    return v;
}

int main(){
    const int maxn = 5;
    srand(time(0));
    for(int i=0; i<maxn; i++) {
        float x = get_random(-2.0f, 2.0f);
        float res_relu = relu(x);
        float res_sigmoid = sigmoid(x);
        printf("x=%f\n", x);
        printf("relu(x)=%f\n", res_relu);
        printf("sigmoid(x)=%f\n", res_sigmoid);
        printf("\n");
    }
    RandomPrint();
    TimerPrint();

    return 0;
}
