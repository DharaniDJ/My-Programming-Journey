
// Problem Link : https://leetcode.com/problems/serialize-and-deserialize-binary-tree/

// Preorder : O(n) time and O(n) space complexity
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream out;
        serialize(root,out);
        return out.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream in(data);
        return deseralize(in);
    }

private:
    
    void serialize(TreeNode* root, ostringstream &out){
        // The extraction operator will read until whitespace is reached or until the stream fails.

        if(!root) {
            out << "#" << ' ';
            return;
        }
        out << root->val << ' ';
        serialize(root->left,out);
        serialize(root->right,out);
    }
    
    TreeNode* deseralize(istringstream &in){
        string val;
        in >> val;
        if(val=="#")return nullptr;
        TreeNode* root = new TreeNode(stoi(val));
        root->left = deseralize(in);
        root->right = deseralize(in);
        
        return root;
    }
};

// Further Space Optimization

// In the above solution, we store the node value and the references to None child nodes, which means N⋅V+2N complexity,
// where V is the size of value. That is called natural serialization, and has was implemented above.

// The N⋅V component here is the encoding of values, can't be optimized further,
// but there is a way to reduce 2N part which is the encoding of the tree structure.

// The number of unique binary tree structures that can be constructed using n nodes is C(n),
// where C(n) is the nth Catalan number.

