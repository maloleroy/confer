#include <stddef.h>
#include <confer.h>
#include <assertions.h>

void test_bool_assertions(CFTEST);
void test_pointers_assertions(CFTEST);
void test_int_assertions(CFTEST);
void test_int_equal(CFTEST);
void test_int_compare(CFTEST);
void test_char_assertions(CFTEST);
void test_byte_assertions(CFTEST);
void test_string_assertions(CFTEST);
void test_chain_assertions(CFTEST);

void test_assertions(CFTEST)
{
    cf_test(test_bool_assertions);
    cf_test(test_pointers_assertions);
    cf_test(test_int_assertions);
    cf_test(test_char_assertions);
    cf_test(test_byte_assertions);
    cf_test(test_string_assertions);
    cf_test(test_chain_assertions);
}

void test_pointers_assertions(CFTEST)
{
    assert_null(NULL);
    assert_null(0);
    int a = 3, b = 3;
    int *p = &a;
    int *q = &b;
    int *r = &b;
    assert_not_null(p);
    assert_not_null(&p);

    assert_pointer_equal(q, r);
    assert_pointer_not_equal(p, q);
    assert_pointer_not_equal(p, r);
}

void test_bool_assertions(CFTEST)
{
    assert_true(true);
    assert_true(1);
    assert_true(2);
    assert_true(-6);

    assert_false(0);
    assert_false(false);
}

void test_int_assertions(CFTEST)
{
    cf_test(test_int_equal);
    cf_test(test_int_compare);
}

void test_int_equal(CFTEST)
{
    assert_zero(2 - 2);
    assert_non_zero(2 - 3);
    assert_int_equal(2 + 4, 6);
    assert_int_not_equal(2 + 4, 5);
}

void test_int_compare(CFTEST)
{
    assert_int_ge(3, 2);
    assert_int_ge(1, 1);
    assert_int_le(2, 3);
    assert_int_le(1, 1);
    assert_int_greater(3, -2);
    assert_int_less(-2, 3);
}

void test_char_assertions(CFTEST)
{
    char a = 'a', b = 'b';
    assert_char_equal(a, a);
    assert_char_equal(b, b);
    assert_char_not_equal(a, b);
    assert_char_not_equal(b, a);
}

void test_byte_assertions(CFTEST)
{
    unsigned char a = 12, b = 34;
    assert_char_equal(a, a);
    assert_char_equal(b, b);
    assert_char_not_equal(a, b);
    assert_char_not_equal(b, a);
}

void test_string_assertions(CFTEST)
{
    assert_string_equal("blah", "blah");
    assert_string_equal("blah" + 1, "lah");
    assert_string_equal("blah", "blah\0");

    assert_string_not_equal("blah", "bleh");
    assert_string_not_equal("blah", "lah");
    assert_string_not_equal("blah", "bla");
}

bool is_five(int n)
{
    return n == 5;
}

void test_chain_assertions(CFTEST)
{
    assert_chain(is_five, 5);
    assert_chain_not(is_five, 4);
}
