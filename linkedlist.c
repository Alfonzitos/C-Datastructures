#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node node;
struct linkedlist;
void add_node(struct linkedlist *list, node *newNode);
node *create_node(int iteration);
void make_head(struct linkedlist *list);
void iterate_forwards(node *head, node *tail);
void iterate_backwards(node *head, node *tail);
void delete_node(node *target);
node *forwards_find(int id, node *head, node *tail);
node *backwards_find(int id, node *head, node *tail);
node *find_wrapper(node *head, node *tail);

struct node
{
    int id;
    node *next;
    node *previous;
};

struct linkedlist
{   
    node *head;
    node *tail;
    int elements;
} list;

int main(void)
{
    make_head(&list);
    for (int i = 1; i <= 10; i++)
    {
        add_node(&list, create_node(i));
    }
    iterate_forwards(list.head, list.tail);
    iterate_backwards(list.head, list.tail);


    node *res = find_wrapper(list.head, list.tail);
    if (res != NULL)
    {
        printf("Address is %p, value is %d\n", res, res->id);
    }
    else
    {
        printf("ID not found\n");
    }
}

node *find_wrapper(node *head,  node *tail)
{   
    char answer[15];
    printf("Enter an ID to find: ");
    fgets(answer, 15, stdin);
    for (int i = 0; i < strlen(answer); i++)
    {   
        if (answer[i] == '\n')
        {
            answer[i] = '\0'; 
        }
    }
    float res = atoi(answer);
    if (res < list.elements/2)
    {
        return forwards_find(res, head, tail);
    }
    else
    {
        return backwards_find(res, head, tail);
    }
    
}


node *forwards_find(int id, node *head, node *tail)
{
    printf("Doing forwards_find\n");
    node *iter = head;
    do 
    {
        if (iter->id == id)
        {
            return iter;
        }
        if (iter->next == NULL)
        {
            return NULL;
        }
        iter = iter->next;
    } while (iter->id != id); 
    if (iter->id == id)
    {
        return iter;
    }
    return NULL;
}

node *backwards_find(int id, node *head, node *tail)
{
    printf("Doing backwards_find\n");
    node *iter = tail;
    do
    {   
        if (iter->id == id)
        {
            return iter;
        }
        if (iter->previous == NULL)
        {
            return NULL;
        }
        iter = iter->previous;
    } while (iter->id != id);
    
    if (iter->id == id)
    {
        return iter;
    }
    return NULL;
}   



void delete_node(node *target) 
{
    if (target = list.head)
    {   
        list.head = list.head->next;
        list.head->previous = NULL; 
        free(target);
        list.elements--;
    }
    else if (target =  list.tail)
    {
        list.tail = list.tail->previous;
        list.tail->next = NULL;
        free(target);
        list.elements--;

    }
    else
    {
        target->previous->next = target->next;
        target->next->previous = target->previous;
        free(target);
        list.elements--;
    }
}

void iterate_backwards(node *head, node *tail)
{
    node *iter = tail;
    do
    {
        printf("value = %d\n", iter->id);
        iter = iter->previous;
    } while (iter != head);
    printf("value = %d\n", iter->id);

}

void iterate_forwards(node *head, node *tail)
{
    node *iter = head;
    do
    {
        printf("value = %d\n", iter->id);
        iter = iter->next;
    } while (iter != tail);
    printf("value = %d\n", iter->id);
}

void add_node(struct linkedlist *list, node *newNode)
{
    list->tail->next = newNode;
    newNode->previous = list->tail;
    list->tail = newNode;
    list->elements++;
}

node *create_node(int iteration)
{
    node *temp = malloc(sizeof(node));
    temp->id = iteration;
    return temp;
}

void make_head(struct linkedlist *list)
{
    list->head = create_node(0);
    list->tail = list->head;
    list->head->previous = NULL;
    list->head->next = NULL;
}