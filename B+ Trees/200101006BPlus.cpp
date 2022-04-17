#include <bits/stdc++.h>
using namespace std;
class Node
{
public:
    bool isLeaf;
    int degree;
    vector<pair<int, Node *>> key;
    Node *last;
    Node(int degree, bool isLeaf)
    {
        this->degree = degree;
        this->last = NULL;
        this->isLeaf = isLeaf;
    }
};
class Tree
{
    int d;
    int t;
    int numIndexNodes;
    int numDataNodes;
    Node *root;

public:
    Tree(int d, int t)
    {
        this->d = d;
        this->t = t;
        root = NULL;
        numIndexNodes = 0;
        numDataNodes = 0;
    }
    void insert(int x)
    {
        if (root == NULL)
        {
            root = new Node(d, true); // making a dataNode;
            numDataNodes++;
            root->key.push_back({x, NULL});
            // cout<<"From 1\n";
        }
        else if (root->isLeaf)
        {
            /*
                Two case arises -
                a) root is not full
                b) root is full
            */

            if (root->key.size() <= 2 * root->degree)
            {
                // first we have to find the correct position for the item to push
                int i;
                for (i = 0; i < root->key.size(); i++)
                {
                    if (root->key[i].first < x)
                        continue;
                    else
                        break;
                }
                if (i == root->key.size())
                    root->key.push_back({x, NULL});
                else
                    root->key.insert(root->key.begin() + i, {x, NULL});
                // cout<<"From 2\n";
            }
            else
            {
                Node *newNode = new Node(d, true); // making a new dataNode;
                numDataNodes++;
                for (int i = 0; i <= d; i++)
                {
                    pair<int, Node *> temp = root->key[root->key.size() - 1];
                    root->key.pop_back();
                    newNode->key.insert(newNode->key.begin(), temp);
                }
                root->last = newNode;
                int i;
                for (i = 0; i < newNode->key.size(); i++)
                {
                    if (root->key[i].first < x)
                        continue;
                    else
                        break;
                }
                newNode->key.insert(newNode->key.begin() + i, {x, NULL});
                Node *newIndex = new Node(t, false);
                numIndexNodes++;
                newIndex->key.push_back({newNode->key[0].first, root});
                newIndex->last = newNode;
                root = newIndex;
                // cout<<"From 3\n";
            }
        }
        else
        {
            // cout << "Root is not a leaf node\n";
            Node *cursor = root;
            while (!cursor->isLeaf)
            {
                for (int i = 0; i < cursor->key.size(); i++)
                {
                    if (x < cursor->key[i].first)
                    {
                        cursor = cursor->key[i].second;
                        break;
                    }
                    if (i == cursor->key.size() - 1)
                    {
                        cursor = cursor->last;
                        break;
                    }
                }
            }
            /*
                Two case arises again -
                a) cursor is not full
                b) cursor is full
            */
           if (cursor->key.size() <= 2 * cursor->degree)
            {
                // first we have to find the correct position for the item to push
                int i;
                for (i = 0; i < cursor->key.size(); i++)
                {
                    if (cursor->key[i].first < x)
                        continue;
                    else
                        break;
                }
                if (i == cursor->key.size())
                    cursor->key.push_back({x, NULL});
                else
                    cursor->key.insert(cursor->key.begin() + i, {x, NULL});
                // cout<<"From 2\n";
            }
            else
            {
                Node *newNode = new Node(d, true); // making a new dataNode;
                numDataNodes++;
                for (int i = 0; i <= d; i++)
                {
                    pair<int, Node *> temp = cursor->key[cursor->key.size() - 1];
                    cursor->key.pop_back();
                    newNode->key.insert(newNode->key.begin(), temp);
                }
                cursor->last = newNode;
                int i;
                for (i = 0; i < newNode->key.size(); i++)
                {
                    if (cursor->key[i].first < x)
                        continue;
                    else
                        break;
                }
                newNode->key.insert(newNode->key.begin() + i, {x, NULL});
                Node *newIndex = new Node(t, false);
                numIndexNodes++;
                newIndex->key.push_back({newNode->key[0].first, cursor});
                newIndex->last = newNode;
                cursor = newIndex;
                // cout<<"From 3\n";
            }


        }
    }
    void display()
    {
        cout << numIndexNodes << " " << numDataNodes << " ";
        // Node*temp= root;
        // while(temp->key[0].second!=NULL){
        //     temp = temp->key[0].second;
        // }
        // while(temp!=NULL){
        //     for(int i=0; i<temp->key.size(); i++){
        //         cout<<temp->key[i].first<<" ";
        //     }
        //     cout<<"\n";
        //     temp=temp->last;
        // }
        for (int i = 0; i < root->key.size(); i++)
        {
            cout << root->key[i].first << " ";
        }
        cout << "\n";
    }
};

int main()
{

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int d; // A leaf or data node has capacity to store 2d records. Each leaf node should contain at least d records, except when there is only one leaf node in the B+ tree.
    int t; // A non-leaf or index node has capacity to store 2t+1 keys. Each non-leaf node should contain at least t keys, except when there is only one non-leaf node in the B+ tree.
    cin >> d;
    cin >> t;
    int opcode, x;
    Tree T(d, t);
    while (true)
    {
        cin >> opcode;
        switch (opcode)
        {
        case 1:
        {
            cin >> x;
            T.insert(x);
        }
        break;
        case 2:
        {
            T.display();
        }
        break;
        case 3:
        {
            return 0;
        }
        }
    }
    // Tree T(2,1);
    // T.insert(10);
    // T.insert(20);
    // T.insert(30);
    // T.insert(40);
    // T.insert(50);
    // T.insert(60);
    // T.insert(70);
    // T.insert(80);
    // T.insert(90);
    // T.display();
}
