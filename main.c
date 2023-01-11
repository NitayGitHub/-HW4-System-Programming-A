#include "graph.h"
#include <stdio.h>

int main()
{
    pnode *head = NULL;
    char input = 'a';
    while (input != 'D')
    {
        scanf("%c", &input);
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
    return 0;
}