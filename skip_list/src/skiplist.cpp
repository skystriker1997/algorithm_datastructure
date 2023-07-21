#include "skiplist.h"



Node::Node() {
    val_ = -1;
}



Node::Node(int val) {
    val_ = val;
}



SkipList::SkipList() {
    dummy_head_ = new Node{};
    max_level_ = 0;
}



SkipList::~SkipList() {
    delete dummy_head_;
}



Node* SkipList::Find(int val) {
    Node* curr_node = dummy_head_;
    for(int i=max_level_; i>=0; i--) {
        while(curr_node->next_nodes_[i]!=nullptr && curr_node->next_nodes_[i]->val_<val)
            curr_node = curr_node->next_nodes_[i];
        if(curr_node->next_nodes_[i]!=nullptr && curr_node->next_nodes_[i]->val_==val)
            return curr_node->next_nodes_[i];
    }
    return nullptr;
}



void SkipList::Insert(int val) {
    if(Find(val)!= nullptr)
        return;
    unsigned int level = LevelGenerator();     // it's the top level this node reaches
    Node* node = new Node{val};
    if(max_level_<level)
        max_level_ = level;
    Node* curr_node = dummy_head_;
    for(int i=level; i>=0; i--) {
        // while loop is used to locate the node at the certain level to adjust accordingly
        while(curr_node->next_nodes_[i]!=nullptr && curr_node->next_nodes_[i]->val_<val)
            curr_node = curr_node->next_nodes_[i];
        node->next_nodes_[i] = curr_node->next_nodes_[i];
        curr_node->next_nodes_[i] = node;
    }
}



void SkipList::Delete(int val) {
    Node* curr_node = dummy_head_;
    Node* node_to_delete = nullptr;
    for(int i=max_level_; i>=0; i--) {
        while(curr_node->next_nodes_[i]!=nullptr && curr_node->next_nodes_[i]->val_<val)
            curr_node = curr_node->next_nodes_[i];
        if(curr_node->next_nodes_[i]!=nullptr && curr_node->next_nodes_[i]->val_==val) {
            if(!node_to_delete)
                node_to_delete = curr_node->next_nodes_[i];
            curr_node->next_nodes_[i] = curr_node->next_nodes_[i]->next_nodes_[i];
        }
    }
    delete node_to_delete;
    while(max_level_>0 && dummy_head_->next_nodes_[max_level_]==nullptr)
        max_level_--;
}




void SkipList::PrintAll() const {
    Node* curr_node;
    for(int i = max_level_; i>=0; i--) {
        curr_node = dummy_head_;
        while(curr_node->next_nodes_[i]) {
            std::cout << curr_node->next_nodes_[i]->val_ << " -> ";
            curr_node = curr_node->next_nodes_[i];
        }
        std::cout << std::endl;
    }
}



void SkipList::DeleteAll() {
    while(dummy_head_->next_nodes_[0]!= nullptr)
        Delete(dummy_head_->next_nodes_[0]->val_);
}



unsigned int SkipList::LevelGenerator() {
    static std::random_device rd;
    static std::mt19937 generator(rd());
    static std::uniform_real_distribution<double> distribution(-1.0, 1.0);
    unsigned int level = 0;
    while (distribution(generator) < 0 && level<=LV_LIMIT)   // 50% -- 25% -- 12.5% --...
        level += 1;
    return level;
}

