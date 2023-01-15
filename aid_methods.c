#include "graph.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define INFINITY 10

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
                return 'E';
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
                return 'E';
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

void deleteGraph_cmd(node **head)
{
    while (*head != NULL)
    {
        int node_num = (*head)->node_num;
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
                    break;
                }
                else
                {
                    previous->next = current->next;
                }
                free(current);
                break;
            }
            previous = current;
            current = current->next;
        }
    }
}

int find_path(node *head, int i, int j)
{
    node *tmp = find_node(head, i);
    edge *current_edge = tmp->edges;
    if (current_edge == NULL)
    {
        return 0;
    }

    while (current_edge != NULL)
    {
        if (current_edge->endpoint->node_num == j)
        {
            return current_edge->weight;
        }
        current_edge = current_edge->next;
    }
    return 0;
}

int shortsPath_aid(node *head, int start, int end)
{
    int isPath, rank = 0;
    node *current = head;
    while (current != NULL)
    {
        rank++;
        current = current->next;
    }
    int shortMat[rank][rank], i, j;
    for (i = 0; i < rank; i++)
    {
        for (j = 0; j < rank; j++)
        {
            isPath = find_path(head, i, j);
            if (i != j && !isPath)
            {
                shortMat[i][j] = INFINITY;
            }
            else
            {
                shortMat[i][j] = isPath;
            }
        }
    }

    for (i = 0; i < rank; i++)
    {
        for (j = 0; j < rank; j++)
        {
            for (int k = 0; k < rank; k++)
            {
                if (shortMat[j][k] > shortMat[j][i] + shortMat[i][k])
                {
                    shortMat[j][k] = shortMat[j][i] + shortMat[i][k];
                }
            }
        }
    }

    if (shortMat[start][end] == INFINITY)
    {
        return -1;
    }
    else
    {
        return shortMat[start][end];
    }
}

int isAllPath(int k, int start, int *nodes, node *head)
{
    if (k == 1)
    {
        int tmp = shortsPath_aid(head, start, nodes[0]);
        if (tmp == -1)
        {
            return -1;
        }
        else
        {
            return tmp;
        }
    }
    int a, min = -1;
    for (int s = 0; s < k; s++)
    {
        a = 0;
        int *n = (int *)malloc(sizeof(int) * (k - 1));
        for (int i = 0; i < k; i++)
        {
            if (i != s)
            {
                n[a++] = nodes[i];
            }
        }
        int tmp = isAllPath(k - 1, nodes[s], n, head);
        if (tmp != -1 && min == -1)
        {
            int tmp2 = shortsPath_aid(head, start, nodes[s]);
            if (tmp2 != -1)
            {
                min = tmp + tmp2;
            }
        }
        else if (tmp != -1)
        {
            int tmp2 = shortsPath_aid(head, start, nodes[s]);
            if (tmp2 != -1 && tmp + tmp2 < min)
            {
                min = tmp + tmp2;
            }
        }
    }
    return min;
}