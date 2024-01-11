
#include "Deque.h"

#define NORM(val) \
    ((val) & (vec->max_size - 1))

struct Deque _deque_new (size_t type_size) {
	struct Deque ret;

	ret.type_size = type_size;
	ret.max_size = type_size;
	ret.ptr = malloc(type_size);

	ret.used_size = 0;
	ret.start_pos = 0;

	return ret;
}

void _deque_resize (struct Deque *vec, size_t new_size) {
	void *new_ptr = malloc(new_size);

	vec->used_size = min(vec->used_size, new_size);
	if (vec->start_pos + vec->used_size >= vec->max_size) {
		memcpy(new_ptr, vec->ptr + vec->start_pos, vec->max_size - vec->start_pos);
		memcpy(new_ptr + vec->max_size - vec->start_pos, vec->ptr, vec->start_pos + vec->used_size - vec->max_size);
	}
	else if (vec->used_size) {
		memcpy(new_ptr, vec->ptr + vec->start_pos, vec->used_size);
	}
	free(vec->ptr);
	vec->ptr = new_ptr;

	vec->max_size = new_size;
	vec->start_pos = 0;
}

void _deque_push_back (struct Deque *vec, const void *val) {
	if (vec->used_size + vec->type_size == vec->max_size) {
		_deque_resize(vec, vec->max_size << 1);
	}
	memcpy(vec->ptr + NORM(vec->start_pos + vec->used_size), val, vec->type_size);
	vec->used_size += vec->type_size;
}
void _deque_pop_back (struct Deque *vec) {
	assertf(vec->used_size, "Popped out of an empty deque");
	vec->used_size -= vec->type_size;
	if (vec->used_size <= vec->max_size >> 2) {
		_deque_resize(vec, vec->max_size >> 1);
	}
}
void _deque_push_front (struct Deque *vec, const void *val) {
	if (vec->used_size + vec->type_size == vec->max_size) {
		_deque_resize(vec, vec->max_size << 1);
	}
	vec->start_pos = NORM(vec->start_pos - vec->type_size);
	vec->used_size += vec->type_size;
	memcpy(vec->ptr + vec->start_pos, val, vec->type_size);
}
void _deque_pop_front (struct Deque *vec) {
	assertf(vec->used_size, "Popped out of an empty deque");
	vec->start_pos = NORM(vec->start_pos + vec->type_size);
	vec->used_size -= vec->type_size;
	if (vec->used_size <= vec->max_size >> 2) {
		_deque_resize(vec, vec->max_size >> 1);
	}
}

bool _deque_is_empty (const struct Deque *vec) {
	return vec->used_size == 0;
}
size_t _deque_size (const struct Deque *vec) {
	return vec->used_size / vec->type_size;
}

void *_deque_at (struct Deque *vec, size_t pos) {
	return vec->ptr + NORM(vec->start_pos + pos * vec->type_size);
}

#ifdef DEBUG
void _deque_show (struct Deque *vec) {
	fprintf(stderr, "State of deque: \n");
	for (size_t i = 0; i < vec->max_size; i += vec->type_size) {
		if (i == vec->start_pos) {
			fprintf(stderr, "[");
		}
		if (i == ((vec->start_pos + vec->used_size) & (vec->max_size - 1))) {
			fprintf(stderr, "]");
		}
		fprintf(stderr, "%d ", *(int *)(vec->ptr + i));
	}
	fprintf(stderr, "\n%llx: %lld - %lld %lld - %lld\n\n", vec->ptr, vec->type_size, vec->max_size, vec->used_size, vec->start_pos);
}
#endif

#undef NORM