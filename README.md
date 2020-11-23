cTrace is a program that simulates s contact tracing system for combating the spread of a virus.
The program simulates a social network (represented as a graph),
in which an epidemic is spreading, and contact tracers are searching for infected people,
trace their contacts, and attempt to break the chain of infection.

The program receives a config file (json) as an input, which includes the description of the
social network graph, a list of agents (viruses and contact tracers), and the type of tracing that will be preforemd.

The program receives the path of the config file as the first command line argument.
After the program is initialized, the function simulate() would trigger.
The simulate() function runs in a loop, until no more nodes can be infected.
In each iteration of the loop (Called a cycle), each agent in the session acts on the graph.
The two types of agents which operate on the graph are contact tracers and viruses.
Viruses infect the node they occupy, and spread themselves (By creating new viruses) into adjacent nodes.
Contact tracers attempt to break the chain of infection by disconnecting a node from the graph.
The choice of the node to disconnect, is according to some pre-defined logic (Described below).

Each Contact tracer creates a Tree from the graph using a BFS algoritm and chooses a node to disconnect using the function trace().
There are 3 different types of traces available:

  RootTree – Simply returns the index of the root of the tree.
  
  MaxRankTree – Returns the index of the node in the tree with the highest number of children.
  In case of a tie, the node with the smallest depth in the tree would be picked. If there is still a tie, 
  then the left-most node in that tree would be picked.
  
  CycleTree – Starts traversing the tree from the root, picking always the left-most child.
  Returns the c'th node in this trip, where c is the cycle in which the tree was created.
  If the trip is less than c nodes long, returns the last node in it.
