### From linked list to skip list

Let's review the time complexity of searching for an element in a sorted linked list. The linked list uses pointers to chain every element, and we need to traverse elements one by one from the head node until the target one, so the time complexity of searching is O(n), a linear one. Can we improve it?

We may recall how a binary tree works. At each node of a binary tree, we encounter two branches, one towards a chunk of elements with a value less than that of the root, the other one promises greater values than that of the root. By choosing the correct direction, we avoid meaningless visits. Intuitively, we expect that there could be multiple layers above the original linked list (bottom layer), and each layer can tell us where to enter the next layer, rather than starting at the head node for each layer. Moreover, similar to the binary tree, the number of elements in each layer should decay as the layer grows.

An ideal implementation is to put every other element (node) into the above layer so that the number of elements in the top layer will turn out to be 1. Let's say we have 3 layers, and we want to search for 8.

Layer 2: 1->5 

Layer 1: 1->3->5->7 

Layer 0: 1->2->3->4->5->6->7->8

Beginning with layer 2, the last node is 5, so I just jump to layer 1 and start searching at 5, but the last one of layer 1, 7, is also less than 8, so I jump down to layer 0, start searching at 7, and finally find out the target at the last layer. If I only use the original layer to search, I will visit 8 nodes to find the target. However, with the help of above layers, I only need to visit 4 nodes to locate.

Let's analyze the time complexity of the skip list. Recall that we put every other element into the above layer, so the number of layers turns out to be log<sub>2</sub>N. Note that at each layer, what we do is to locate the node whose next node's value is greater than the target and then jump to the below layer at the same value, so the time complexity at each layer is O(1). In summary, the overall time complexity is log<sub>2</sub>N.

When it comes to inserting and deleting elements into the skip list, we should remember that one element in layer 0 may appear multiple times in above layers. So, when we delete something from the original linked list, also remove it from above layers. For insertion, we need to determine how many layers should be placed with the element. My solution is to use a random value generator, whose possibility of generating N is half of that of generating N-1, so that the number of elements in layer N is approximately half of that in layer N-1. Since each element in layer N-1 has 50% probability to appear also in layer N, the distance between two elements at layer N-1, which are adjacent at layer N, is very unlikely to be too large to maintain the efficiency of in-layer search, and then the time complexity at each layer is very likely to keep at O(1). In summary, this method balances the tradeoff between efficiency and the ideal structure of the whole skip list. Also note that the order of traversing layers when inserting or deleting elements is always from the top to bottom, to leverage the traits of the skip list.

Compared with red-black trees, the skip list is easier to understand. Since the C++ STL does not provide it, I implemented it. Please refer to my implementation for more details.



