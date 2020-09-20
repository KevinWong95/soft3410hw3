Instructions to build program:
Run compile.sh. This should compile the main program. (Use chmod u+x to add permissions if necessary).

Description of how program works:
The linkedlistmap is implemented using two struct: linkedlist_map, which is the struct representing the entire map, and linkedlist_map_entry, which represents a node in the linkedlist. From a high level, the data structure is implemented as a doubly linked list, with key-value pairs on each node.

linkedlist_map maintains a reference to the head and tail of the linked list, and whenever keys are retrieved / inserted, the program iterates through the linked list (starting at the head) to find/insert the appropriate node. Through this iteration, the program can also check for pre-existing keys and modify the previous entry to contain the new value.
