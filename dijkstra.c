#include <stdio.h>
#include <stdlib.h>
#include "pq.h"

#define DATA_FILE "airports.dat"
#define START_NODE 0

struct node{
	int N;
	int prev;
};

int main(int argc, char const *argv[]) {
	/*
	 * Open file and read the first two int: num of nodes, num of edges
	 */
	int n_nodes, n_edges;
	
	//int total_cost;
	int matrix[100][100] = {0};

	FILE* file = fopen(DATA_FILE, "r");
	fscanf(file, " %d %d ", &n_nodes, &n_edges);

	// this intializes the price and previous array to size of n_nodes

	int* price = malloc(sizeof(int) *n_nodes);
	int* prev = malloc(sizeof(int) *n_nodes);
	

	// this reads the edge data and also stores the adjacency martix
	for(int i = 0; i < n_nodes; i++){
		for(int j = 0; j <n_nodes; j++){
			matrix[i][j] = 0;
		}
	}

	for(int i = 0; i < n_edges; i++){
		int going;
		int toward;
		int cost;
		fscanf(file, "%d %d %d", &going, &toward, &cost);
		matrix[going][toward] = cost;
	}

	// this intializes the price price array and previous array
	for(int i = 0; i < n_nodes; i++){
		price[i] = 9999;
		prev[i] = -1;
	}


	// create the node struct and initalize the start node
	struct node* start = malloc(sizeof(struct node));
	start->N = START_NODE;
	start->prev = 0;


	// create path struct and intialize
	struct pq* pri_q = pq_create();
	pq_insert(pri_q, start, 0);

	while(pq_isempty(pri_q) != 1){

		int total_cost = pq_first_priority(pri_q);

		struct node *Node = pq_remove_first(pri_q);
		int c_node  = Node->N;
		int p_node  = Node->prev;
		free(Node);

		if(total_cost < price[c_node]){

			price[c_node] = total_cost;
			prev[c_node] = p_node;

			for(int i = 0; i < n_nodes; i++){

				

				if(matrix[c_node][i] != 0){
					
					int ci = matrix[c_node][i];
					struct node *node_in = malloc(sizeof(struct node));
					node_in->N = i;
					node_in->prev = c_node;
					pq_insert(pri_q, node_in, total_cost+ci);

				}		
			}
		}
	}
	pq_free(pri_q);


	// this prints the shortest path from the start node to the each node
	printf("lowest coast paths from start node %d: \n", START_NODE);

	// this prints the costs all of the path
	for(int i = 0; i < n_nodes; i++){

		printf("node: %d ", i);
		printf("cost: %d ", price[i]);
		printf("Path: ");


		int prv = i;
		int arr[n_nodes];
		int size = 0;
		int j = 0;

		printf(" 0 ");

		// prints the path and nodes.
		while(prv != 0){
			arr[j] = prv;
			j++;
			size++;
			prv = prev[prv];
		}

		for(int k = size-1; k >= 0; k--){
			printf("-> %d ", arr[k]);
		}

		printf("\n");
	

	}
	free(price);
	free(prev);
	fclose(file);

	 
  return 0;
}
