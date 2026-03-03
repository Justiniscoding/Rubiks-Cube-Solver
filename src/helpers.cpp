#include "helpers.h"

long factorial(int n) {
	long result = 1;

	for (int i = 2; i <= n; i++) {
		result *= i;
	}

	return result;
}

long nCr(int n, int r) {
	return factorial(n) / (factorial(r) * factorial(n - r));
}
