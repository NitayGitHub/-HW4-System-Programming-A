#include "graph.h"
#include <stdio.h>
#include <ctype.h>

node *find_node(node *, int);
edge *find_empty_edge(node *);

void build_graph_cmd(node *head)
{
    node *current = head;
    edge *current_edge = NULL;
    int num_of_nodes = 0;
    char input = 'n';
    scanf("%d", &num_of_nodes);
    if (head != NULL)
    {
        free(head);
    }

    // allocate storage for head node in graph
    head = (node *)malloc(sizeof(pnode));
    if (head == NULL)
    {
        printf("Error: head malloc failed");
        return;
    }

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
    while (!isalph(input) || input == 'n')
    {
        scanf("%c", &input);
        if (input == 'n')
        {
            scanf("%c", &input);
            current = find_node(head, atoi(input));
        }
        else
        {
            current_edge = find_empty_edge(current);
            current_edge = (edge *)malloc(sizeof(edge));
            if (current_edge == NULL)
            {
                printf("Error: edge malloc failed");
                return;
            }
            current_edge->endpoint = atoi(input);
            current_edge->next = NULL;
            scanf("%c", &input);
            current_edge->weight = atoi(input);
        }
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