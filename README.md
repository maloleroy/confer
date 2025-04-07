Confer
======

Confer is a C and C++ unit testing library written in C.

## Features

Confer comes with a number of tools and feaures out of the box.
  -  20+ built-in assertions for most common types
  -  Custom assertions
  -  Fast build (...)
  -  Extra-light library written in C, no dynamic memory allocation (hence no memory leaks)
  -  A handy tool to manage projects and run tests (not compulsory)

## Installation

The easiest way to install confer is with the install script:
```bash
bash <(curl -sL https://url.viarezo.fr/cf)
```

## Preview

Create a project with `cf create my_project`. Now let's look at the example code:

`src/my_project.c` contains a simple code using a function `add` declared in `include/add.h`
```c
#include <stdio.h>
#include <add.h>

int main(void) {
    printf("Hello world!\n1 + 2 = %d\n", add(1, 2));
    return 0;
}
```

To build the executable and run it, run `cf run`
```
$ cf run
🔨 src/add.c -> obj/add.o
⚙ src/my_project.c obj/add.o -> bin/my_project
Hello world!
1 + 2 = 3
```

> Here is the declaration of `add` in `include/add.h`:
> ```c
> int add(int a, int b);
> ```

This function is defined in `src/add.c`
```c
#include <add.h>

int add(int a, int b) {
    return a + b;
}
```

Now, we're getting to the interesting part: **the tests!** The `add` function is tested in `test/test.c`
```c
#include <confer.h>
#include <add.h>

void test_add(CFTEST) {
    assertIntEqual(add(1, 2), 3);
}

int main(void) {
    cfInit();

    cfTest(test_add);

    cfPrintCallTree();
    return cfReturnCode();
}
```

Here, after calling the initialization function `cfInit`, the main function calls the subtest `test_add`, which has one assertion on the `add` function. The code ends by displaying the results, and returns an error exit code if some tests failed.

To run the tests, run `cf test`
```
🔨 src/add.c -> obj/add.o
✓ main
└── ✓ test_add (1 ✓)
```

You can nest subtests indefinitely, they will be displayed in a tree-like structure at the end of execution.

## What next?

To know more about the library, we also recommend you visiting [Confer's official documentation on GitHub](https://maloleroy.github.io/confer/)!

## Where can I get help?

Feel free to open issues on the [Github Repo](https://github.com/maloleroy/confer), especially if
you did not find an answer to a question in our documentation.