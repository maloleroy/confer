#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "assertions.h"
#include "print.h"

#define ASSERTION_PASSED true
#define ASSERTION_FAILED false

#define CF_ASSERTIONS_CONTEXT_ARGS struct cfScope *scope, unsigned int line, const char *file
#define CF_ASSERTIONS_CONTEXT scope, line, file

static char *bool_to_string(bool b);

#define _assert(condition, CF_ASSERTIONS_CONTEXT, format, ...) \
    if (condition)                                             \
    {                                                          \
        ++scope->assertions.passed;                            \
        return ASSERTION_PASSED;                               \
    }                                                          \
    else                                                       \
    {                                                          \
        ++scope->assertions.failed;                            \
        _cf_print_assertion_fail(file, __func__, line, scope);    \
        printf(format __VA_OPT__(, ) __VA_ARGS__);             \
        putc('\n', stdout);                                    \
        return ASSERTION_FAILED;                               \
    }

int _assert_null(void *p, CF_ASSERTIONS_CONTEXT_ARGS)
{
    _assert(p == NULL, CF_ASSERTIONS_CONTEXT, "(%p): is not null", p);
}
int _assert_not_null(void *p, CF_ASSERTIONS_CONTEXT_ARGS)
{
    _assert(p != NULL, CF_ASSERTIONS_CONTEXT, "(NULL): is null");
}
int _assert_pointer_equal(const void *p1, const void *p2, CF_ASSERTIONS_CONTEXT_ARGS)
{
    _assert(p1 == p2, CF_ASSERTIONS_CONTEXT, "(%p, %p): not the same pointer", p1, p2);
}
int _assert_pointer_not_equal(const void *p1, const void *p2, CF_ASSERTIONS_CONTEXT_ARGS)
{
    _assert(p1 != p2, CF_ASSERTIONS_CONTEXT, "(%p, %p): the same pointer", p1, p2);
}

int _assert_true(bool b, CF_ASSERTIONS_CONTEXT_ARGS)
{
    _assert(b == true, CF_ASSERTIONS_CONTEXT, "(%s): is not true", bool_to_string(b));
}
int _assert_false(bool b, CF_ASSERTIONS_CONTEXT_ARGS)
{
    _assert(b == false, CF_ASSERTIONS_CONTEXT, "(%s): is not false", bool_to_string(b));
}

int _assert_zero(int x, CF_ASSERTIONS_CONTEXT_ARGS)
{
    _assert(x == 0, CF_ASSERTIONS_CONTEXT, "(%d): is not zero", x);
}
int _assert_non_zero(int x, CF_ASSERTIONS_CONTEXT_ARGS)
{
    _assert(x, CF_ASSERTIONS_CONTEXT, "(0): is zero");
}

int _assert_int_equal(int x, int y, CF_ASSERTIONS_CONTEXT_ARGS)
{
    _assert(x == y, CF_ASSERTIONS_CONTEXT, "(%d, %d): are not equal", x, y);
}
int _assert_int_not_equal(int x, int y, CF_ASSERTIONS_CONTEXT_ARGS)
{
    _assert(x != y, CF_ASSERTIONS_CONTEXT, "(%d, %d): are equal", x, y);
}

int _assert_int_ge(int x, int y, CF_ASSERTIONS_CONTEXT_ARGS)
{
    _assert(x >= y, CF_ASSERTIONS_CONTEXT, "(%d, %d): not greater or equal", x, y);
}
int _assert_int_le(int x, int y, CF_ASSERTIONS_CONTEXT_ARGS)
{
    _assert(x <= y, CF_ASSERTIONS_CONTEXT, "(%d, %d): not less or equal equal", x, y);
}
int _assert_int_greater(int x, int y, CF_ASSERTIONS_CONTEXT_ARGS)
{
    _assert(x > y, CF_ASSERTIONS_CONTEXT, "(%d, %d): not greater", x, y);
}
int _assert_int_less(int x, int y, CF_ASSERTIONS_CONTEXT_ARGS)
{
    _assert(x < y, CF_ASSERTIONS_CONTEXT, "(%d, %d): not less", x, y);
}
int _assert_int_non_negative(int x, CF_ASSERTIONS_CONTEXT_ARGS)
{
    _assert(x >= 0, CF_ASSERTIONS_CONTEXT, "(%d): negative", x);
}
int _assert_int_non_positive(int x, CF_ASSERTIONS_CONTEXT_ARGS)
{
    _assert(x <= 0, CF_ASSERTIONS_CONTEXT, "(%d): positive", x);
}
int _assert_int_nositive(int x, CF_ASSERTIONS_CONTEXT_ARGS)
{
    _assert(x > 0, CF_ASSERTIONS_CONTEXT, "(%d): negative or zero", x);
}
int _assert_int_negative(int x, CF_ASSERTIONS_CONTEXT_ARGS)
{
    _assert(x < 0, CF_ASSERTIONS_CONTEXT, "(%d): positive or zero", x);
}

int _assert_char_equal(char c1, char c2, CF_ASSERTIONS_CONTEXT_ARGS)
{
    _assert(c1 == c2, CF_ASSERTIONS_CONTEXT, "(%c, %c): not the same character", c1, c2);
}
int _assert_char_not_equal(char c1, char c2, CF_ASSERTIONS_CONTEXT_ARGS)
{
    _assert(c1 != c2, CF_ASSERTIONS_CONTEXT, "(%c, %c): are the same character", c1, c2);
}

int _assert_byte_equal(unsigned char b1, unsigned char b2, CF_ASSERTIONS_CONTEXT_ARGS)
{
    _assert(b1 == b2, CF_ASSERTIONS_CONTEXT, "(%d, %d): not the same byte", b1, b2);
}
int _assert_byte_not_equal(unsigned char b1, unsigned char b2, CF_ASSERTIONS_CONTEXT_ARGS)
{
    _assert(b1 != b2, CF_ASSERTIONS_CONTEXT, "(%d, %d): are the same byte", b1, b2);
}

int _assert_string_equal(const char *s1, const char *s2, CF_ASSERTIONS_CONTEXT_ARGS)
{
    _assert(strcmp(s1, s2) == 0, CF_ASSERTIONS_CONTEXT, "(%s, %s): are not equal", s1, s2);
}
int _assert_string_not_equal(const char *s1, const char *s2, CF_ASSERTIONS_CONTEXT_ARGS)
{
    _assert(strcmp(s1, s2) != 0, CF_ASSERTIONS_CONTEXT, "(\"%s\", \"%s\"): are equal", s1, s2);
}

static char *bool_to_string(bool b)
{
    static char s[6];
    if (b == false)
        strcpy(s, "false");
    else if (b == true)
        strcpy(s, "true");
    else
        sprintf(s, "%d", b);
    return s;
}

int _assert_true_chain(bool b, _ASSERT_ARGS)
{
    _assert(b == true, CF_ASSERTIONS_CONTEXT, " call to function returned false");
}

int _assert_false_chain(bool b, _ASSERT_ARGS)
{
    _assert(b == false, CF_ASSERTIONS_CONTEXT, " call to function returned true");
}
