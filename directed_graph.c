#include "graph.h"
#include <stdio.h>

void build_graph_cmd(pnode *head)
{
    pnode temp = *head;
    int num_of_nodes = 0, i = 0;
    char input = 'c';
    scanf("%d", &num_of_nodes);

    
    scanf("%c", &input);
    for (int i = 0; i < num_of_nodes; i++)
    {
        scanf("%c", &input);
        while(input != 'n')
        switch (input)
        {
        case 'A':
            build_graph_cmd(head);
            break;

        case 'B':

            break;

        case 'C':

            break;

        default:
            break;
        }
    }
}