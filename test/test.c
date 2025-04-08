#include <stdio.h>
#include <confer.h>
#include "test_assertions.c"

void test_return_value(CFTEST);

int main(void)
{
    cf_init();
    cf_test(test_assertions);
    cf_test(test_return_value);
    cf_print_call_tree();
    cf_print_results();
    return 0;
}

void test_return_value(CFTEST)
{
    if (assert_true(true))
    {
        assert_null(NULL); // ok, great
    }
    /* Works well, but commented because it outputs a failed assertion
    (as expected)

    if (!assertFalse(true)) {
        assertNull(NULL);
    } */
}
