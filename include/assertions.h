#ifndef CF_SCOPES_ASSERT_H
#define CF_SCOPES_ASSERT_H 1
#include <stdbool.h>
#include "build.h"

#define assert_is_null assert_null
#define assertIsNotNull assert_not_null
#define _ASSERT_ARGS struct cfScope *scope, unsigned int line, const char *file
#define ASSERT_ARGS self, __LINE__, __FILE__

int _assert_true(bool b, _ASSERT_ARGS);
int _assert_false(bool b, _ASSERT_ARGS);

int _assert_null(void *p, _ASSERT_ARGS);
int _assert_not_null(void *p, _ASSERT_ARGS);
int _assert_pointer_equal(const void *p1, const void *p2, _ASSERT_ARGS);
int _assert_pointer_not_equal(const void *p1, const void *p2, _ASSERT_ARGS);

int _assert_zero(int x, _ASSERT_ARGS);
int _assert_non_zero(int x, _ASSERT_ARGS);
int _assert_int_equal(int x, int y, _ASSERT_ARGS);
int _assert_int_not_equal(int x, int y, _ASSERT_ARGS);

int _assert_int_ge(int x, int y, _ASSERT_ARGS);
int _assert_int_le(int x, int y, _ASSERT_ARGS);
int _assert_int_greater(int x, int y, _ASSERT_ARGS);
int _assert_int_less(int x, int y, _ASSERT_ARGS);
int _assert_int_non_negative(int x, _ASSERT_ARGS);
int _assert_int_non_positive(int x, _ASSERT_ARGS);
int _assert_int_positive(int x, _ASSERT_ARGS);
int _assert_int_negative(int x, _ASSERT_ARGS);

int _assert_char_equal(char c1, char c2, _ASSERT_ARGS);
int _assert_char_not_equal(char c1, char c2, _ASSERT_ARGS);

int _assert_byte_equal(unsigned char b1, unsigned char b2, _ASSERT_ARGS);
int _assert_byte_not_equal(unsigned char b1, unsigned char b2, _ASSERT_ARGS);

int _assert_string_equal(const char *s1, const char *s2, _ASSERT_ARGS);
int _assert_string_not_equal(const char *s1, const char *s2, _ASSERT_ARGS);

int _assert_true_chain(bool b, _ASSERT_ARGS);
int _assert_false_chain(bool b, _ASSERT_ARGS);

#define assert_true(b) _assert_true(b, ASSERT_ARGS)
#define assert_false(b) _assert_false(b, ASSERT_ARGS)

#define assert_null(p) _assert_null(p, ASSERT_ARGS)
#define assert_not_null(p) _assert_not_null(p, ASSERT_ARGS)
#define assert_pointer_equal(p1, p2) _assert_pointer_equal(p1, p2, ASSERT_ARGS)
#define assert_pointer_not_equal(p1, p2) _assert_pointer_not_equal(p1, p2, ASSERT_ARGS)

#define assert_zero(x) _assert_zero(x, ASSERT_ARGS)
#define assert_non_zero(x) _assert_non_zero(x, ASSERT_ARGS)
#define assert_int_equal(x, y) _assert_int_equal(x, y, ASSERT_ARGS)
#define assert_int_not_equal(x, y) _assert_int_not_equal(x, y, ASSERT_ARGS)

#define assert_int_ge(x, y) _assert_int_ge(x, y, ASSERT_ARGS)
#define assert_int_le(x, y) _assert_int_le(x, y, ASSERT_ARGS)
#define assert_int_greater(x, y) _assert_int_greater(x, y, ASSERT_ARGS)
#define assert_int_less(x, y) _assert_int_less(x, y, ASSERT_ARGS)
#define assert_int_non_negative(x) _assert_int_non_negative(x, ASSERT_ARGS)
#define assert_int_non_positive(x) _assert_int_non_positive(x, ASSERT_ARGS)
#define assert_int_positive(x) _assert_int_positive(x, ASSERT_ARGS)
#define assert_int_negative(x) _assert_int_negative(x, ASSERT_ARGS)

#define assert_char_equal(x, y) _assert_char_equal(x, y, ASSERT_ARGS)
#define assert_char_not_equal(x, y) _assert_char_not_equal(x, y, ASSERT_ARGS)

#define assert_string_equal(s1, s2) _assert_string_equal(s1, s2, ASSERT_ARGS)
#define assert_string_not_equal(p1, p2) _assert_string_not_equal(p1, p2, ASSERT_ARGS)

#define assert_chain(f, ...) _assert_true_chain(f(__VA_ARGS__), ASSERT_ARGS)
#define assert_chain_not(f, ...) _assert_false_chain(f(__VA_ARGS__), ASSERT_ARGS)

#endif
