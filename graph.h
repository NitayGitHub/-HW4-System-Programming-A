#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ *pnode;

typedef struct edge_
{
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;

typedef struct GRAPH_NODE_
{
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;

// main methods
char build_graph_cmd(node *head);
char insert_node_cmd(node *head);
void delete_node_cmd(node **head);
void shortsPath_cmd(node *head);
void TSP_cmd(node *head);

// aid methods
void printGraph_cmd(node *head);
int parse_to_int(char input);
char add_edges(node *current, node *head);
node *find_node(node *head, int node_num);
void deleteGraph_cmd(node *head);
int isAllPath(int k, int start, int *nodes, node *head);
int shortestPath_aid(node *head, int start_node, int end_node);


#endif
