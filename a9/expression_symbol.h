// expression_symbol.h
#ifndef EXPRESSION_SYMBOL_H
#define EXPRESSION_SYMBOL_H

#include "hash.h"
#include "common_queue_stack.h"

 


QUEUE infix_to_postfix_symbol(HASHTABLE *ht, char *infixstr);
int evaluate_infix_symbol(HASHTABLE *ht, char *infixstr);
int evaluate_postfix(QUEUE queue);
DATA evaluate_statement(HASHTABLE *ht, char* statement);

#endif