#include "algorithm.h"
#include "util.h"
#include "io.h"

void logDebug(char c) {
	return;
}

int main() {
	int a = doComputation(5, 7.0); 
	int b = 5;
	max(a, b);
	logDebug('!');   
	return 0;
}
