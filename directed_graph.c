#include "graph.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void build_graph_cmd(node *head)
{
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

    scanf(" %c", &input);
    // add edges to the directed graph one by one
    while (1)
    {
        if (input == 'n')
        {
            scanf(" %c", &input);
            current = find_node(head, parse_to_int(input));
        }
        else if (isdigit(input))
        {
            input = add_edges(current, head);
        }
        else
        {
            break;
        }
    }
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
            add_edges(current, head);
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
        add_edges(head, head);
    }
    else
    {
        previous->next = (node *)malloc(sizeof(node));
        previous->next->node_num = node_num;
        previous->next->edges = NULL;
        previous->next->next = NULL;
        add_edges(previous->next, head);
    }
}

void delete_node_cmd(node * head){
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
            // Delete the node
            if (previous == NULL)
            {
                head = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Node %d is not in the graph\n", node_num);
}