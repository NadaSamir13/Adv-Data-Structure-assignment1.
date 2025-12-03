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

    // Helper functions
    void insertNonFull(Node * node, T key); // Insert when node is NOT full
    void split(Node* node, int childIndex); // Split a full child during insertion
};

template <typename T, int order>
void B_Tree<T, order>::split(Node* parent, int childIndex) {
    Node* fullChild = parent->child[childIndex];
    Node* newRight = new Node(fullChild->is_leaf);

    int mid = (order - 1) / 2;

    int j = 0;
    for (int k = mid + 1; k < order - 1; k++) {
        newRight->keys[j++] = fullChild->keys[k];
    }
    newRight->keyCount = j;

    if (!fullChild->is_leaf) {
        for (int k = mid + 1; k < order; k++) {
            newRight->child[k - (mid + 1)] = fullChild->child[k];
            fullChild->child[k] = nullptr;
        }
    }

    fullChild->keyCount = mid;

    for (int k = parent->keyCount; k >= childIndex + 1; k--) {
        parent->child[k + 1] = parent->child[k];
    }
    parent->child[childIndex + 1] = newRight;

    for (int k = parent->keyCount - 1; k >= childIndex; k--) {
        parent->keys[k + 1] = parent->keys[k];
    }
    parent->keys[childIndex] = fullChild->keys[mid];
    parent->keyCount++;
}

template <typename T, int order>
void B_Tree<T, order>::insertNonFull(B_Tree::Node *node, T key)
{
    /*
       This function inserts a key into a node that is guaranteed NOT to be full.
       Two scenarios:

       1) If node is LEAF → insert key into correct sorted position.
       2) If node is INTERNAL:
            - Determine which child to descend into.
            - If that child is full → split it first.
            - After split, determine correct child and continue insertion.
    */


    int count = node->keyCount - 1;
    // Case 1: Leaf node → Insert directly into sorted position
    if(node->is_leaf)
    {
        while (count >= 0) {
            if (node->keys[count] > key) {
                node->keys[count + 1] = node->keys[count];
                count--;
            }
            else
                break;
        }
        node->keys[count + 1] = key;
        node->keyCount++;
    }

    // Case 2: Internal node → Find correct child to descend into
    else
    {
        // Locate child index to descend
        while(count >= 0 && node->keys[count] > key)
            count--;
        count++; // count = correct child index

        // If child is full → MUST split before insertion
        if(node->child[count]->keyCount == order - 1)
        {
            split(node, count);

            // After split, check which of the two children should receive the key
            if(key > node->keys[count])
                count++;
        }

        // Recursive insert into correct child
        insertNonFull(node->child[count], key);
    }
}

template <typename T, int order>
void B_Tree<T, order>::insert(T key)
{
    /*
      Main insertion logic:
      1) If tree is empty → create root as leaf and insert key.
      2) If root is full → split it first (special case).
      3) Otherwise → insertNonFull(root)
   */

    // Case 1: Tree is empty: create root
    if(root == NULL)
    {
        root = new Node(true);
        root->keys[0] = key;
        root->keyCount++;
        return;
    }

    // Case 2: root is Full: (Split needed)
    if (root->keyCount == order - 1)
    {
        Node* newRoot = new Node(false);
        newRoot->child[0] = root;

        split(newRoot, 0);

        // Determine which child of new root will receive the key
        int i = 0;
        if (key > newRoot->keys[0])
            i++;

        insertNonFull(newRoot->child[i], key);

        root = newRoot;
    }

    // Case 3: Root not full → normal insert
    else
    {
        insertNonFull(root, key);
    }
}

int main () {
    return 0;
}