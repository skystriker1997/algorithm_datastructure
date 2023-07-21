#include <vector>
#include <random>
#include <iostream>


#define LV_LIMIT 15

class Node {    // one node can appear in multiple levels; if node A appears in level N, then it must appear also in level N-1; its val is supposed to be unique; nodes are supposed to be sorted in ascending order in each level
public:
    Node();
    explicit Node(int val);
    ~Node() = default;
    int val_;
    std::vector<Node*> next_nodes_{LV_LIMIT+1, nullptr};     // the index of vector represents the level; the element represents the next node of this node at this certain level
};



class SkipList {
public:
    SkipList();
    ~SkipList();
    void Insert(int val);
    void Delete(int val);
    Node* Find(int val);
    static unsigned int LevelGenerator();
    void PrintAll() const;
    void DeleteAll();
    Node* dummy_head_;
    unsigned int max_level_;
};

