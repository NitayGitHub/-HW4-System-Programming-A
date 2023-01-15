#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    node *head = NULL;
    node **tmp_head;
    char input = 'a';
    int scan = 1;

    while (1)
    {
        if (scan)
        {
            if (scanf(" %c", &input) == EOF)
            {
                deleteGraph2(tmp_head);
                exit(0);
            }
        }
        else
        {
            scan = 1;
        }

        switch (input)
        {
        case 'A':
            if (head != NULL)
            {
                deleteGraph2(tmp_head);
            }
            head = (node *)malloc(sizeof(pnode));
            if (head == NULL)
            {
                printf("Error: head malloc failed");
                return 0;
            }
            tmp_head = &head;
            input = build_graph_cmd(head);
            scan = 0;
            break;

        case 'B':
            input = insert_node_cmd(head);
            scan = 0;
            break;

        case 'D':
            delete_node_cmd(tmp_head);
            break;

        case 'S':
            shortsPath_cmd(head);
            break;

        case 'T':
            TSP_cmd(head);
            break;

        case 'F':
            deleteGraph2(tmp_head);
            head = (node *)malloc(sizeof(pnode));
            break;

        case 'P':
            printGraph_cmd(head);
            break;

        default:
            break;
        }
    }
    return 0;
}
