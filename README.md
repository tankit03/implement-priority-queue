# Priority Queue Implementation

This project implements a priority queue based on a minimizing binary heap. The priority queue will be utilized for various operations, and specific criteria will be evaluated for correctness and efficiency.

## Priority Queue Structure

- The `pq` struct defines a heap-based priority queue.

## Priority Queue Functions

- `pq_create()` correctly allocates and initializes a heap-based priority queue.
- `pq_free()` correctly frees all memory associated with a priority queue (no memory leaks!).
- `pq_isempty()` correctly determines whether a priority queue contains any elements or not.
- `pq_first()` correctly returns the first value in a priority queue in O(1) runtime complexity.
- `pq_first_priority()` correctly returns the priority value associated with the first element in a priority queue in O(1) runtime complexity.
- `pq_insert()` correctly inserts a value into a priority queue with the specified priority and restores the heap property as needed in O(log n) runtime complexity.
- `pq_remove_first()` correctly removes the first element from a priority queue and returns its value, restoring the heap property as needed in O(log n) runtime complexity.

## Dijkstra's Application

This criterion is linked to an application that uses Dijkstra's algorithm to find and output the least-cost paths in the graph defined in `airports.dat`.
