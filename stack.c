#include <stdio.h>

#include <conio.h>

#include <stdlib.h>

#include<stack.h>



void pop(struct node *top)

{

    int item;

    struct node *ptr;

    if (top == 0)

    {

        printf("\n Stack is empty");
    }

    else

    {

        item = top->item;

        ptr = top;

        printf("\n item popped is=%d", item);

        top = top->next;

        free(ptr);
    }
}

void push(struct node *top)

{

    int n;

    struct node *nw;

    nw = (struct node *)malloc(sizeof(struct node));

    printf("\n Enter item in stack:");

    scanf("%d", &n);

    nw->item = n;

    nw->next = 0;

    if (top == 0)

    {

        top = nw;
    }

    else

    {

        nw->next = top;

        top = nw;
    }
}




