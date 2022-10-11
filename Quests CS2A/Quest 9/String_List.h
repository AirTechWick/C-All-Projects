// Student ID: 20342635
//
// String_List.h
//
// 2a-Lab
#ifndef String_List_h
#define String_List_h

#include <iostream>
#include <sstream>

class String_List {
    private:
        struct Node {
            std::string data;
            Node *next;
            Node(std::string s = "") : data(s), next(nullptr){}
        };

        Node *_head, *_tail, *_prev_to_current;

        size_t _size = 0;

    public:
        String_List(){
            _head = new Node("_SENTINEL_");
            _tail = _head;
            _prev_to_current = _head;
        }

        ~String_List(){
            clear();
            delete _head;
        }

        size_t get_size() const{
            return _size;
        }

        void clear(){
            while(_head->next != nullptr)
            {   
                Node *savedNode = _head->next;
                _head->next = savedNode->next;
                delete savedNode;
            }
            _size = 0;
            _prev_to_current = _head;
            _tail = _head;
            _head->next = nullptr;
        }

        String_List *rewind(){
            _prev_to_current = _head;
            return this;
        }

        String_List *insert_at_current(std::string s){
            _size++;
            Node *insertedNode = new Node(s);
            Node *currentNode = _prev_to_current->next;
            insertedNode->next = currentNode;
            _prev_to_current->next = insertedNode;
            if(_tail == _prev_to_current)
                _tail = insertedNode;
            return this;
        }

        String_List *remove_at_current(){
            _size--;
            Node * currentNode = _prev_to_current->next;
            _prev_to_current->next = currentNode->next;
            delete currentNode;
            return this;
        }

        String_List *push_front(std::string s){
            Node *savedNode = _prev_to_current;
            _prev_to_current = _head;
            insert_at_current(s);
            _prev_to_current = savedNode;
            return this;
        }

        String_List *push_back(std::string s){
            Node *currentPrevNode = _prev_to_current;
            _prev_to_current = _tail;
            insert_at_current(s);
            _tail = _prev_to_current->next;
            _prev_to_current = currentPrevNode;
            return this;
        }

        String_List *advance_current(){
            if (_prev_to_current == _tail)
            {
                return nullptr;
            }
            
            _prev_to_current = _prev_to_current->next;
            
            return this;
        }

        std::string get_current() const{
            if(_prev_to_current != nullptr)
            {
                return _prev_to_current->next->data;
            }

            else
            {
                return  "_SENTINEL_";
            }
        }

        std::string &find_item(std::string s) const{
            Node *searchNode = _head;
            while(searchNode!=nullptr)
            {
                if (searchNode->data == s)
                {
                    std::string &result1 = searchNode->data;
                    return result1;
                }
                searchNode = searchNode->next;
            }
            static std::string _SENTINEL_ = "_SENTINEL_";
            std::string& refSentinel = _SENTINEL_;
            return refSentinel;
        }

        std::string to_string() const{
            std::string stringResult1 = "";
            std::string stringResult2 = "String_List: <N> entries total. Starting at cursor:\n";
            std::string strConverted = "";
            Node* currentNode = _prev_to_current->next;
            bool firstElement = true;
            int count = 0;
            
            // Conversion
            std::ostringstream cnvrt1;
            cnvrt1 << _size;
            strConverted += cnvrt1.str();
            stringResult2.replace(13,3, strConverted); // replacing <N>

            while (currentNode) 
            {
                if (!firstElement)
                    stringResult1 += "\n";
                if (count == 25)
                    return stringResult2 += stringResult1 += "...";
                stringResult1 += currentNode->data;
                firstElement = false;
                currentNode = currentNode->next;
                count++;
            }
            return stringResult2 + stringResult1;
        }
        friend class Tests;
};

#endif /* String_List_h */