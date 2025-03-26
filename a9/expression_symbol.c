
#include "expression_symbol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Helper: Check operator precedence
static int precedence(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default: return 0;
    }
}

// Convert symbolic infix to postfix
QUEUE infix_to_postfix_symbol(HASHTABLE *ht, char *infixstr) {
    QUEUE output = {0};
    STACK operators = {0};
    char token[32];
    int pos = 0, len = strlen(infixstr);

    while (pos < len) {
        if (isspace(infixstr[pos])) {
            pos++; continue;
        }

        if (isalnum(infixstr[pos])) {
            int tpos = 0;
            while (isalnum(infixstr[pos]))
                token[tpos++] = infixstr[pos++];
            token[tpos] = '\0';
            enqueue(&output, token);
        } else if (infixstr[pos] == '(') {
            push(&operators, "(");
            pos++;
        } else if (infixstr[pos] == ')') {
            while (!is_stack_empty(&operators) && strcmp(peek(&operators), "(") != 0)
                enqueue(&output, pop(&operators));
            pop(&operators); // Pop '('
            pos++;
        } else { // operator
            char op[2] = {infixstr[pos], '\0'};
            while (!is_stack_empty(&operators) &&
                   precedence(*peek(&operators)) >= precedence(op[0]))
                enqueue(&output, pop(&operators));
            push(&operators, op);
            pos++;
        }
    }

    while (!is_stack_empty(&operators))
        enqueue(&output, pop(&operators));

    return output;
}

// Evaluate postfix expression
int evaluate_postfix(QUEUE queue) {
    STACK eval_stack = {0};
    char *token;
    int a, b;

    while (!is_queue_empty(&queue)) {
        token = dequeue(&queue);

        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(&eval_stack, token);
        } else {
            b = atoi(pop(&eval_stack));
            a = atoi(pop(&eval_stack));
            char res[32];

            switch (token[0]) {
                case '+': sprintf(res, "%d", a + b); break;
                case '-': sprintf(res, "%d", a - b); break;
                case '*': sprintf(res, "%d", a * b); break;
                case '/': sprintf(res, "%d", a / b); break;
            }
            push(&eval_stack, res);
        }
    }
    return atoi(pop(&eval_stack));
}

// Evaluate symbolic infix expression
int evaluate_infix_symbol(HASHTABLE *ht, char *infixstr) {
    QUEUE postfix = infix_to_postfix_symbol(ht, infixstr);

    QUEUE resolved = {0};
    char *token;
    HNODE *symbol_node;
    while (!is_queue_empty(&postfix)) {
        token = dequeue(&postfix);
        if (isalpha(token[0])) {
            symbol_node = hashtable_search(ht, token);
            if (!symbol_node) {
                printf("Symbol '%s' not found!\n", token);
                exit(1);
            }
            char num[32];
            sprintf(num, "%d", symbol_node->data.value);
            enqueue(&resolved, num);
        } else {
            enqueue(&resolved, token);
        }
    }

    return evaluate_postfix(resolved);
}

// Evaluate statement like a=(b+3)*2;
DATA evaluate_statement(HASHTABLE *ht, char* statement) {
    char var[NAME_SIZE], expr[256];
    sscanf(statement, "%[^=]=%[^;]", var, expr);

    DATA result;
    strcpy(result.name, var);
    result.value = evaluate_infix_symbol(ht, expr);

    hashtable_insert(ht, result);
    return result;
}
