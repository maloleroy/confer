Confer
======

Confer is a C and C++ unit testing library written in C. It is currently only available on Linux, and limited to GCC.

## Features

Confer comes with a number of tools and feaures out of the box.
  -  20+ built-in assertions for most common types
  -  Custom assertions
  -  Fast build (the example compiles and runs in ~100 ms)
  -  Lightning-fast runs (the example runs in 637 µs on a 7th-gen i5 processor !)
  -  Extra-light library written in C, no dynamic memory allocation (hence no memory leaks)
  -  A handy tool to manage projects and run tests (not compulsory)

## Preview

To start using Confer, simply <place installation instructions here>, and include it in your test file:

```c
#include <confer.h>
```

Then, after calling the initialization function, you will be able to write your first tests:

```c
void main(void) {
  cf_init(); // nothing more needed
  cf_test(test_my_function); // call subtests
  cf_print_call_tree(); // show the results
}

void test_my_function(CFTEST) { // make it a test
  assert_int_equal(my_function(0), 1);
  assert_int_greater(my_function(2), 7);
}
```

## What next?

To know more about the library, we also recommend you visiting Confer's [documentation](https://github.com/maloleroy/confer/tree/main/docs). For a fast overview of Confer's capacity, you can also check the [example](https://github.com/maloleroy/confer/tree/main/examples/calc).

## Where can I get help?

Feel free to open issues on the [Github Repo](https://github.com/maloleroy/confer), especially if
you did not find an answer to a question in our documentation.
