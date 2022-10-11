//
// Created by erikr on 5/10/2021.
//

#pragma once

#include <memory>

template <typename Key, typename Value=Key>
class AVLTree {
public:
    class Node {
    private:
        Key key_;
        Value value_;
        int balance_factor_, height_;
        Node *left_, *right_;
        Node(const Key& key) : key_(key), height_(0) {}
        Node(const Key& key, const Value& value) : key_(key), value_(value), height_(0) {}

         void print(int depth = 0) const {
             if (right_ != nullptr)
             {
                right_->print(depth + 1);
             }
             for (int i = 0; i < depth; ++i)
             {
                std::cout << "  ";
             }
             std::cout << key_ << ": " << value_ << " (bf: " << balance_factor_ << ")" << " (ht: " << height_ << ")" << std::endl;

             if (left_ != nullptr)
             {
                left_->print(depth + 1);
             }
        }

    public:
        // All these getter methods are O(1)
        Node *left() {
            return left_;
        }
        Node *right() {
            return right_;
        }
        const Key& key()  {
            return key_;
        }
        const Value& value()  {
            return value_;
        }
        const int balance_factor()  {
            return balance_factor_;
        }

        friend class AVLTree<Key, Value>;
    };
// class AVLTree
private:
    Node *root_;
    int size_;

    void insert( const Key && new_key, const Value && new_value, Node * & node)
    {
        if(node == nullptr)
        {
            node = new Node(new_key,new_value);
            balance();
            ++size_;
        }

        else if (new_key < node->key_)
        {
            insert(new_key,new_value,node->left_);
        }

        else if (new_key > node->key_)
        {
            insert(new_key,new_value,node->right_);
        }
        std::cout << "balance" << std::endl;
        balance(node);
        std::cout << "after balance" << std::endl;
    }

//    void insert(const Key && k, const Value && v)
//    {
//        insert(k,v,root_);
//    }
//
//    void insert(const Key && k)
//    {
//        Node newNode = new Node(k);
//        insert(k,newNode.value_);
//    }


public:
    AVLTree() : root_(nullptr), size_(0){}

    // TODO: Add code to update the balance factor and do rebalancing...

    static const int ALLOWED_IMBALANCE = 1;


    bool isEmpty() const
    {
        return root_ == nullptr;
    }

    void print()
    {
         if (root_ != nullptr)
         {
            root_->print();
         }
    }

    void balance(Node * & node)
    {
        if ( node == nullptr )
            return;

        node->balance_factor_ = height( node->left_ ) - height( node->right_ );

        if (node->balance_factor_ > ALLOWED_IMBALANCE )
        {
            if (height( node->left_->left_) >= height(node->left_->right_))
            {
                rotateWithLeftChild(node);
            }
            else
            {
                doubleWithLeftChild(node);
            }
        }
        else
        {
            node->balance_factor_ = height( node->right_ ) - height( node->left_ );

            if (node->balance_factor_ > ALLOWED_IMBALANCE)
            {
                if (height(node->right_->right_) >= height(node->right_->right_))
                {
                    rotateWithRightChild(node);
                }
                else
                {
                    doubleWithRightChild(node);
                }

            }
        }
        node->height_ = max(height(node->left_), height(node->right_)) + 1;
    }

//    Value& operator[](const Key& k)
//    {
//        Node *cur;
//        for (cur = root_;
//             cur != nullptr;
//             cur = k < (*cur).key_ ? (*cur).left_ : (*cur).right_) {
//        if (k == (*cur).key_) {
//            return (*cur).value_;
//        } else if (k < (*cur).key_) {  // Need to insert to the left
//            if ((*cur).left_ == nullptr) {
//                --(*cur).balance_factor_;
//                (*cur).left_ = new Node(k);
//                return (*cur).left_->value;
//            } else {
//                int prev_left_bf = (*cur)->balance_factor_;
//                auto& result = (*cur).left_[k];
//                int cur_left_bf = (*cur).left_->balance_factor;
//                // if the left subtree is bigger after the insert ...
//                if (abs(cur_left_bf) > abs(prev_left_bf)) {
//                    --(*cur).balance_factor_;
//                }
//                return result;
//            }
//        } else { // if (k > key)  Need to insert to the right
//            if ((*cur).right_ == nullptr) {
//                ++(*cur).balance_factor_;
//                (*cur).right_ = new Node(k);
//                return (*cur).right_->value;
//            } else {
//                    int prev_right_bf = (*cur).right_->balance_factor;
//                    auto& result = (*cur).right_[k];
//                    int cur_right_bf = (*cur).right_->balance_factor;
//                    // if the right subtree is bigger after the insert ...
//                    if (abs(cur_right_bf) > abs(prev_right_bf)) {
//                        ++(*cur).balance_factor_;
//                    }
//                    return result;
//                }
//            }
//        }
//    }

    //This overloaded operator method is O(log(size()))
    Value& operator[](const Key& key) {

        // Try to find the node with the value we want:
        Node *cur;
        for (cur = root_;
             cur != nullptr;
             cur = key < (*cur).key_ ? (*cur).left_ : (*cur).right_) {
            if (key == (*cur).key_) {
                return (*cur).value_;

            }
        }
        // If we didn't find it, insert a new node with that key:
        // (This is the same behaviour as an std::map.)
        cur = new Node(key);
        //balance(cur);
        ++size_;
        return (*cur).value_;
    }

    int size() {
        return size_;
    }

    Node *root() {
        return root_;
    }

    int height( Node *rootOfSubtree ) const
    {
        return rootOfSubtree == nullptr ? -1 : rootOfSubtree->height_;
    }

    int max(int lhs, int rhs) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    //-----------//
    // ROTATIONS //
    //-----------//

    void rotateWithLeftChild(Node * & k2)
    {
        Node *k1 = k2->left_;
        k2->left_ = k1->right_;
        k1->right_ = k2;
        k2->height_ = max(height( k2->left_ ), height( k2->right_ ) ) + 1;
        k1->height_ = max(height( k1->left_), k2->height_ ) + 1;
        k2 = k1;
    }

    void rotateWithRightChild(Node * & k1)
    {
        Node *k2 = k1->right_;
        k1->right_ = k2->left_;
        k2->left_ = k1;
        k1->height_ = max(height( k1->left_ ), height( k1->right_)) + 1;
        k2->height_ = max(height( k2->right_), k1->height_) + 1;
        k1 = k2;
    }

    void doubleWithLeftChild(Node * & k3)
    {
        rotateWithRightChild(k3->left_);
        rotateWithLeftChild(k3);
    }

    void doubleWithRightChild(Node * & k1)
    {
        rotateWithLeftChild(k1->right_);
        rotateWithRightChild(k1);
    }

};