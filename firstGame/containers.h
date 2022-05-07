/*
 * containers.h
 *
 *  Created on: May 6, 2022
 *      Author: Никита
 */

#ifndef CONTAINERS_H_
#define CONTAINERS_H_

struct animation{
	int angle;
	int timer[10];
	SDL_Point center;
	SDL_Rect animationRect;
};

struct item{
	int ID;
	struct animation animation;
	int recharge;
	SDL_Rect rectangle;
	SDL_Texture *texture;
};

struct object{
	int HP;
	int DMG;
	int LVL;
	int ID;
	int direction;
	int restofway;
	int takendamage;
	int attackrecharge;
	struct item weapon;
	struct animation animation;
	SDL_Rect damageEffectRect;
	SDL_Texture *damageEffectTexture;
	SDL_Rect rectangle;
	SDL_Texture *texture, *death;
};

typedef struct element{
	struct object data;
    struct element *next, *previous, *head, *tail;
}container;

container *newcontainer(){
    container *newcontainer = malloc(sizeof(container));
    newcontainer->next = NULL;
    newcontainer->head = NULL;
    newcontainer->tail = NULL;
    newcontainer->previous = NULL;
    return newcontainer;
}

//checking if the container is empty
int is_empty(container **headcontainer){
    container *extelement = *headcontainer;
    if(extelement->head == NULL){
        return 0;
    }
    else{
        return 1;
    }
}

//counting container elements
int element_count(container **headcontainer){
    container *extelement = newcontainer();
    extelement = *headcontainer;
    int counter = 0;
    if(is_empty(&extelement) == 0){
        return 0;
    }
    else{
        while (extelement != NULL){
            counter++;
            extelement = extelement->next;
        }
        return counter;
    }
}


//stack

//function to add a new element to the stack
void addtostack(container **headstack, struct object data){
    container *extelement = newcontainer();
    container *addelement = newcontainer();
    extelement = *headstack;
    if(element_count(&extelement) == 0){
        addelement->data = data;
        addelement->head = addelement;
        addelement->tail = addelement;
        extelement = addelement;
    }
    else{
        addelement->data = data;
        addelement->head = addelement;
        addelement->next = extelement;
        addelement->tail = extelement->tail;
        extelement->previous = addelement;
        while (extelement != NULL){
            extelement->head = addelement;
            extelement = extelement->next;
        }
        extelement = addelement;
    }
    *headstack = extelement;
}

//function to pop an element from the stack
struct object getstack(container **headstack){
    container *extstack = *headstack;
    struct object getvalue = extstack->data;
    if (element_count(&extstack) == 1){
        extstack->next = NULL;
        extstack->head = NULL;
        extstack->tail = NULL;
        extstack->previous = NULL;
    } else if (element_count(&extstack) > 1){
        extstack = extstack->next;
        extstack->head = extstack;
        extstack->previous = NULL;
        while (extstack->next != NULL){
            extstack = extstack->next;
            extstack->head = extstack->previous->head;
        }
        extstack = extstack->head;
        *headstack = extstack;
    }
    return getvalue;
}


//queue

//function to add a new element to the queue
void addtoqueue(container **headqueue, struct object data){
    container *extelement = newcontainer();
    container *addelement = newcontainer();
    extelement = *headqueue;
    if(element_count(&extelement) == 0){
        addelement->data = data;
        addelement->head = addelement;
        addelement->tail = addelement;
        extelement = addelement;
    }
    else{
        addelement->data = data;
        addelement->head = addelement;
        addelement->next = extelement;
        addelement->tail = extelement->tail;
        extelement->previous = addelement;
        while (extelement != NULL){
            extelement->head = addelement;
            extelement = extelement->next;
        }
        extelement = addelement;
    }
    *headqueue = extelement;
}

//function to pop an element from the queue
struct object getqueue(container **headqueue){
    container *extqueue = *headqueue;
    struct object getdata;
    if (element_count(&extqueue) == 1){
        getdata = extqueue->data;
        extqueue->next = NULL;
        extqueue->head = NULL;
        extqueue->tail = NULL;
        extqueue->previous = NULL;
    } else if (element_count(&extqueue) > 1){
        getdata = extqueue->tail->data;
        extqueue = extqueue->tail->previous;
        extqueue->tail = extqueue;
        extqueue->next = NULL;
        while (extqueue->previous != NULL){
            extqueue = extqueue->previous;
            extqueue->tail = extqueue->next->tail;
        }
        extqueue = extqueue->head;
        *headqueue = extqueue;
    }
    return getdata;
}


