#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ *pnode;;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;

void build_graph_cmd(node *head);
void insert_node_cmd(node *head);
void delete_node_cmd(node *head);
void printGraph_cmd(node head); //for self debug
void deleteGraph_cmd(node* head);
void shortsPath_cmd(node head);
void TSP_cmd(node head);

#endif
