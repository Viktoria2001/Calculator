/*
 * queue.h
 *
 *  Created on: 16 июн. 2022 г.
 *      Author: Home
 */
#include "structs.h"
#ifndef QUEUE_H_
#define QUEUE_H_

void initqueue (queue *q);

void enqueue (queue *q, element *data);

element* dequeue (queue *q);

#endif /* QUEUE_H_ */
