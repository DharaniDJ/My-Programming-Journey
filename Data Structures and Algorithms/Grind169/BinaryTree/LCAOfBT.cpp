
// Problem Link : https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree

// Approach 1 (Recursion): O(n) time and O(n) space complexity
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root || root==p || root==q) return root;
        
        TreeNode* l = lowestCommonAncestor(root->left, p, q);
        TreeNode* r = lowestCommonAncestor(root->right, p, q);
        
        if(l && r) return root;
        if(r) return r;
        return l;
        
    }
};

// Approach 2(Iterative using parent pointers): O(n) time and O(n) space complexity
class Solution {
public:
    bool getAncestor(TreeNode* root, TreeNode* p, vector<TreeNode*> &res){
        if(!root) return false;
        res.push_back(root);
        if(root==p){
            return true;
        }
        if(getAncestor(root->left,p,res)){
            return true;
        }
        if(getAncestor(root->right,p,res)){
            return true;
        }
        res.pop_back();
        return false;
        
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        vector<TreeNode*> ancP;
        getAncestor(root,p,ancP);
        vector<TreeNode*> ancQ;
        getAncestor(root,q,ancQ);
        
        int i = 0;
        TreeNode *temp = NULL;
        while(i<ancP.size() && i<ancQ.size() && ancP[i]==ancQ[i]){
            temp = ancP[i];
            i++;
        }
        return temp;
    }
};

// Approach 3(Iterative without parent pointers): O(n) time and O(n) space complexity
// Java Solution

// Algorithm

// 1. Start with root node.

// 2. Put the (root, root_state) on to the stack. root_state defines whether
// one of the children or both children of root are left for traversal.

// 3. While the stack is not empty, peek into the top element of the stack
// represented as (parent_node, parent_state).

// 4. Before traversing any of the child nodes of parent_node we check if
// the parent_node itself is one of p or q.

// 5. First time we find either of p or q, set a boolean flag called one_node_found to True.
// Also start keeping track of the lowest common ancestors by keeping a note of the
// top index of the stack in the variable LCA_index. Since all the current elements
// of the stack are ancestors of the node we just found.

// 6.The second time parent_node == p or parent_node == q it means we have found both the
// nodes and we can return the LCA node.

// 7. Whenever we visit a child of a parent_node we push the (parent_node, updated_parent_state)onto the stack.
// We update the state of the parent since a child/branch has been visited/processed and accordingly the state changes.

// 8. A node finally gets popped off from the stack when the state becomes BOTH_DONE implying both left
// and right subtrees have been pushed onto the stack and processed. If one_node_found is True
// then we need to check if the top node being popped could be one of the ancestors of the found node.
// In that case we need to reduce LCA_index by one. Since one of the ancestors was popped off.

// Whenever both p and q are found, LCA_index would be pointing to an index in the stack which would
// contain all the common ancestors between p and q. And the LCA_index element has the lowest ancestor common between p and q.

class Solution {

    // Three static flags to keep track of post-order traversal.

    // Both left and right traversal pending for a node.
    // Indicates the nodes children are yet to be traversed.
    private static int BOTH_PENDING = 2;

    // Left traversal done.
    private static int LEFT_DONE = 1;

    // Both left and right traversal done for a node.
    // Indicates the node can be popped off the stack.
    private static int BOTH_DONE = 0;

    public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {

        Stack<Pair<TreeNode, Integer>> stack = new Stack<Pair<TreeNode, Integer>>();

        // Initialize the stack with the root node.
        stack.push(new Pair<TreeNode, Integer>(root, Solution.BOTH_PENDING));

        // This flag is set when either one of p or q is found.
        boolean one_node_found = false;

        // This is used to keep track of the LCA.
        TreeNode LCA = null;

        // Child node
        TreeNode child_node = null;

        // We do a post order traversal of the binary tree using stack
        while (!stack.isEmpty()) {

            Pair<TreeNode, Integer> top = stack.peek();
            TreeNode parent_node = top.getKey();
            int parent_state = top.getValue();

            // If the parent_state is not equal to BOTH_DONE,
            // this means the parent_node can't be popped off yet.
            if (parent_state != Solution.BOTH_DONE) {

                // If both child traversals are pending
                if (parent_state == Solution.BOTH_PENDING) {

                    // Check if the current parent_node is either p or q.
                    if (parent_node == p || parent_node == q) {

                        // If one_node_found was set already, this means we have found
                        // both the nodes.
                        if (one_node_found) {
                            return LCA;
                        } else {
                            // Otherwise, set one_node_found to True,
                            // to mark one of p and q is found.
                            one_node_found = true;

                            // Save the current top element of stack as the LCA.
                            LCA = stack.peek().getKey();
                        }
                    }

                    // If both pending, traverse the left child first
                    child_node = parent_node.left;
                } else {
                    // traverse right child
                    child_node = parent_node.right;
                }

                // Update the node state at the top of the stack
                // Since we have visited one more child.
                stack.pop();
                stack.push(new Pair<TreeNode, Integer>(parent_node, parent_state - 1));

                // Add the child node to the stack for traversal.
                if (child_node != null) {
                    stack.push(new Pair<TreeNode, Integer>(child_node, Solution.BOTH_PENDING));
                }
            } else {

                // If the parent_state of the node is both done,
                // the top node could be popped off the stack.
                // Update the LCA node to be the next top node.
                if (LCA == stack.pop().getKey() && one_node_found) {
                    LCA = stack.peek().getKey();
                }

            }
        }

        return null;
    }
}