/*
 * structs.h
 *
 *  Created on: 16 июн. 2022 г.
 *      Author: Home
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_

typedef struct element
{
	char c;
	char regime;
	double result;
	double *x,*y;
	double *res;
	int size;
	struct element *next;
} element;

typedef struct queue
{
	element *head;
	element *tail;
} queue;

typedef struct node
{
	double x;
	struct node *next;
} node;
typedef struct stack
{
	node *head;
} stack;

typedef struct list
{
	element *head;
	element *current;
} list;


#endif /* STRUCTS_H_ */
