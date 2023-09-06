/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: tanish hupare 
 * Email: huparet@oregonstate.edu
 */

#include <stdlib.h>
#include "pq.h"
#include "dynarray.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq{

	struct dynarray* heap;
	
};

struct node{

	int priority;
	void* value;
	
};

/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
	
	struct pq* temp_pq = malloc(sizeof(struct pq));
	temp_pq->heap = dynarray_create();

	return temp_pq;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
	
	dynarray_free(pq->heap);
	free(pq);

}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
	
	if(dynarray_size(pq->heap) == 0){
		return 1;
	}else{
		return 0;
	}
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */


void pq_insert(struct pq* pq, void* value, int priority) {

	// struct node* temp_node = malloc(sizeof(struct node));
	// temp_node->value = value;
	// temp_node->priority = priority;
	// int parent_index = 0;
	// int curr_index;


	// dynarray_insert(pq->heap,temp_node);
	// curr_index = dynarray_size(pq->heap) - 1;

	// struct node* temp = NULL;
	
	// while(1){

	// 	parent_index = (curr_index - 1)/2;
	// 	temp = (struct node*) dynarray_get(pq->heap, parent_index);

	// 	if(temp->priority > temp_node->priority){

	// 		dynarray_set(pq->heap, parent_index, temp_node);
	// 		dynarray_set(pq->heap, curr_index, temp);
	// 		curr_index = parent_index;

	// 	}else{
	// 		break;
	// 	}
	// }

	// return;

	struct node* temp = malloc(sizeof(struct node));
	temp->value = value;
	temp->priority = priority;


	//insert the value of that element into the array and increase size of pq
	dynarray_insert(pq->heap, temp);

	//initialize current index to array size and parent index to 0
 	int curr_index = dynarray_size(pq->heap) - 1;
    int parent_index = 0;

	//create temp data struct
	struct node* temp_1 = NULL;

	//while true
	while(1){

		//calculate the inserted elements parent index using the formula
		parent_index = (curr_index - 1) / 2;
		temp_1 = (struct node*) dynarray_get(pq->heap, parent_index);
		
		//compare the priority of the inserted element to the priority of its parent. If priority of parent is greater than the priority of inserted element then swap 
		if(temp_1->priority > temp->priority){
			dynarray_set(pq->heap, parent_index, temp);
			dynarray_set(pq->heap, curr_index, temp_1);
			curr_index = parent_index;
		}
		//element has reached beginning of array OR parent priority is less than inserted element priority
		else{
			break;
		}
	}

	return;

}



/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
	
	struct node* first_val;
	first_val = dynarray_get(pq->heap,0);

	if(first_val != NULL){
		return first_val->value;
	}else{
		return NULL;
	}
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
	
	struct node* first_val;
	first_val = dynarray_get(pq->heap,0);

	if(first_val != NULL){
		return first_val->priority;
	}else{
		return 0;
	}

}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {

	if(pq_isempty(pq)){
		return NULL;
	}	
	
	struct node* root = dynarray_get(pq->heap,0);
	void* root_data = root->value;

	struct node* last_el = dynarray_get(pq->heap,dynarray_size(pq->heap) -1);

	dynarray_set(pq->heap,0,last_el);
	dynarray_remove(pq->heap,dynarray_size(pq->heap) - 1);
	last_el = NULL;

	free(root);
	

	int curr_idx = 0;

	int left_child_idx = curr_idx * 2 + 1;
	int right_child_idx = curr_idx * 2 + 2;

	while(left_child_idx < dynarray_size(pq->heap)){

		int lowest_child_idx = curr_idx;

		struct node* curr = (struct node*)dynarray_get(pq->heap,curr_idx);
		struct node* left_child = (struct node*)dynarray_get(pq->heap,left_child_idx);

		if(left_child->priority < curr->priority){
			lowest_child_idx = left_child_idx;
		}
		if(right_child_idx < dynarray_size(pq->heap)){

			struct node* right_child = (struct node*)dynarray_get(pq->heap,right_child_idx);

			if(right_child->priority < ((struct node*)dynarray_get(pq->heap, lowest_child_idx))->priority){
				lowest_child_idx = right_child_idx;
			}
		}
	

		if(curr->priority > ((struct node*)dynarray_get(pq->heap, lowest_child_idx))->priority){

			dynarray_set(pq->heap,curr_idx, dynarray_get(pq->heap, lowest_child_idx));
			dynarray_set(pq->heap, lowest_child_idx, curr);
			curr_idx = lowest_child_idx;
			left_child_idx = curr_idx * 2 + 1;
			right_child_idx = curr_idx * 2 + 2;

		}else{
			break;
		}
	}

	return root_data;

}

	



	
	



