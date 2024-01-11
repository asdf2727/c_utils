#include <stdio.h>

#include "c_utils/c_utils.h"

int main () {
	struct Deque vec = deque_new(int);

	for (int i = 0; i < 1000000; i++) {
		if (i & 1) {
			deque_push_back(vec, i);
		}
		else {
			deque_push_front(vec, i);
		}
	}
	for (int i = 0; i < 1000000; i++) {
		deque_pop_front(vec);
	}

	printf("%d\n", deque_is_empty(vec));
	for (int i = 0; i < deque_size(vec); i++) {
		printf("%d ", deque_at(vec, i, int));
	}

	return 0;
}