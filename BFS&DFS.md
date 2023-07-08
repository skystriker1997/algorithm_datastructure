When we traverse data structures such as binary tree and graph, in which nodes are connected, we can use broad first search(BFS) or deep first search(DFS) to visit each node in a certain order. As the name suggests, BFS visits closest nodes at first, then comes to second nearest, and so on. In contrast, DFS goes through a path as deep as possible each time. I will demonstrate how to implement them with simple cases. 

BFS:

Queue, working by first-in-first-out, fits into the trait of BFS. 

```cpp
// Lets say we have a binary tree whose root node is named root, and I gonna traverse the tree level by level to implement some functionality upon each node visited in order.
std::queue<Node*> myqueue;
if(root != nullptr) myqueue.push(root);
while (!myqueue.empty()) {
  Node* node = myqueue.pop();
  // TODO
  if(node->right != nullptr) myqueue.push(node->right);
  if(node->left != nullptr) myqueue.push(node->left);
}
```

DFS:

Stack, working by last-in-first-out, fits into the trait of DFS. 

```cpp
std::stack<Node*> mystack;
if(root != nullptr) mystack.push(root);
while (!mystack.empty()) {
  Node* node = mystack.pop();
  // TODO
  if(node->right != nullptr) mystack.push(node->right);
  if(node->left != nullptr) mystack.push(node->left);
}
```

