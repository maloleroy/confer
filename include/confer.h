#ifndef CONFER_H
#define CONFER_H

#include "assertions.h"
#include "build.h"
#include "print.h"

#define cfInit init_root_scope

#define CFTEST struct cfScope *self
#define cfTest(f)                   \
    static struct cfScope node_##f; \
    init_scope(node_##f);            \
    _cf_add_child(self, &node_##f);   \
    f(&node_##f)

#endif
