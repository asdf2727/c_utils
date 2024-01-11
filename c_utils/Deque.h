#ifndef C_UTILS_DEQUE_H
#define C_UTILS_DEQUE_H

#include "base.h"

struct Deque {
	void *ptr;

	size_t type_size;
	size_t max_size;
	size_t used_size;

	size_t start_pos;
};

struct Deque _deque_new (size_t type_size);

void _deque_resize (struct Deque *vec, size_t new_size);

void _deque_push_back (struct Deque *vec, const void *val);
void _deque_pop_back (struct Deque *vec);
void _deque_push_front (struct Deque *vec, const void *val);
void _deque_pop_front (struct Deque *vec);

bool _deque_is_empty (const struct Deque *vec);
size_t _deque_size (const struct Deque *vec);

void *_deque_at (struct Deque *vec, size_t pos);

#define deque_new(type) \
    _deque_new(sizeof(type))

#define deque_push_back(vec, val) \
    _deque_push_back(&vec, &val)
#define deque_pop_back(vec) \
    _deque_pop_back(&vec)
#define deque_push_front(vec, val) \
    _deque_push_front(&vec, &val)
#define deque_pop_front(vec) \
    _deque_pop_front(&vec)

#define deque_is_empty(vec) \
    _deque_is_empty(&vec)
#define deque_size(vec) \
    _deque_size(&vec)

#define deque_at(vec, pos, type) \
    *(type *)_deque_at(&vec, pos)

#ifdef DEBUG
void _deque_show (struct Deque *vec);
#define deque_show(vec) \
	_deque_show(&vec)
#endif

#endif //C_UTILS_DEQUE_H
