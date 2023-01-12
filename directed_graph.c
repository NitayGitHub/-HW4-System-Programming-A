#include "graph.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

node *find_node(node *, int);
edge *find_empty_edge(node *);

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
            puts("!");
            scanf(" %c", &input);
            printf("%d\n", input - '0');
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
    printf("-%d", head->node_num);
    puts("end");
}

void printGraph_cmd(node *head)
{
    puts("enter print");
    if (head == NULL)
    {
        puts("head is null");
    }
    else
    {
        puts("head is not null");
    }
    node *current = head;
    edge *current_edge = NULL;
    while (current != NULL)
    {
        puts("enter print");
        printf("Node no. : %d", current->node_num);
        // printf("Edge     : %d", current->edges);
        current_edge = current->edges;
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