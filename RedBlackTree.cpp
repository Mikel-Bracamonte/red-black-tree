#include <iostream>
#include <vector>
using namespace std;

template <typename T>
struct RBNode {
    T data;
    RBNode* left = nullptr;
    RBNode* right = nullptr;

    //true significa rojo
    bool color = true;

    RBNode(T data) : data(data) {}
};

template <typename T>
class RBTree {
private:
    RBNode<T>* root = nullptr;

    bool getColor(RBNode<T>* node) {
        if(node == nullptr) {
            return false;
        }

        return node->color;
    }

    int auxHeight(RBNode<T>* root) {
        if(root == nullptr) {
            return -1;
        }

        return max(auxHeight(root->left), auxHeight(root->right)) + 1;
    }

    RBNode<T>* rightRotate(RBNode<T>* y) {
        RBNode<T>* x = y->left;
        y->left = x->right;
        x->right = y;

        return x;
    }

    RBNode<T>* leftRotate(RBNode<T>* x) {
        RBNode<T>* y = x->right;
        x->right = y->left;
        y->left = x;

        return y;
    }

    bool auxSearch(RBNode<T>* node, T key) {
        if(node == nullptr) {
            return false;
        }

        if(node->data == key) {
            return true;
        }

        if(key < node->data) {
            return auxSearch(node->left, key);
        } else {
            return auxSearch(node->right, key);
        }
    }

    RBNode<T>* auxInsert(RBNode<T>* node, T key) {
        if(node == nullptr) {
            node = new RBNode<T>(key);
            return node;
        }

        if(key < node->data) {
            node->left = auxInsert(node->left, key);
        } else {
            node->right = auxInsert(node->right, key);
        }

        //Solo los nodos negros serán los encargados de verificar y hacer rotaciones en caso sea necesario
        if(!getColor(node)) {
            //El nodo izquierdo es rojo
            if(getColor(node->left)) {
                //El nodo izquierdo del izquierdo es rojo
                if(getColor(node->left->left)) {
                    node = rightRotate(node);
                    node->left->color = false;
                }
                //El nodo derecho del izquierdo es rojo
                if(getColor(node->left->right)) {
                    node->left = leftRotate(node->left);
                    node = rightRotate(node);
                    node->left->color = false;
                }
            }

            //El nodo derecho es rojo
            if(getColor(node->right)) {
                //El nodo derecho del derecho es rojo
                if(getColor(node->right->right)) {
                    node = leftRotate(node);
                    node->right->color = false;
                }
                //El nodo izquierdo del derecho es rojo
                if(getColor(node->right->left)) {
                    node->right = rightRotate(node->right);
                    node = leftRotate(node);
                    node->right->color = false;
                }
            }
        }

        return node;
    }

    void auxPreorder(RBNode<T>* root, vector<T>& vec) {
        if(root == nullptr) {
            return;
        }
        vec.push_back(root->data);
        auxPreorder(root->left, vec);
        auxPreorder(root->right, vec);
    }

    void auxInorder(RBNode<T>* root, vector<T>& vec) {
        if(root == nullptr) {
            return;
        }
        auxInorder(root->left, vec);
        vec.push_back(root->data);
        auxInorder(root->right, vec);
    }

    void auxPostorder(RBNode<T>* root, vector<T>& vec) {
        if(root == nullptr) {
            return;
        }
        auxPostorder(root->left, vec);
        auxPostorder(root->right, vec);
        vec.push_back(root->data);
    }

    int auxVerifyConstraints(RBNode<T>* root, int& blackNodes, int currentBlackNodes) {
        if(root == nullptr) {
            if(blackNodes == -1) {
                blackNodes = currentBlackNodes;
            }
            return blackNodes == currentBlackNodes;
        }
        if(!getColor(root)) {
            ++currentBlackNodes;
        } else {
            if(getColor(root->left) || getColor(root->right)) {
                return -1;
            }
        }

        return auxVerifyConstraints(root->left, blackNodes, currentBlackNodes) && auxVerifyConstraints(root->right, blackNodes, currentBlackNodes);
    }

public:
    void insert(T key) {
        root = auxInsert(root, key);
        if(root != nullptr) {
            root->color = false;
        }
    }

    void remove(T key) {

    }

    bool search(T key) {
        return auxSearch(root, key);
    }

    int height() {
        return auxHeight(root);
    }

    vector<T> preorder() {
        vector<T> res;
        auxPreorder(root, res);
        return res;
    }

    vector<T> inorder() {
        vector<T> res;
        auxInorder(root, res);
        return res;
    }

    vector<T> postorder() {
        vector<T> res;
        auxPostorder(root, res);
        return res;
    }

    bool verifyConstraints() {
        int blackNodes = -1;
        return auxVerifyConstraints(root, blackNodes, 0) && !getColor(root);
    }
};

int main() {

    srand(time(nullptr));

    RBTree<int> rbTree;

    for(int i = 0; i < 10000; i++) {
        int random = rand() % 10000 - 5000;
        cout << "Insertando " << random << endl;
        rbTree.insert(random);
    }

    rbTree.insert(100);

    vector<int> vec = rbTree.inorder();

    for(int i : vec) {
        cout << i << " ";
    }

    cout << endl << "Altura: " << rbTree.height() << endl;

    cout << (rbTree.verifyConstraints() ? "Cumple las restricciones de un red-black tree" : "No cumple las restricciones de un red-black tree") << endl;

    cout << (rbTree.search(100) ? "Si existe 100" : "No existe 100") << endl;

    return 0;
}