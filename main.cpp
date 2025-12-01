#include <bits/stdc++.h>
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
        int keyCount1;
        bool is_leaf;

        Node(bool leaf)
        {
            is_leaf= leaf;
            keyCount1 = 0;
            for(int p = 0; p < order; p++)
            {
                child[p] = NULL;
            }
        }
    };

    Node* ro;

public:

    B_Tree()
    {
        ro = NULL;
    }

    /*void Insert(T value);
    void Print();
    void InsertNonFull(Node* node, T value);
    void SplitChild(Node* parent, int index);
    void Print(Node* node, int level);*/
};


int main () {
    return 0;
}