//list

//function to add a new element to the beginning of the list
void addfirst(container **headlist, struct object data){
    container *extelement = *headlist;
    container *addelement = newcontainer();
    addelement->data = data;
    addelement->next = extelement;
    addelement->head = addelement;
    extelement->previous = addelement;
    while (extelement != NULL){
        extelement->head = addelement;
        extelement = extelement->next;
    }
    *headlist = addelement;
}

//function to add a new element to the end of the list
void addlast(container **headlist, struct object data){
    container *extelement = *headlist;
    container *addelement = newcontainer();
    addelement->data = data;
    addelement->head = extelement->head;
    while(extelement->next != NULL){
        extelement = extelement->next;
    }
    extelement->next = addelement;
    addelement->previous = extelement;
    extelement = extelement->head;
    *headlist = extelement;
}

//function to add a new element after the specified number
void addtolist(container **headlist, struct object data, int number){
    container *extelement = newcontainer();
    container *addelement = newcontainer();
    extelement = *headlist;
    if(element_count(&extelement) == 0){
        addelement->data = data;
        addelement->head = addelement;
        extelement = addelement;
    }
    else if(number == -1){
        addfirst(&extelement, data);
    }
    else if(number == element_count(&extelement) - 1){
        addlast(&extelement, data);
    }
    else{
        int counter = 0;
        while(extelement->next != NULL){
            if (counter == number){
                addelement->data = data;
                addelement->head = extelement->head;
                addelement->previous = extelement;
                addelement->next = extelement->next;
                extelement->next->previous = addelement;
                extelement->next = addelement;
            }
            counter++;
            extelement = extelement->next;
        }
        extelement = extelement->head;
    }
    *headlist = extelement;
}

//function to remove a new element to the beginning of the list
void delfirst(container **headlist){
    container *extelement = *headlist;
    extelement = extelement->next;
    extelement->head = extelement;
    extelement->previous = NULL;
    while (extelement->next != NULL){
        extelement = extelement->next;
        extelement->head = extelement->previous->head;
    }
    extelement = extelement->head;
    *headlist = extelement;
}

//function to remove a new element to the end of the list
void dellast(container **headlist){
    container *extelement = *headlist;
    while (extelement->next != NULL) {
        extelement = extelement->next;
    }
    extelement->previous->next = NULL;
    extelement = extelement->head;
    *headlist = extelement;
}

//function to remove the specified element
void delelement(container **headlist, int number){
    container *extelement = newcontainer();
    extelement = *headlist;
    int counter = 0;
    if(number == 0){
        delfirst(&extelement);
    }
    else if(number == element_count(&extelement) - 1){
        dellast(&extelement);
    }
    else {
        while (extelement->next != NULL) {
            if (counter == number) {
                extelement->previous->next = extelement->next;
                extelement->next->previous = extelement->previous;
            }
            counter++;
            extelement = extelement->next;
        }
    }
    extelement = extelement->head;
    *headlist = extelement;
}

//function to get the value of the specified element
struct object getlistdata(container **headlist, int number){
    container *pointer = *headlist;
    container *getlist = newcontainer();
    int counter = 0;
    if(element_count(&pointer) - 1 != number) {
        while (pointer != NULL) {
            if (counter == number) {
                getlist->data = pointer->data;
            }
            counter++;
            pointer = pointer->next;
        }
    }
    else if(element_count(&pointer) - 1 == number){
        while (pointer->next != NULL) {
            pointer = pointer->next;
        }
        getlist->data = pointer->data;
    }
    pointer = NULL;
    return getlist->data;
}

//function to get the address of the specified element
container *getlist(container **headlist, int number){
    container *extlist = *headlist;
    int counter = 0;
    while (extlist != NULL){
        if(number == counter){
            return extlist;
        }
        counter++;
        extlist = extlist->next;
    }
    return extlist;
}


#endif /* CONTAINERS_H_ */
