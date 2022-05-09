
#include "containers.h"


container *newcontainer(){
	extraContainer2 = malloc(sizeof(container));
	extraContainer2->next = NULL;
	extraContainer2->head = NULL;
	extraContainer2->tail = NULL;
	extraContainer2->previous = NULL;
    return extraContainer2;
}

//checking if the container is empty
int is_empty(container **headcontainer){
	extraContainer2 = *headcontainer;
    if(extraContainer2->head == NULL){
        return 0;
    }
    else{
        return 1;
    }
}

//counting container elements
int element_count(container **headcontainer){
	extraContainer2 = *headcontainer;
	counter3 = 0;
    if(is_empty(&extraContainer2) == 0){
        return 0;
    }
    else{
        while (extraContainer2 != NULL){
        	counter3++;
        	extraContainer2 = extraContainer2->next;
        }
        return counter3;
    }
}


//stack

//function to add a new element to the stack
void addtostack(container **headstack, object data){
	addElement = newcontainer();
    extraContainer2 = *headstack;
    if(element_count(&extraContainer2) == 0){
    	addElement->data = data;
    	addElement->head = addElement;
    	addElement->tail = addElement;
        extraContainer2 = addElement;
    }
    else{
    	addElement->data = data;
    	addElement->head = addElement;
    	addElement->next = extraContainer2;
    	addElement->tail = extraContainer2->tail;
        extraContainer2->previous = addElement;
        while (extraContainer2 != NULL){
        	extraContainer2->head = addElement;
        	extraContainer2 = extraContainer2->next;
        }
        extraContainer2 = addElement;
    }
    *headstack = extraContainer2;
}

//function to pop an element from the stack
object getstack(container **headstack){
	extraContainer2 = *headstack;
	extraObject2 = extraContainer2->data;
    if (element_count(&extraContainer2) == 1){
    	extraContainer2->next = NULL;
    	extraContainer2->head = NULL;
    	extraContainer2->tail = NULL;
    	extraContainer2->previous = NULL;
    } else if (element_count(&extraContainer2) > 1){
    	extraContainer2 = extraContainer2->next;
    	extraContainer2->head = extraContainer2;
    	extraContainer2->previous = NULL;
        while (extraContainer2->next != NULL){
        	extraContainer2 = extraContainer2->next;
        	extraContainer2->head = extraContainer2->previous->head;
        }
        extraContainer2 = extraContainer2->head;
        *headstack = extraContainer2;
    }
    return extraObject2;
}


//queue

//function to add a new element to the queue
void addtoqueue(container **headqueue, object data){
	addElement = newcontainer();
    extraContainer2 = *headqueue;
    if(element_count(&extraContainer2) == 0){
    	addElement->data = data;
    	addElement->head = addElement;
    	addElement->tail = addElement;
        extraContainer2 = addElement;
    }
    else{
    	addElement->data = data;
    	addElement->head = addElement;
    	addElement->next = extraContainer2;
    	addElement->tail = extraContainer2->tail;
        extraContainer2->previous = addElement;
        while (extraContainer2 != NULL){
        	extraContainer2->head = addElement;
        	extraContainer2 = extraContainer2->next;
        }
        extraContainer2 = addElement;
    }
    *headqueue = extraContainer2;
}

//function to pop an element from the queue
object getqueue(container **headqueue){
    extraContainer2 = *headqueue;
    if (element_count(&extraContainer2) == 1){
        extraObject2 = extraContainer2->data;
        extraContainer2->next = NULL;
        extraContainer2->head = NULL;
        extraContainer2->tail = NULL;
        extraContainer2->previous = NULL;
    } else if (element_count(&extraContainer2) > 1){
    	extraObject2 = extraContainer2->tail->data;
        extraContainer2 = extraContainer2->tail->previous;
        extraContainer2->tail = extraContainer2;
        extraContainer2->next = NULL;
        while (extraContainer2->previous != NULL){
        	extraContainer2 = extraContainer2->previous;
        	extraContainer2->tail = extraContainer2->next->tail;
        }
        extraContainer2 = extraContainer2->head;
        *headqueue = extraContainer2;
    }
    return extraObject2;
}


