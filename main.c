#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    node *head = (node *)malloc(sizeof(pnode));
    if (head == NULL)
    {
        printf("Error: head malloc failed");
        return 0;
    }
    char input = 'a';
    while (input != 'D')
    {
        scanf(" %c", &input);
        switch (input)
        {
        case 'A':
            build_graph_cmd(head);
            break;

        case 'B':
            printGraph_cmd(head);
            break;

        case 'C':
            insert_node_cmd(head);
            break;

        default:
            break;
        }
    }
    return 0;
}