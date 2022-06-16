/*
 * list.h
 *
 *  Created on: 16 июн. 2022 г.
 *      Author: Home
 */
#include "structs.h"
#ifndef LIST_H_
#define LIST_H_

void initList (list *l);

void pushlist (list *l, element *data);

void delete (list *l);

element* next (list *l);

#endif /* LIST_H_ */