//list

//function to add a new element to the beginning of the list
void addfirst(container **headlist, object data){
    extraContainer2 = *headlist;
    addElement = newcontainer();
    addElement->data = data;
    addElement->next = extraContainer2;
    addElement->head = addElement;
    extraContainer2->previous = addElement;
    while (extraContainer2 != NULL){
    	extraContainer2->head = addElement;
    	extraContainer2 = extraContainer2->next;
    }
    *headlist = addElement;
}

//function to add a new element to the end of the list
void addlast(container **headlist, object data){
    extraContainer3 = *headlist;
    addElement = newcontainer();
    addElement->data = data;
    addElement->head = extraContainer3->head;
    while(extraContainer3->next != NULL){
    	extraContainer3 = extraContainer3->next;
    }
    extraContainer3->next = addElement;
    addElement->previous = extraContainer3;
    extraContainer3 = extraContainer3->head;
    *headlist = extraContainer3;
}

//function to add a new element after the specified number
void addtolist(container **headlist, object data, int number){
    addElement = newcontainer();
    extraContainer2 = *headlist;
    if(element_count(&extraContainer2) == 0){
    	addElement->data = data;
    	addElement->head = addElement;
        extraContainer2 = addElement;
    }
    else if(number == -1){
        addfirst(&extraContainer2, data);
    }
    else if(number == element_count(&extraContainer2) - 1){
        addlast(&extraContainer2, data);
    }
    else{
    	counter2 = 0;
        while(extraContainer2->next != NULL){
            if (counter2 == number){
            	addElement->data = data;
            	addElement->head = extraContainer2->head;
            	addElement->previous = extraContainer2;
            	addElement->next = extraContainer2->next;
                extraContainer2->next->previous = addElement;
                extraContainer2->next = addElement;
            }
            counter2++;
            extraContainer2 = extraContainer2->next;
        }
        extraContainer2 = extraContainer2->head;
    }
    *headlist = extraContainer2;
}

//function to remove a new element to the beginning of the list
void delfirst(container **headlist){
    extraContainer2 = *headlist;
    extraContainer2 = extraContainer2->next;
    free(extraContainer2->previous);
    extraContainer2->head = extraContainer2;
    extraContainer2->previous = NULL;
    while (extraContainer2->next != NULL){
    	extraContainer2 = extraContainer2->next;
    	extraContainer2->head = extraContainer2->previous->head;
    }
    extraContainer2 = extraContainer2->head;
    *headlist = extraContainer2;
}

//function to remove a new element to the end of the list
void dellast(container **headlist){
	extraContainer2 = *headlist;
    while (extraContainer2->next->next != NULL) {
    	extraContainer2 = extraContainer2->next;
    }
    free(extraContainer2->next);
    extraContainer2->next = NULL;
    extraContainer2 = extraContainer2->head;
    *headlist = extraContainer2;
}

//function to remove the specified element
void delelement(container **headlist, int number){
	extraContainer3 = *headlist;
    struct element *extpointer;
    counter2 = 0;
    if(number == 0){
        delfirst(&extraContainer3);
    }
    else if(number == element_count(&extraContainer3) - 1){
        dellast(&extraContainer3);
    }
    else {
        while (extraContainer3->next != NULL) {
            if (counter2 == number) {
            	extpointer = extraContainer3;
            	extraContainer3->previous->next = extraContainer3->next;
            	extraContainer3->next->previous = extraContainer3->previous;
            	counter2++;
                extraContainer3 = extraContainer3->next;
                free(extpointer);

            }
            else{
            	counter2++;
            	extraContainer3 = extraContainer3->next;
            }
        }
    }
    extraContainer3 = extraContainer3->head;
    *headlist = extraContainer3;
}


//function to get the address of the specified element
container *getlist(container **headlist, int number){
	extraContainer2 = *headlist;
    counter = 0;
    while (extraContainer2 != NULL){
        if(number == counter){
            return extraContainer2;
        }
        counter++;
        extraContainer2 = extraContainer2->next;
    }
    return extraContainer2;
}
