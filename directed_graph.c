#include "graph.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

node *find_node(node *, int);
edge *find_empty_edge(node *);
void insert_node_cmd(node *head);

void build_graph_cmd(node *head)
{
    edge *current_edge = NULL;
    int num_of_nodes = 0;
    char input = 'n';
    scanf(" %d", &num_of_nodes);

    // allocate storage for head node in graph
    node *current = head;

    // allocate storage for all nodes in graph
    for (int i = 0; i < num_of_nodes; i++)
    {

        current->next = NULL;
        current->node_num = i;
        current->edges = NULL;
        if (i != num_of_nodes - 1)
        {
            current->next = (node *)malloc(sizeof(pnode));
            if (current->next == NULL)
            {
                printf("Error: node malloc failed");
                return;
            }
        }
        current = current->next;
    }

    // add edges to the directed graph one by one
    while (1)
    {
        scanf(" %c", &input);
        if (input == 'n')
        {
            scanf(" %c", &input);
            current = find_node(head, input - '0');
        }
        else if (isdigit(input))
        {
            current_edge = find_empty_edge(current);
            current_edge = (edge *)malloc(sizeof(edge));
            if (current_edge == NULL)
            {
                printf("Error: edge malloc failed");
                return;
            }
            current_edge->endpoint = find_node(head, input - '0');
            current_edge->next = NULL;
            scanf("%c", &input);
            current_edge->weight = input - '0'; // only for 0-9
        }
        else
        {
            break;
        }
    }
    puts("end\n");
}
/*
void insert_node_cmd(node *head)
{
    int node_num;
    char input = '1';
    scanf(" %d", &node_num);
    if (find_node(head, node_num) == NULL)
    {
        node *current = head;
        while (current != NULL)
        {
            current = current->next;
        }
        current = (node *)malloc(sizeof(pnode));
        if (current == NULL)
        {
            printf("Error: node malloc failed");
            return;
        }
        current->next = NULL;
        current->node_num = node_num;
        current->edges = NULL;
        while (isdigit(input))
        {
            scanf(" %c", &input);
        }
    }
    else
    {
    }
}*/

void printGraph_cmd(node *head)
{
    if (head == NULL)
    {
        puts("head is null");
    }
    node *current = head;
    edge *current_edge = NULL;
    while (current != NULL)
    {
        printf("Node no. : %d", current->node_num);
        current_edge = current->edges;
        if(current_edge == NULL){
            perror("No edges");
        }
        while (current_edge != NULL)
        {
            printf("%d(%d) ", current_edge->endpoint->node_num, current_edge->weight);
            current_edge = current_edge->next;
        }
        printf("\n");
        current = current->next;
    }
}

node *find_node(node *head, int node_num)
{
    node *current = head;
    while (current != NULL)
    {
        if (current->node_num == node_num)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

edge *find_empty_edge(node *current)
{
    edge *e = current->edges;
    if (e == NULL)
    {
        return e;
    }
    while (e->next != NULL)
    {
        e = e->next;
    }
    return e;
}

void insert_node_cmd(node *head)
{
    int node_num;
    printf("Enter the node number: ");
    scanf("%d", &node_num);

    node *current = head;
    node *previous = NULL;
    // Search for the node
    while (current != NULL)
    {
        if (current->node_num == node_num)
        {
            // Delete all edges connected to the node
            edge *current_edge = current->edges;
            edge *previous_edge = NULL;
            while (current_edge != NULL)
            {
                previous_edge = current_edge;
                current_edge = current_edge->next;
                free(previous_edge);
            }
            current->edges = NULL;
            return;
        }
        previous = current;
        current = current->next;
    }
    // If the node doesn't exist, create a new one
    if (previous == NULL)
    {
        head = (node *)malloc(sizeof(node));
        head->node_num = node_num;
        head->edges = NULL;
        head->next = NULL;
    }
    else
    {
        previous->next = (node *)malloc(sizeof(node));
        previous->next->node_num = node_num;
        previous->next->edges = NULL;
        previous->next->next = NULL;
    }
}