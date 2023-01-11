#include "graph.h"
#include <stdio.h>
#include <ctype.h>

void build_graph_cmd(pnode *head)
{
    pnode temp = *head;
    int num_of_nodes = 0, i = 0;
    char input = 'n';
    scanf("%d", &num_of_nodes);
    if (head != NULL)
    {
        free(head);
    }
    // allocate storage for the graph data structure
    head = malloc(sizeof(pnode));
    if (head == NULL)
    {
        printf("Error: malloc failed");
        return;
    }
    // initialize head pointer for all vertices
    for (i = 0; i < num_of_nodes; i++)
    {
        head[i] = malloc(sizeof(node));
        if (head[i] == NULL)
        {
            printf("Error: malloc failed");
            return;
        }
        head[i]->next = NULL;
    }
    // add edges to the directed graph one by one
    node *new_node = malloc(sizeof(node));
    while (!isalph(input) || input == 'n')
    {
        scanf("%c", &input);
        if (input == 'n')
        {
            scanf("%c", &input);
            new_node->node_num = atoi(input);
        }
        else
        {
            edge *e = malloc(sizeof(edge));
            e->endpoint = head + new_node->node_num;
            scanf("%c", &input);
            e->weight = atoi(input);
        }
    }
    free(new_node);
}