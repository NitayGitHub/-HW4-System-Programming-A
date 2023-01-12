#include "graph.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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
        printf("Node %d : ", current->node_num);
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

int parse_to_int(char input)
{
    int weight;
    sscanf(&input, "%d", &weight);
    return weight;
}

char add_edges(node *current, node *head)
{
    char input;
    edge *current_edge = current->edges;

    while (1)
    {
        scanf(" %c", &input);
        if (isalpha(input))
        {
            return input;
        }
        if (current_edge == NULL)
        {
            current->edges = (edge *)malloc(sizeof(edge));
            if (current == NULL)
            {
                printf("Error: edge malloc failed");
                return 'e';
            }
            current_edge = current->edges;
            current_edge->endpoint = find_node(head, parse_to_int(input));
            current_edge->next = NULL;
            scanf(" %c", &input);
            current_edge->weight = parse_to_int(input); // only for 0-9
        }
        else
        {
            while (current_edge->next != NULL)
            {
                current_edge = current_edge->next;
            }
            current_edge->next = (edge *)malloc(sizeof(edge));
            if (current_edge->next == NULL)
            {
                printf("Error: edge malloc failed");
                return 'e';
            }
            current_edge->next->endpoint = find_node(head, parse_to_int(input));
            current_edge->next->next = NULL;
            scanf(" %c", &input);
            current_edge->next->weight = parse_to_int(input); // only for 0-9
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