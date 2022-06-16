/*
 * list.c
 *
 *  Created on: 16 июн. 2022 г.
 *      Author: Home
 */
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>

void initList (list *l)
{
	l->head = NULL;
	l->current = NULL;
}

void pushlist (list *l, element *data)
{
	element* tmp = malloc (sizeof(element));
	element *last = l->head;
	tmp->c = data->c;
	tmp->x = data->x;
	tmp->y = data->y;
	tmp->regime = data->regime;
	tmp->res = data->res;
	tmp->size = data->size;
	tmp->next = NULL;
	tmp->result = data->result;
	if (l->head==NULL)
	{
		l->head = tmp;
		return;
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = tmp;
	return;
}

void delete (list *l)
{
	element *tmp;
	if (&l->head == NULL) return;
	tmp = l->head;
	l->head = l->head->next;
	free (tmp);
}

element* next (list *l)
{
	l->current = l->current->next;
	return l->current;
}
