#include <vector>
#include <random>
#include <iostream>


#define LV_LIMIT 15    // the upper limit of level

class Node {
public:
    Node();
    explicit Node(int val);
    ~Node() = default;
    int val_;
    std::vector<Node*> next_nodes_{LV_LIMIT+1, nullptr};
    // the index of vector represents the level; the element is the next node of this node at the level denoted by the index
};



class SkipList {
public:
    SkipList();
    ~SkipList();
    void Insert(int val);
    void Delete(int val);
    Node* Find(int val) const;
    static unsigned int LevelGenerator();
    void PrintAll() const;
    void DeleteAll();
    Node* dummy_head_;
    unsigned int max_level_;    // the highest level that current nodes reach
};

