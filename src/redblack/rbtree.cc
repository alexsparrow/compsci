
#include <iostream>

template <typename KeyType, typename ValType>
class RedBlack {
    struct Node {
        KeyType key;
        ValType val;
        Node* left;
        Node* right;
        Node* p;
        bool red;
        
        Node(KeyType key, ValType val, bool red=false):
            key(key), val(val), red(red)
        {
        }
    };

    Node* sentinel_;
    Node* root_;

    public:
    RedBlack(){
        sentinel_ = new Node(0, 0, false);
        root_ = sentinel_;
    }

    void Insert(KeyType key, ValType val){
        Node* n = new Node(key, val);
        Node* x = root_;
        Node* y = sentinel_;
        
        std::cout << "Inserting key=" << key << " val=" << val << "\n";
        while(x != sentinel_){
           y = x;
           if (n->key < x->key){
               std::cout << n->key << " < " << x->key << " => left branch\n";
                x = x->left;
           }
           else {
               std::cout << n->key << " >= " << x->key << " => right branch\n";
               x = x->right;
           }
        }
        n->p = y;

        if(y == sentinel_){
            std::cout << "Tree was empty => insert root \n";
            root_ = n;
        }
        else if ( n->key < y->key ){
            std::cout << n->key << " < " << y->key << " => insert left\n";
            y->left = n;
        }
        else{
            std::cout << " => insert right\n";
            y->right = n;
        }
        n->left = sentinel_;
        n->right = sentinel_;
        n->red = true;
    }

    void Traverse(Node* root, int depth){
        for(int i=0; i<= depth; ++i) std::cout << " + ";
        std::cout << root << " key=" << root->key << " val=" << root->val << "\n";
        if(root->left != sentinel_) Traverse(root->left, depth + 1);
        if(root->right != sentinel_) Traverse(root->right, depth + 1);
    }

    void Traverse(){
        Traverse(root_, 0);
    }
};


int main(int argc, char** argv){
    RedBlack<int, int> rb;
    rb.Insert(1, 1);
    rb.Insert(2, 2);
    rb.Traverse();
}
