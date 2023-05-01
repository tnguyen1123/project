#include <stdio.h>
#include <math.h>
#include "roots.h"
float compute_c1(float a1, float a2, float y0, float y1, float lambda1, float lambda2) {
    return (y1 - (lambda2 * y0)) / (lambda1 - lambda2);
}

float compute_c2(float a1, float a2, float y0, float y1, float lambda1, float lambda2) {
    return ((lambda1 * y0 )- y1) / (lambda1 - lambda2);
}

float compute_theta(float alpha, float beta) {
    return atan(beta / alpha);
}

int main() {
    float a1, a2, y0, y1;
    printf("Enter the coefficients (a1, a2): ");
    scanf("%f %f", &a1, &a2);
    printf("Enter the initial conditions (y0, y1): ");
    scanf("%f %f", &y0, &y1);

    float lambda1, lambda2;
	float real, imag;
    find_roots(a1, a2, lambda1, lambda2, real, imag);

    if (lambda1 == lambda2) { // Repeating real roots
        float C1, C2;
        C1 = y0;
        C2 = y1 - lambda1 * y0;
        printf("y(t) = (%.2f + %.2ft)e^(%.2ft)\n", C1, C2, lambda1);
    }
    else if (lambda1 != lambda2) { // Distinct real roots
        float C1, C2;
        C1 = compute_c1(a1, a2, y0, y1, lambda1, lambda2);
        C2 = compute_c2(a1, a2, y0, y1, lambda1, lambda2);
        printf("y(t) = %.2fe^(%.2ft) + %.2fe^(%.2ft)\n", C1, lambda1, C2, lambda2);
    }
    else { // Complex conjugate roots
        float alpha = -a1 / 2;
        float beta = sqrt(-a2);
        float C = (sqrt(y0 * y0 + (y1 - alpha * y0) * (y1 - alpha * y0))) / beta;
        float theta = compute_theta(alpha, beta);
        printf("y(t) = %.2f e^(%0.2f)tcos(%.2f t + %.2f t)\n", C, alpha, beta, theta);
    }

    return 0;
}

void find_roots(float a1, float a2, float lambda1, float lambda2, float real, float imag ) {
    float discriminant = a1*a1 - 4*a2;
    float i;

    if (discriminant > 0) {
        lambda1 = (-a1 + sqrt(discriminant)) / 2;
        lambda2 = (-a1 - sqrt(discriminant)) / 2;
        printf("root1 = %.2lf and root2 = %.2lf \n", lambda1, lambda2);
    }
    else if (discriminant == 0) {
        lambda1 = lambda2 = -a1 / 2;
        printf("root1 = root2 = %.2lf \n", lambda1);
    }
    else {
        real = -a1 / 2;
        imag = (sqrt(-discriminant)) / 2;
        lambda1 = real + imag*i;
        lambda2 = real - imag*i;
        printf("root1 = %.0f + %.0fi and root2 = %.0f - %.0fi \n", real, imag, real, imag);
    }
}

