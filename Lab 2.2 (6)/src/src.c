#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

double getDouble(double lowBound, double highBound) {
    double input;
    char ch;
    while (scanf("%lf%c", &input, &ch) != 2 || ch != '\n' || input < lowBound || input > highBound) {
        printf("Enter another number. Possible from %lf to %lf\n", lowBound, highBound);
        while (getchar() != '\n') {
        }
    }
    return input;
}

int sinDecomposion(double angle, double standardAnswer, double eps) {
    if (angle <= eps) {
        return 0;
    }
    int n = 1;
    int fact = 2;
    double denominator = 1;
    double numerator = angle;
    double currentAnswer = angle;

    while (fabs(currentAnswer - standardAnswer) >= eps) {
        numerator *= angle * angle;
        denominator *= fact * (fact + 1);
        fact += 2;
        double value = numerator / denominator;
        if (n % 2 == 0) {
            currentAnswer += value;
        }
        else {
            currentAnswer -= value;
        }
        n++;
    }
    return n;
}