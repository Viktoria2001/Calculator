/*
 * stack.c
 *
 *  Created on: 16 июн. 2022 г.
 *      Author: Home
 */

#include "structs.h"
#include <stdio.h>
#include <stdlib.h>

void init_stack (stack *s)
{
	s->head = NULL;
}
void push (stack *s, double number)
{
	node * tmp = malloc (sizeof (node));
	tmp->x = number;
	tmp->next = s->head;
	s->head = tmp;
}
double pop (stack *s)
{
	node *tmp;
	tmp = malloc (sizeof (node));
	tmp = s->head;
	s->head = s->head->next;
	return tmp->x;
}
