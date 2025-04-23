#ifndef CF_NODES_CHILDREN_H
#define CF_NODES_CHILDREN_H 1

#define CF_MAX_DEPTH 999

#include <stdbool.h>
#include "build.h"
bool is_last_child(struct cfScope *s);
int get_child_index(struct cfScope *s);
struct cfScope *get_parent(struct cfScope *s, unsigned int depth);

bool has_children_with_errors(struct cfScope *scope);
unsigned int count_children(struct cfScope *scope);
unsigned int count_children_passed(struct cfScope *scope);
unsigned int count_children_failed(struct cfScope *scope);

unsigned int count_assertions_passed(struct cfScope *scope);
unsigned int count_assertions_failed(struct cfScope *scope);

#endif
