#include "test_str.h"
#include <assert.h>

int main() {
	assert(test_cmp1());
	assert(test_cmp2());
	assert(test_cpy());
	assert(test_cat());
	assert(test_len());
	return 0;
}
