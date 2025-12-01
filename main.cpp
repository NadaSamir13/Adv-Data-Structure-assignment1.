#include <iostream>

using namespace std;
#define ll long long

template <typename T, int order>
class B_Tree
{
private:
    struct Node
    {
        T keys[order - 1];
        Node* child[order];
        int keyCount;
        bool is_leaf;

        Node(bool leaf)
        {
            is_leaf= leaf;
            keyCount = 0;
            for(int p = 0; p < order; p++)
            {
                child[p] = NULL;
            }
        }
    };
    Node* root;

public:
    B_Tree()
    {
        root = NULL;
    }
    void insert(T key);
    void split(Node* node, T key);
};

template <typename T, int order>
void B_Tree<T, order>::split(Node* node, T key)
{

}

template <typename T, int order>
void B_Tree<T, order>::insert(T key)
{
    //case1: root is empty:
    if(root == NULL)
    {
        root = new Node(true);
        root->keys[0] = key;
        root->keyCount++;
        return;
    }

    //case2: root not Full:
    if(root->keyCount < order - 1)
    {
        int count = root->keyCount - 1;
        while(count >= 0)
        {
            if(root->keys[count] > key)
            {
                root->keys[count + 1] = root->keys[count];
                count--;
            } else
                break;
        }
        root->keys[count + 1] = key;
        root->keyCount++;
        return;
    }

    //case3: root is Full: (Split)
    else
    {
       split(root, key);
    }
}


int main () {
    return 0;
}