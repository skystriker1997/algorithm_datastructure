Requirements of a binary search tree are as below: 

The left subtree of a node contains only nodes with keys less than the node's key.

The right subtree of a node contains only nodes with keys greater than the node's key.

Given these, how to validate a binary search tree. 

From the angle of any indiviual node in the binary tree, the key of the right node and left node of current node should comply constraints, which are determined by the nearest forefather node located to the left of current node, the nearest forefather node located to the right of current node and the current node. 

I use nearest_fn__right to represent the nearest forefather node located to the right of current node, nearest_fn_left to represent the nearest forefather node located to the left of current node, and root to represent the current node. 

The key of  root's left child node should be less than that of root, but greater than that of nearest_fn_left, as both root and root->left are in the right subtrees of nearest_fn_left.

The key of  root's right child node should be greater than that of root, but less than that of nearest_fn_right, because both root and root->right are in the left subtrees of nearest_fn_right.

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

   														

How to build up a height-balanced binary search tree, based on a sorted array?

The essential function of the binary search tree is to divide a group of numbers into two parts, where the least one of right part should be greater than the largest one of the left part. In order to make the tree be balanced, I always evenly divide the given group. For example, if I want to add left and right child nodes for root, with left border(l), right border(r) and current index(c), the left child node should be the middle(l, c-1), and the right child node should be middle(c+1, r)

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

 Since every node in a binary search tree works as a watershed, it's easy to insert an element into the tree. 

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

When it comes to deleting a node from the binary search tree, the most complicated case happens when the node has both right node and left node. I use the least one of right subtree or the largest one of left subtree, to take the place of the deleted node. 

[LeetCode 450 Delete Node in a BST](https://leetcode.com/problems/insert-into-a-binary-search-tree/) 

```cpp
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        TreeNode* dummy = new TreeNode(); 
        dummy->right = root;
        gothrough(root, key, dummy, true);
        return dummy->right;
    }

    void replace(TreeNode* root, TreeNode* p, bool right) {
        if (root->right && root->left) {
          // find out what's the largest node of the left subtree
            if (!root->left->right) {   // in this case, root->left
                root->val = root->left->val;
                root->left = root->left->left?root->left->left:nullptr;
            } else {
                TreeNode* front = root->left->right;
                TreeNode* p = root->left;
                while (front->right) {
                    p = front;
                    front = front->right;
                }
                root->val = front->val;
                if (front->left) {
                    p->right = front->left;
                } else {
                    p->right = nullptr;
                }
            }
        } else if(root->left) {
            if (right) {
                p->right = root->left;
            } else {
                p->left = root->left;
            }
        } else if(root->right) {
            if (right) {
                p->right = root->right;
            } else {
                p->left = root->right;
            }
        } else {
            if (right) {
                p->right = nullptr;
            } else {
                p->left = nullptr;
            }
        }
    }

    void gothrough(TreeNode* root, const int& key, TreeNode* p, bool right) {
        if (!root) {
            return;
        }
        if (root->val == key) {
            replace(root, p, right);
        } else {
            gothrough(root->right, key, root, true);
            gothrough(root->left, key, root, false);
        }
    }
};
```

