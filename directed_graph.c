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
            current->next = (node *)malloc(sizeof(node));
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
    int choice_num;
    scanf("%d", &choice_num);
    node *choice = find_node(*head, choice_num);
    if (choice == NULL)
    {
        perror("Error: node doesn't exist");
        return;
    }
    node * curr = *head;
    node *pre_choice = *head;
    node *next_head = NULL;
    edge *temp_curr_edge;
    edge *temp_pre_edge;

    // Delete edges connected to the node
    while(curr != NULL){
        temp_curr_edge = curr->edges;
        temp_pre_edge = curr->edges;
        while(temp_curr_edge != NULL){
            if(temp_curr_edge->endpoint->node_num == choice_num){
                if(temp_curr_edge == curr->edges){
                    curr->edges = temp_curr_edge->next;
                    free(temp_curr_edge);
                    break;
                }
                else{
                    temp_pre_edge->next = temp_curr_edge->next;
                    free(temp_curr_edge);
                    break;
                }
            }
            else{
                temp_pre_edge = temp_curr_edge;
                temp_curr_edge = temp_curr_edge->next;
            }
        }
        curr = curr->next;
    }

    // Delete the node and its edges
    if (choice_num == (*head)->node_num)
    {
        next_head = (*head)->next;
        temp_curr_edge = choice->edges;
        while (temp_curr_edge != NULL)
        {
            temp_pre_edge = temp_curr_edge;
            temp_curr_edge = temp_curr_edge->next;
            free(temp_pre_edge);
            temp_pre_edge = NULL;
        }
        free(*head);
        *head = next_head;
    }
    else
    {
        while (pre_choice != NULL)
        {
            if (pre_choice->next->node_num == choice->node_num)
            {
                break;
            }
            pre_choice = pre_choice->next;
        }
        if (pre_choice == NULL)
        {
            perror("Error: node doesn't exist");
            return;
        }
        //seperate the node from the list
        pre_choice->next = choice->next;

        //delete all edges connected to the node
        temp_curr_edge = choice->edges;
        while (temp_curr_edge != NULL)
        {
            temp_pre_edge = temp_curr_edge;
            temp_curr_edge = temp_curr_edge->next;
            free(temp_pre_edge);
            temp_pre_edge = NULL;
        }
        free(choice);
        choice = NULL;
    }
    return;
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
    // create an array of the original and new names of the nodes
    node *curr = head;
    int names[2][10];
    for (int i = 0; i < 10; i++)
    {
        names[0][i] = -1;
        names[1][i] = -1;
    }
    int num_of_nodes = 0;
    while (curr != NULL)
    {
        int n = curr->node_num;
        // original name
        names[0][n] = n;
        // new name
        names[1][n] = num_of_nodes;
        num_of_nodes++;
        curr = curr->next;
    }

    // Give nums new names
    for (int i = 0; i < k; i++)
    {
        if (nums[i] != names[1][nums[i]])
        {
            nums[i] = names[1][nums[i]];
        }
    }

    // Give nodes new names
    curr = head;
    for (int i = 0; i < num_of_nodes; i++)
    {
        //printf("New name : %d. Original name: %d.\n", names[1][curr->node_num], curr->node_num);
        if (curr->node_num != names[1][curr->node_num])
        {
            curr->node_num = names[1][curr->node_num];
        }
        curr = curr->next;
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
        free(n);
        if (tsp != -1 && min == -1)
        {
            min = tsp;
        }
        else if (tsp != -1 && tsp < min)
        {
            min = tsp;
        }
    }
    free(nums);

    // return names to original
    curr = head;
    for (int i = 0; i < 10; i++)
    {
        if (names[0][i] != -1)
        {
            curr->node_num = names[0][i];
            curr = curr->next;
        }
    }

    printf("TSP shortest path: %d \n", min);
}

void shortsPath_cmd(node *head)
{
    int start_node, end_node;
    scanf(" %d %d", &start_node, &end_node);

    // create an array of the original and new names of the nodes
    node *curr = head;
    int names[2][10];
    for (int i = 0; i < 10; i++)
    {
        names[0][i] = -1;
        names[1][i] = -1;
    }

    int num_of_nodes = 0;
    while (curr != NULL)
    {
        int n = curr->node_num;
        // original name
        names[0][n] = n;
        // new name
        names[1][n] = num_of_nodes;
        num_of_nodes++;
        curr = curr->next;
    }

    // Give nums new names
    if (start_node != names[1][start_node])
    {
        start_node = names[1][start_node];
    }
    if (end_node != names[1][end_node])
    {
        end_node = names[1][end_node];
    }

    int result = shortestPath_aid(head, start_node, end_node);

    // return names to original
    curr = head;
    for (int i = 0; i < 10; i++)
    {
        if (names[0][i] != -1)
        {
            curr->node_num = names[0][i];
            curr = curr->next;
        }
    }

    printf("Dijsktra shortest path: %d \n", result);
}
