---
title: Assertions
---

Assertions
==========

Confer comes with more than 20 built-in assertions. You can call them from any `CFTEST` or from your `main` function. Here is an example with `assert_int_equal`:

```c
void test_plus(CFTEST) {
    assert_int_equal(2 + 3, 5);
}
```

{% info Calling subtests %}
To run tests in `test_plus`, call it with `cf_test(test_plus);` from any `CFTEST` or from your `main` function.
{% end %}

Assertions return `true` if they pass, `false` if they fail. This return value can be used in conditions to make more tests:
```c
if (assert_not_null(my_car_pointer)) {
    assert_true(is_red(*my_car_pointer));
}
```
This prevents errors like null dereferences or semgentation faults.

## Constants

```c
#define ASSERTION_PASSED true
#define ASSERTION_FAILED false
```

## Built-in assertions

### Booleans

```c
int assert_true(bool b);
```

```c
int assert_false(bool b);
```

Test that `b` is true (or false).

### Pointers

```c
int assert_null(void *p);
```

```c
int assert_not_null(void *p);
```

Test that `p` is (or is not) `NULL`.

```c
int assert_pointer_equal(const void *p1, const void *p2);
```

```c
int assert_pointer_not_equal(const void *p1, const void *p2);
```

Test that `p1` and `p2` are (or are not) equal.

### Integers

```c
int assert_zero(int x);
```

```c
int assert_non_zero(int x);
```

Test that `x` is (or is not) equal to `0`.

```c
int assert_int_equal(int x, int y);
```

```c
int assert_int_not_equal(int x, int y);
```

Test that `x` and `y` are (or are not) equal.

```c
int assert_int_ge(int x, int y);
```

Test that `x` is greater than or equal to `y` (passes if `x >= y`).

```c
int assert_int_le(int x, int y);
```

Test that `x` is less than or equal to `y` (passes if `x <= y`).

```c
int assert_int_greater(int x, int y);
```

Test that `x` is greater than `y` (passes if `x > y`).

```c
int assert_int_less(int x, int y);
```

Test that `x` is less than `y` (passes if `x < y`).

```c
int assert_int_non_negative(int x);
```

Test that `x` is non-negative; that is, greater than or equal to `0` (passes if `x >= 0`).

```c
int assert_int_non_positive(int x);
```

Test that `x` is non-positive; that is, less than or equal to `0` (passes if `x <= 0`).

```c
int assert_int_positive(int x);
```

Test that `x` is positive; that is, greater than `0` (passes if `x > 0`).

```c
int assert_int_negative(int x);
```

Test that `x` is negative; that is, less than `0` (passes if `x < 0`).

### Characters & bytes

```c
int assert_char_equal(char c1, char c2);
```

```c
int assert_char_not_equal(char c1, char c2);
```

Test that `c1` and `c2` are (or are not) equal.

```c
int assert_byte_equal(unsigned char b1, unsigned char b2);
```

```c
int assert_byte_not_equal(unsigned char b1, unsigned char b2);
```

Test that `b1` and `b2` are (or are not) equal.

### Strings

```c
int assert_string_equal(const char *s1, const char *s2);
```

Test that `s1` and `s2` are equal (passes if `strcmp(s1, s2) == 0`).

```c
int assert_string_not_equal(const char *s1, const char *s2);
```

Test that `s1` and `s2` are not equal (passes if `strcmp(s1, s2) != 0`).

## Special assertions

### Chaining assertions

Chaining assertions is used to pass parameters to an existing check function. Let's say you defined a `rational` typedef and a `is_zero` function that tells if a `rational` is zero, returning a `bool`. To test if a rational `x` is zero, we could obviously use both `assertTrue` and `is_zero`

```c
// Bad code
assert_true(is_zero(x));
```

This is a bad coding practice, because if the check fails we have no way to get back the value of x, and log it for example. Chained assertions were designed to solve this problem. To work with chained assertions we use two functions

```c
int assert_chain(f, ...)
int assert_chain_not(f, ...)
```

They apply the arguments in `...` to the function `f` that returns a `bool`, providing more insights than the previous method if the test fails. The previous code would be replaced by

```c
assert_chain(is_zero, x);
```

Chained assertions work with multiple arguments too, so checking if two `rational` numbers `x` and `y` are equal would be fairly simple using a `are_equal` function
```c
assert_chain(are_equal, x, y);
```

### Custom assertions

The great thing about chained assertions is that it enables us to define custom assertions. To learn more about custom assertions, go to the `Custom assertions` page.
