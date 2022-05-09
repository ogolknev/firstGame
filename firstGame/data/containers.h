
#ifndef CONTAINERS_H_
#define CONTAINERS_H_
#include "types.h"


container *objects;
container *extraContainer;
container *extraContainer2, *extraContainer3, *addElement;
object extraObject2;
int counter, counter2, counter3;


container *newcontainer();

//checking if the container is empty
int is_empty(container **headcontainer);

//counting container elements
int element_count(container **headcontainer);

//stack

//function to add a new element to the stack
void addtostack(container **headstack, object data);

//function to pop an element from the stack
object getstack(container **headstack);


//queue

//function to add a new element to the queue
void addtoqueue(container **headqueue, object data);

//function to pop an element from the queue
object getqueue(container **headqueue);


//list

//function to add a new element to the beginning of the list
void addfirst(container **headlist, object data);

//function to add a new element to the end of the list
void addlast(container **headlist, object data);

//function to add a new element after the specified number
void addtolist(container **headlist, object data, int number);

//function to remove a new element to the beginning of the list
void delfirst(container **headlist);

//function to remove a new element to the end of the list
void dellast(container **headlist);

//function to remove the specified element
void delelement(container **headlist, int number);


//function to get the address of the specified element
container *getlist(container **headlist, int number);

#endif /* CONTAINERS_H_ */
