/*
 * queue.c
 *
 *  Created on: 16 июн. 2022 г.
 *      Author: Home
 */

#include "structs.h"
#include <stdio.h>
#include <stdlib.h>

void initqueue (queue *q)
{
	q->head = NULL;
	q->tail = NULL;
}

void enqueue (queue *q, element *data)
{
	element* tmp = malloc (sizeof(element));
	tmp->c = data->c;
	tmp->x = data->x;
	tmp->y = data->y;
	tmp->regime = data->regime;
	tmp->res = data->res;
	tmp->size = data->size;
	tmp->next = NULL;
	tmp->result = data->result;
	if (q->tail != NULL)
	{
		q->tail->next = tmp;
	}
	q->tail = tmp;
	if (q->head == NULL)
	{
		q->head = tmp;
	}
}

element* dequeue (queue *q)
{
	element *out;
	out = malloc (sizeof (element));
	if (q->head == NULL)
	{
		out = NULL;
		return out;
	}
	element *tmp = q->head;
	out->c = tmp->c;
	out->res = tmp->res;
	out->result = tmp->result;
	out->x = tmp->x;
	out->y = tmp->y;
	out->size = tmp->size;
	out->regime = tmp->regime;
	q->head = q->head->next;
	if (q->head == NULL)
	{
		q->tail = NULL;
	}
	free (tmp);
	return out;
}
