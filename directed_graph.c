#include "graph.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define INFINITY 10

char build_graph_cmd(node *head)
{
    int num_of_nodes = 0;
    char input = 'n';
    scanf(" %d", &num_of_nodes);

    node *current = head;

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
                perror("Error: node malloc failed");
                return 'E';
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
            return input;
        }
    }
    return 'E';
}

char insert_node_cmd(node *head)
{
    int node_num;
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
            return add_edges(current, head);
        }
        previous = current;
        current = current->next;
    }
    // If the node doesn't exist: create a new one
    if (previous == NULL)
    {
        head = (node *)malloc(sizeof(node));
        head->node_num = node_num;
        head->edges = NULL;
        head->next = NULL;
        return add_edges(head, head);
    }
    else
    {
        previous->next = (node *)malloc(sizeof(node));
        previous->next->node_num = node_num;
        previous->next->edges = NULL;
        previous->next->next = NULL;
        return add_edges(previous->next, head);
    }
}

void delete_node_cmd(node **head)
{
    int node_num;
    scanf("%d", &node_num);
    node *current = *head;
    node *previous = NULL, *next_head = NULL;
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
                next_head = (*head)->next;
                free(*head);
                *head = next_head;
                return;
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

void TSP_cmd(node *head)
{
    int k;
    scanf("%d", &k);
    int *nums = (int *)malloc(sizeof(int) * k);
    for (int i = 0; i < k; i++)
    {
        scanf("%d", &nums[i]);
    }

    int min = -1, a;
    for (int start = 0; start < k; start++)
    {
        a = 0;
        int *n = (int *)malloc(sizeof(int) * (k - 1));
        for (int i = 0; i < k; i++)
        {
            if (i != start)
            {
                n[a++] = nums[i];
            }
        }
        int tsp = isAllPath(k - 1, nums[start], n, head);
        if (tsp != -1 && min == -1)
        {
            min = tsp;
        }
        else if (tsp != -1 && tsp < min)
        {
            min = tsp;
        }
    }
    printf("TSP shortest path: %d \n", min);
}

void shortsPath_cmd(node *head)
{
    int start_node, end_node;
    scanf(" %d %d", &start_node, &end_node);
    int result = shortestPath_aid(head, start_node, end_node);
    printf("Dijsktra shortest path: %d \n", result);
}
