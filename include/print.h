#ifndef NODES_PRINT_H
#define NODES_PRINT_H 1

#include "build.h"

#define cf_print_call_tree() print_tree(&node_main);
#define cf_print_results() _cf_print_results(self)
#define cf_return_code() _cf_return_code(&node_main)

void print_tree(struct cfScope *root);
void print_scope(struct cfScope *s, const int depth);
int _cf_print_results(struct cfScope *root);
void _cf_print_assertion_fail(const char *file, const char *assertionType, const unsigned int line, const struct cfScope *scope);
int _cf_return_code(struct cfScope *root);

#endif
