#include <stdio.h>
#include "children.h"

struct cfScope *get_parent(struct cfScope *s, unsigned int depth)
{
    struct cfScope *p = s;
    for (; p && p->parent && depth; p = p->parent, --depth)
        ;
    return p;
}

int get_child_index(struct cfScope *s)
{
    if (s->parent == NULL)
        return -1;
    for (unsigned int i = 0; i < CF_MAX_CHILDREN - 1; ++i)
    {
        if (s->parent->children[i] == s)
            return i;
    }
    return -1;
}

bool is_last_child(struct cfScope *s)
{
    int index = get_child_index(s);
    if (index == -1)
    {
        fprintf(stderr, "ERROR: Cannot find parent index of node '%s' at %p.\nWARNING: This will probably cause a segmentation fault.\n", s->name, (void *)s);
        return false;
    }
    return s->parent->children[index + 1] == NULL;
}

bool has_children_with_errors(struct cfScope *scope)
{
    return (count_children_failed(scope) != 0);
}

unsigned int count_children(struct cfScope *scope)
{
    unsigned int c = 0;
    for (unsigned int i = 0; i < CF_MAX_CHILDREN; ++i)
    {
        if (scope->children[i] != NULL)
            ++c;
    }
    return c;
}

unsigned int count_children_passed(struct cfScope *scope)
{
    unsigned int c = 0;
    for (unsigned int i = 0; i < CF_MAX_CHILDREN; ++i)
    {
        if (scope->children[i] != NULL && scope->children[i]->assertions.failed == 0)
            ++c;
    }
    return c;
}

unsigned int count_children_failed(struct cfScope *scope)
{
    unsigned int c = 0;
    for (unsigned int i = 0; i < CF_MAX_CHILDREN; ++i)
    {
        if (scope->children[i] != NULL && scope->children[i]->assertions.failed)
            ++c;
    }
    return c;
}

unsigned int count_assertions_passed(struct cfScope *scope)
{
    unsigned int sum = 0;
    for (unsigned int i = 0; i < CF_MAX_CHILDREN; ++i)
    {
        if (scope->children[i] != NULL)
        {
            sum += scope->children[i]->assertions.passed;
            if (count_children(scope->children[i]))
                sum += count_assertions_passed(scope->children[i]);
        }
    }
    return sum;
}

unsigned int count_assertions_failed(struct cfScope *scope)
{
    unsigned int sum = 0;
    for (unsigned int i = 0; i < CF_MAX_CHILDREN; ++i)
    {
        if (scope->children[i] != NULL)
        {
            sum += scope->children[i]->assertions.failed;
            if (count_children(scope->children[i]))
                sum += count_assertions_failed(scope->children[i]);
        }
    }
    return sum;
}
