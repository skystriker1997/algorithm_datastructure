A binary search tree is a specialised binary tree added restrictions as below: 

1. The key of root is greater than that of any nodes from the left subtree.

2. The key of root is less than that of any nodes from the right subtree.

Given these, how can we validate a binary tree being a binary search tree?

For a root, although its left node should not only be less than it, but also be greater than the nearest forefather node of it which regards it as a member of right subtree and is named nearest_fn_left by me. Similarly, its right node should not only be greater than it, but also be less than the nearest forefather node of it which regards it as a member of left subtree and is named nearest_fn__right by me. 

[LeetCode 98 Validate Binary Search Tree](https://leetcode.com/problems/validate-binary-search-tree/)

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        bool result = recursive(root, true, nullptr, nullptr);
        return result;
    }

    bool recursive(TreeNode* root, bool fst, TreeNode* nearest_fn_right, TreeNode* nearest_fn_left) {
        if(!root) {
            return true;
        }

        bool right = true;
        bool left = true;

        if(root->left) {
            if(root->left->val >= root->val) {
                left = false;
            } 
            if(!fst) {
                if(nearest_fn_left) {
                    if(nearest_fn_left->val >= root->left->val) {
                        left = false;
                    }
                }
            }
        }

        if(root->right) {
            if(root->right->val <= root->val) {
                right = false;
            } 
            if(!fst) {
                if(nearest_fn_right) {
                    if(nearest_fn_right->val <= root->right->val) {
                        right = false;
                    }
                }
            }
        }

        if(left && right) {
            return recursive(root->left, false, root, nearest_fn_left) && recursive(root->right, false, nearest_fn_right, root);
        } else {
            return false;
        }

    }

};
```

   														

We invent the binary search tree to facilitate search, but only a binary search tree whose every node has left subtree and right subtree with very close height significantly helps to maintain the time complexity at O(log<sub>2</sub>N).

How to build up a height-balanced binary search tree based on a sorted array?

What should be done recursively is to select out the middle element of the sorted array to be the root, let the left part be the left subtree, let the right part be the right subtree. 

[LeetCode 108 Convert Sorted Array to Binary Search Tree](https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/)

```cpp
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        int len = nums.size();
        int m = (len-1)/2;
        TreeNode* root = new TreeNode(nums[m]);
        TreeNode* result = recursion(nums, 0, len-1, m, root);
        return result;
    }

    TreeNode* recursion(vector<int>& nums, int l, int r, int c, TreeNode* root) {
        if(c>l) {
            int lm = (l+c-1)/2;
            TreeNode* ln = new TreeNode(nums[lm]);
            root->left = recursion(nums, l, c-1, lm, ln);
        }

        if(c<r) {
            int rm = (r+c+1)/2;
            TreeNode* rn = new TreeNode(nums[rm]);
            root->right = recursion(nums, c+1, r, rm, rn);
        }

        return root;

    }
};
```

 Since every node in a binary search tree plays a role as a watershed, it's easy to traverse until the leaf node and then insert the element. 

[LeetCode 701 Insert into a Binary Search Tree](https://leetcode.com/problems/insert-into-a-binary-search-tree/)

```cpp
class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (root==nullptr) {
            root = new TreeNode(val);
            return root;
        }
        if (root->val > val) {
            if (root->left == nullptr) {
                root->left = new TreeNode(val);
            } else {
                insertIntoBST(root->left, val);
            }
        } else {
            if (root->right == nullptr) {
                root->right = new TreeNode(val);
            } else {
                insertIntoBST(root->right, val);
            }
        }
        return root;
    }
};
```

When it comes to deleting a node from the binary search tree, the most complicated case happens when the target node has both right node and left node. We can use the least element from the right subtree or the largest one from left subtree to take the place of the deleted node. 

[LeetCode 450 Delete Node in a BST](https://leetcode.com/problems/delete-node-in-a-bst/) 

```cpp
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        TreeNode* dummy = new TreeNode(); // make a dummy parent node for the root to facilitate processing
        dummy->right = root;
        gothrough(root, key, dummy, true);
        TreeNode* res = dummy->right?dummy->right:nullptr;  // if the original root has been deleted, just return nullptr
        delete dummy;   // release dummy before exiting
        return res;
    }

    void replace(TreeNode* root, TreeNode* p, bool right) {
      	TreeNode* replacement = nullptr;
        if (root->right && root->left) {
            if (!root->left->right) {   // in this case, root->left is the largest one among left subtree
              	replacement = root->left;
              	root->left->right = root->right;
            } else {
                TreeNode* front = root->left->right;
                TreeNode* parent = root->left;
                while (front->right) {  // iterate to find the largest one of left subtree by going right
                    parent = front;
                    front = front->right;
                }
              	replacement = front;
                parent->right = front->left;   // alter linkings
              	front->left = root->left;   
              	front->right = root->right;
            }
       } else if (root->left) {
            replacement = root->left;
       } else if (root->right) {
            replacement = root->right;
       }
       if (right) {
       			p->right = replacement;
       } else {
         		p->left = replacement;
       }
       delete root;  
    }

    void gothrough(TreeNode* root, const int& key, TreeNode* p, bool right) {
        if (!root) {
            return;
        }
        if (root->val == key) {
            replace(root, p, right);
        } else {
            gothrough(root->right, key, root, true);  // use right to record the relative direction
            gothrough(root->left, key, root, false);
        }
    }
};
```

Note that heavily deleting or inserting elements upon a balanced binary search tree is likely to corrupt its balance. That's why red-black tree is invented. 
