
#include "containers.h"


Container *newContainer(){
	Container *new_container = malloc(sizeof(Container));
	new_container->next = NULL;
	new_container->head = NULL;
	new_container->tail = NULL;
	new_container->previous = NULL;
    return new_container;
}

//checking if the container is empty
int isEmpty(Container **headcontainer){
	Container *pointer = *headcontainer;
    if(pointer->head == NULL){
        return 0;
    }
    else{
        return 1;
    }
}

//counting container elements
int elementCount(Container **headcontainer){
	Container *pointer = *headcontainer;
	int counter = 0;
    if(isEmpty(&pointer) == 0){
        return 0;
    }
    else{
        while (pointer != NULL){
        	counter++;
        	pointer = pointer->next;
        }
        return counter;
    }
}


//stack

//function to add a new element to the stack
void addToStack(Container **headstack, Object data){
	Container *new_element = newContainer();
	Container *pointer = *headstack;
    if(elementCount(&pointer) == 0){
    	new_element->data = data;
    	new_element->head = new_element;
    	new_element->tail = new_element;
    	pointer = new_element;
    }
    else{
    	new_element->data = data;
    	new_element->head = new_element;
    	new_element->next = pointer;
    	new_element->tail = pointer->tail;
    	pointer->previous = new_element;
        while (pointer != NULL){
        	pointer->head = new_element;
        	pointer = pointer->next;
        }
        pointer = new_element;
    }
    *headstack = pointer;
}

//function to pop an element from the stack
Object getStack(Container **headstack){
	Container *pointer = *headstack;
	Object get_object = pointer->data;
    if (elementCount(&pointer) == 1){
    	pointer->next = NULL;
    	pointer->head = NULL;
    	pointer->tail = NULL;
    	pointer->previous = NULL;
    } else if (elementCount(&pointer) > 1){
    	pointer = pointer->next;
    	pointer->head = pointer;
    	pointer->previous = NULL;
        while (pointer->next != NULL){
        	pointer = pointer->next;
        	pointer->head = pointer->previous->head;
        }
        pointer = pointer->head;
        *headstack = pointer;
    }
    return get_object;
}


//queue

//function to add a new element to the queue
void addToQueue(Container **headqueue, Object data){
	Container *new_element = newContainer();
	Container *pointer = *headqueue;
    if(elementCount(&pointer) == 0){
    	new_element->data = data;
    	new_element->head = new_element;
    	new_element->tail = new_element;
    	pointer = new_element;
    }
    else{
    	new_element->data = data;
    	new_element->head = new_element;
    	new_element->next = pointer;
    	new_element->tail = pointer->tail;
    	pointer->previous = new_element;
        while (pointer != NULL){
        	pointer->head = new_element;
        	pointer = pointer->next;
        }
        pointer = new_element;
    }
    *headqueue = pointer;
}

//function to pop an element from the queue
Object getQueue(Container **headqueue){
	Container *pointer = *headqueue;
	Object get_object;
    if (elementCount(&pointer) == 1){
    	get_object = pointer->data;
        pointer->next = NULL;
        pointer->head = NULL;
        pointer->tail = NULL;
        pointer->previous = NULL;
    } else if (elementCount(&pointer) > 1){
    	get_object = pointer->tail->data;
    	pointer = pointer->tail->previous;
    	pointer->tail = pointer;
    	pointer->next = NULL;
        while (pointer->previous != NULL){
        	pointer = pointer->previous;
        	pointer->tail = pointer->next->tail;
        }
        pointer = pointer->head;
        *headqueue = pointer;
    }
    return get_object;
}


//list

//function to add a new element to the beginning of the list
void addFirst(Container **headlist, Object data){
	Container *pointer = *headlist;
	Container *new_element = newContainer();
	new_element->data = data;
	new_element->next = pointer;
	new_element->head = new_element;
    pointer->previous = new_element;
    while (pointer != NULL){
    	pointer->head = new_element;
    	pointer = pointer->next;
    }
    *headlist = new_element;
}

//function to add a new element to the end of the list
void addLast(Container **headlist, Object data){
	Container *pointer = *headlist;
	Container *new_element = newContainer();
	new_element->data = data;
	new_element->head = pointer->head;
    while(pointer->next != NULL){
    	pointer = pointer->next;
    }
    pointer->next = new_element;
    new_element->previous = pointer;
    pointer = pointer->head;
    *headlist = pointer;
}

//function to add a new element after the specified number
void addToList(Container **headlist, Object data, int number){
	Container *pointer = *headlist;
	Container *new_element = newContainer();
    if(elementCount(&pointer) == 0){
    	new_element->data = data;
    	new_element->head = new_element;
    	pointer = new_element;
    }
    else if(number == -1){
        addFirst(&pointer, data);
    }
    else if(number == elementCount(&pointer) - 1){
        addLast(&pointer, data);
    }
    else{
    	int counter = 0;
        while(pointer->next != NULL){
            if (counter == number){
            	new_element->data = data;
            	new_element->head = pointer->head;
            	new_element->previous = pointer;
            	new_element->next = pointer->next;
            	pointer->next->previous = new_element;
            	pointer->next = new_element;
            }
            counter++;
            pointer = pointer->next;
        }
        pointer = pointer->head;
    }
    *headlist = pointer;
}

//function to remove a new element to the beginning of the list
void delFirst(Container **headlist){
	Container *pointer = *headlist;
	pointer = pointer->next;
    free(pointer->previous);
    pointer->head = pointer;
    pointer->previous = NULL;
    while (pointer->next != NULL){
    	pointer = pointer->next;
    	pointer->head = pointer->previous->head;
    }
    pointer = pointer->head;
    *headlist = pointer;
}

//function to remove a new element to the end of the list
void delLast(Container **headlist){
	Container *pointer = *headlist;
    while (pointer->next->next != NULL) {
    	pointer = pointer->next;
    }
    free(pointer->next);
    pointer->next = NULL;
    pointer = pointer->head;
    *headlist = pointer;
}

//function to remove the specified element
void delElement(Container **headlist, int number){
	Container *pointer = *headlist;
    int counter = 0;
    if(number == 0){
        delFirst(&pointer);
    }
    else if(number == elementCount(&pointer) - 1){
        delLast(&pointer);
    }
    else {
        while (pointer->next != NULL) {
            if (counter == number) {
            	Container *extra_pointer = pointer;
            	pointer->previous->next = pointer->next;
            	pointer->next->previous = pointer->previous;
            	counter++;
            	pointer = pointer->next;
                free(extra_pointer);

            }
            else{
            	counter++;
            	pointer = pointer->next;
            }
        }
    }
    pointer = pointer->head;
    *headlist = pointer;
}


//function to get the address of the specified element
Container *getList(Container **headlist, int number){
	Container *pointer = *headlist;
    int counter = 0;
    while (pointer != NULL){
        if(number == counter){
            return pointer;
        }
        counter++;
        pointer = pointer->next;
    }
    return pointer;
}
