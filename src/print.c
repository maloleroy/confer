#include <stdio.h>
#include <string.h>
#include "print.h"
#include "children.h"

#ifndef __unix__
/* Windows' CMD does not support UTF-8 and ASCII special sequences */
#define CF_USE_ASCII
#endif

#ifdef CF_USE_ASCII
static const char *hbar = "-", *vbar = "|", *branch = "|", *angle = "`",
                  *checkMark = "OK", *notCheckMark = "X",
                  *passed = "passed", *failed = "failed", *bold = "",
                  *end = "";
#else
static const char *hbar = "─", *vbar = "│", *branch = "├", *angle = "└",
                  *checkMark = "\033[32m✓\033[0m",
                  *notCheckMark = "\033[31m✗\033[0m", // ✘
                      *passed = "\033[32m✓\033[0m",
                  *failed = "\033[31m✗\033[0m", *bold = "\033[1m",
                  *end = "\033[0m";
#endif
static const char *nbsp = " ";
unsigned int TAB_SIZE = 4;

static void print_padding(const char *head, const char *body);
static char *get_padding_head(struct cfScope *s, const unsigned int depth);
static char *get_padding_body(const unsigned int depth);
static char *get_scope_head(struct cfScope *s);
static void _cf_print_scope_assertions(struct cfScope *s);

void _cf_print_assertion_fail(const char *file, const char *assertionType, const unsigned int line, const struct cfScope *scope)
{
    printf("%s%s:%u%s: in function %s: %s", bold, file, line, end, scope->name, assertionType + 1);
}

int _cf_return_code(struct cfScope *root)
{
    if (count_assertions_failed(root) == 0)
    {
        return 0;
    }
    return 1;
}

int _cf_print_results(struct cfScope *root)
{
    puts("\nTotal:");
    unsigned int passed = count_assertions_passed(root);
    unsigned int failed = count_assertions_failed(root);
    if (passed)
        printf("%s %u passed main blocks\n%s %u passed assertions\n", checkMark,
               count_children_passed(root), checkMark, passed);
    if (failed)
        printf("%s %u failed main blocks\n%s %u failed assertions\n", notCheckMark,
            count_children_passed(root), notCheckMark, failed);
    if (!failed && !passed)
        fprintf(stderr, "WARNING: scope '%s' has no failed or passed blocks\n",
                root->name);
    return 0;
}

void print_tree(struct cfScope *s)
{
    if (s->parent != NULL)
        fprintf(stderr, "WARNING: node '%s' at %p has a parent '%s' at %p\n",
                s->name, (void *)s, s->parent->name, (void *)s->parent);
    print_scope(s, 0);
}

void print_scope(struct cfScope *s, const int depth)
{
    if (s == NULL)
        return;
    for (unsigned int i = depth; i; --i)
    {
        print_padding(get_padding_head(s, i), get_padding_body(i));
        putc(' ', stdout);
    }
    printf("%s %s", get_scope_head(s), s->name);
    _cf_print_scope_assertions(s);
    for (int i = 0; i < CF_MAX_CHILDREN; ++i)
    {
        print_scope(s->children[i], depth + 1);
    }
}

static void _cf_print_scope_assertions(struct cfScope *s)
{
    if (!s->assertions.passed && !s->assertions.failed)
    {
        putc('\n', stdout);
        return;
    }
    fputs(" (", stdout);
    if (s->assertions.passed && !s->assertions.failed)
        printf("%u %s", s->assertions.passed, passed);
    else if (!s->assertions.passed && s->assertions.failed)
        printf("%u %s", s->assertions.failed, failed);
    else
        printf("%u %s and %u %s", s->assertions.passed, passed, s->assertions.failed, failed);
    puts(")");
}

static void print_padding(const char *head, const char *body)
{
    fputs(head, stdout);
    for (unsigned int i = 0; i < TAB_SIZE - 2; ++i)
    {
        fputs(body, stdout);
    }
}

static char *get_scope_head(struct cfScope *s)
{
    static char head[13];
    if (s->assertions.failed || has_children_with_errors(s))
        strcpy(head, notCheckMark);
    else
        strcpy(head, checkMark);
    return head;
}

static char *get_padding_head(struct cfScope *s, const unsigned int depth)
{
    static char head[4];
    if (is_last_child(get_parent(s, depth - 1)))
    {
        if (depth == 1)
            strcpy(head, angle);
        else
            strcpy(head, nbsp);
    }
    else
    {
        if (depth == 1)
            strcpy(head, branch);
        else
            strcpy(head, vbar);
    }
    return head;
}

static char *get_padding_body(const unsigned int depth)
{
    static char body[4];
    if (depth == 1)
        strcpy(body, hbar);
    else
        strcpy(body, nbsp);
    return body;
}
