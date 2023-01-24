#include <stdlib.h>
#include <stdio.h>
#define OFFSET 1
typedef struct stackitem stackitem;
typedef struct defstack defstack;
defstack *init_stack(void);
void push(defstack *stack, stackitem *item);
int pop(defstack *stack);
stackitem *create_item(defstack *stack, int value);

struct defstack
{
    stackitem *top;
    stackitem *bottom;
    int items_on_stack;
};

struct stackitem
{
    stackitem *prev;
    int value;
};

int main(void)
{
    defstack *stack = init_stack();

    printf("Value is = %d\n", stack->top->value);
    for (int i = 1; i < 10; i++)
    {   
        stackitem *newvalue = create_item(stack, i);
        push(stack, newvalue);
        printf("Value is = %d\n", stack->top->value);
    }
    printf("items on stack = %d\n", stack->items_on_stack);
    for (int i = stack->items_on_stack; i != 0; i--)
    {
        printf("Value is = %d\n", pop(stack));
    }
    printf("items on stack = %d", stack->items_on_stack);
    for (int i = 1; i < 10; i++)
    {   
        stackitem *newvalue = create_item(stack, i);
        push(stack, newvalue);
        printf("Value is = %d\n", stack->top->value);
    }
    printf("items on stack = %d\n", stack->items_on_stack);


    return 0;
}

stackitem *create_item(defstack *stack, int value)
{
    stackitem *temp = malloc(sizeof(stackitem));
    temp->prev = stack->top;
    temp->value = value;
    return temp;
}

int pop(defstack *stack)
{   
    stackitem old_top = *stack->top;
    free(stack->top);//why the fuck does it ripple and corrupt  all the adresses and values in the underlying items?
    stack->top = old_top.prev; 
    stack->items_on_stack--;
    return old_top.value;
}

void push(defstack *stack, stackitem *item)
{
    item->prev = stack->top;
    stack->top = item;
    stack->items_on_stack++;
}

defstack *init_stack(void)
{
    defstack *stack = malloc(sizeof(defstack));
    stack->top = malloc(sizeof(stackitem));
    stack->top->value = 0;
    stack->top->prev = NULL;
    stack->bottom = stack->top;
    stack->items_on_stack = 1;
    return stack;
}
