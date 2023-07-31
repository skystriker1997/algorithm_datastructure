#include <vector>
#include <random>
#include <iostream>
#include <type_traits>
#include <memory>
#include <string>
#include <concepts>
#include <functional>

#define LV_LIMIT 15    // the upper limit of level



template<typename T>
concept hashable = requires(T& input, std::hash<T> hasher) {
    hasher(input);
};



template<typename T>
concept printable = requires(T& obj) {
    std::cout << obj;
};



template<typename T>
std::size_t Hasher(const T& input) {
    static std::hash<T> hasher;
    return hasher(input);
}



template<typename TVal, typename TKey>
class Node {
public:
    TVal val_;

    TKey key_;

    std::size_t hash_;

    std::vector<Node*> next_nodes_{LV_LIMIT+1, nullptr};
    // the index of vector represents the level; the element is the next node of this node at the level denoted by the index

    Node() = default;

    Node(TVal& val, const TKey& key) {
        val_ = std::is_move_assignable<TVal>::value ? std::move(val):val;
        key_ = key;
        hash_ = Hasher(key);
    };

    Node(const Node& node) = delete;
    Node(Node&& node) = delete;
    Node& operator=(const Node& node) = delete;
    Node& operator=(Node&& node) = delete;

    ~Node() = default;
};



template<typename TVal, typename TKey> requires hashable<TKey>
class SkipList {
public:
    Node<TVal, TKey>* dummy_head_;

    unsigned int max_level_;    // the highest level that current nodes reach

    SkipList() {
        dummy_head_ = new Node<TVal, TKey>;
        max_level_ = 0;
    };

    SkipList(const SkipList& sl) = delete;

    SkipList(SkipList&& sl) noexcept {
        dummy_head_ = sl.dummy_head_;
        sl.dummy_head_ = nullptr;
        max_level_ = sl.max_level_;
    }

    SkipList& operator=(SkipList&& sl) noexcept {
        dummy_head_ = sl.dummy_head_;
        sl.dummy_head_ = nullptr;
        max_level_ = sl.max_level_;
        return *this;
    };

    SkipList& operator=(const SkipList& sl) = delete;

    ~SkipList() {
        delete dummy_head_;
    };


    static unsigned int LevelGenerator() {
        static std::random_device rd;
        static std::mt19937 generator(rd());
        static std::uniform_real_distribution<double> distribution(-1.0, 1.0);
        unsigned int level = 0;
        while (distribution(generator) < 0 && level<=LV_LIMIT)
            level++;
        return level;
    };


    void Insert(TVal& val, const TKey& key) {
        if(Find(key)!= nullptr)
            return;
        Node<TVal, TKey>* node = static_cast<Node<std::string, std::string> *>(new Node{val, key});
        unsigned int level = LevelGenerator();     // level represents the top level this node reaches
        if(max_level_<level)
            max_level_ = level;
        Node<TVal, TKey>* curr_node = dummy_head_;
        std::size_t hash = Hasher(key);
        for(int i=level; i>=0; i--) {
            while(curr_node->next_nodes_[i] && curr_node->next_nodes_[i]->hash_<node->hash_)
                curr_node = curr_node->next_nodes_[i];
            node->next_nodes_[i] = curr_node->next_nodes_[i];
            curr_node->next_nodes_[i] = node;
        }
    };


    void Delete(const TKey& key) {
        Node<TVal, TKey>* curr_node = dummy_head_;
        std::size_t hash = Hasher(key);
        Node<TVal, TKey>* node_to_delete = nullptr;
        for(int i=max_level_; i>=0; i--) {
            while(curr_node->next_nodes_[i] && curr_node->next_nodes_[i]->hash_<hash)
                curr_node = curr_node->next_nodes_[i];
            if(curr_node->next_nodes_[i] && curr_node->next_nodes_[i]->hash_==hash) {
                if(!node_to_delete)
                    node_to_delete = curr_node->next_nodes_[i];
                curr_node->next_nodes_[i] = curr_node->next_nodes_[i]->next_nodes_[i];
            }
        }
        delete node_to_delete;
        while(max_level_>0 && !dummy_head_->next_nodes_[max_level_])
            max_level_--;
    };


    Node<TVal, TKey>* Find(const TKey& key) const {
        Node<TVal, TKey>* curr_node = dummy_head_;
        std::size_t hash = Hasher(key) ;
        for(int i=max_level_; i>=0; i--) {
            while(curr_node->next_nodes_[i] && curr_node->next_nodes_[i]->hash_<hash)
                curr_node = curr_node->next_nodes_[i];
            if(curr_node->next_nodes_[i] && curr_node->next_nodes_[i]->hash_==hash)
                return curr_node->next_nodes_[i];
        }
        return nullptr;
    };


    void PrintAll() const requires printable<TKey> {
        Node<TVal, TKey>* curr_node = dummy_head_;
        while(curr_node->next_nodes_[0]) {
            std::cout << curr_node->next_nodes_[0]->key_ << " -> ";
            curr_node = curr_node->next_nodes_[0];
        }
        std::cout << std::endl;
    }


    void DeleteAll() {
        while(dummy_head_->next_nodes_[0])
            Delete(dummy_head_->next_nodes_[0]->key_);
    };

};

