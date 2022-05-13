
#ifndef CONTAINERS_H_
#define CONTAINERS_H_
#include "types.h"
#include "variables.h"





Container *newContainer();

//checking if the container is empty
int isEmpty(Container **headcontainer);

//counting container elements
int elementCount(Container **headcontainer);

//stack

//function to add a new element to the stack
void addToStack(Container **headstack, Object data);

//function to pop an element from the stack
Object getStack(Container **headstack);


//queue

//function to add a new element to the queue
void addToQueue(Container **headqueue, Object data);

//function to pop an element from the queue
Object getQueue(Container **headqueue);


//list

//function to add a new element to the beginning of the list
void addFirst(Container **headlist, Object data);

//function to add a new element to the end of the list
void addLast(Container **headlist, Object data);

//function to add a new element after the specified number
void addToList(Container **headlist, Object data, int number);

//function to remove a new element to the beginning of the list
void delFirst(Container **headlist);

//function to remove a new element to the end of the list
void delLast(Container **headlist);

//function to remove the specified element
void delElement(Container **headlist, int number);


//function to get the address of the specified element
Container *getList(Container **headlist, int number);

#endif /* CONTAINERS_H_ */
