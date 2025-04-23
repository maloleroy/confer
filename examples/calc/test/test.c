#include <confer.h>
#include <operations.h>

void test_operations(CFTEST);
void test_plus(CFTEST);

int main(void) {
    cf_init();
    cf_test(test_operations);
    cf_print_call_tree();
    return 0;
}

void test_operations(CFTEST) { cf_test(test_plus); }

void test_plus(CFTEST) {
    assert_int_equal(plus(1, 2), 3);
    assert_int_not_equal(plus(1, -2), 0);
}
