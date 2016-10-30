/*
*Create by liujun 20161026.
*Avl tree
*/
#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

//AVL数节点信息
template<class T>
class avlTreeNode{
public:
    avlTreeNode(T x,int h=0):data(x),height(h),lson(NULL),rson(NULL){
    }
    T data;
    int height;
    avlTreeNode *lson;
    avlTreeNode *rson;
};

/*avl 树的属性和方法*/
template<class T>
class avlTree{
    #define treeMax(n) \
           n->height = max(getAvlTreeHeight(n->lson),getAvlTreeHeight(n->rson))+1
public:
    //默认函数
    avlTree(avlTreeNode<T> *ptr):root(ptr){
    }
    void avlTreeInsert(T x);
    void avlTreeDelete(T x);
    void avlTreeTraversal();
    avlTreeNode<T> *avlTreeFind(T x);

private:
    avlTreeNode<T> *root;
    void insert(T x,avlTreeNode<T>* &node);
    void deleteNode(T x,avlTreeNode<T>* &node);
    avlTreeNode<T> * find(T x,avlTreeNode<T> *node);
    void inOrderTraversal(avlTreeNode<T> *root);
    void preOrderTraversal(avlTreeNode<T> *root);
    void posOrderTraversal(avlTreeNode<T> *root);
    int getAvlTreeHeight(avlTreeNode<T> *node);

    void singRotateLeft(avlTreeNode<T>* &n);
    void singRotateRight(avlTreeNode<T>* &n);
    void doubleRotateLR(avlTreeNode<T>* &n);
    void doubleRotateRL(avlTreeNode<T>* &n);
};

template<class T>
int avlTree<T>::getAvlTreeHeight(avlTreeNode<T> *node){
    if(node){
        return node->height;
    }
    return -1;
}

template<class T>
void avlTree<T>::singRotateLeft(avlTreeNode<T>* &n)
{
    avlTreeNode<T>* n2 = n->lson;
    n->lson = n2->rson;
    n2->rson = n;

    treeMax(n);
    treeMax(n2);
    n = n2;
    return;
}

template<class T>
void avlTree<T>::singRotateRight(avlTreeNode<T>* &n)
{
    avlTreeNode<T>* n2 = n->rson;
    n->rson = n2->lson;
    n2->lson = n;

    treeMax(n);
    treeMax(n2);
    n = n2;
    return;
}

template<class T>
void avlTree<T>::doubleRotateLR(avlTreeNode<T>* &n)
{
    singRotateRight(n->lson);
    singRotateLeft(n);
    return;
}

template<class T>
void avlTree<T>::doubleRotateRL(avlTreeNode<T>* &n)
{
    singRotateLeft(n->rson);
    singRotateRight(n);
    return;
}

template<class T>
void avlTree<T>::insert(T x,avlTreeNode<T>* &node){

    //找到了节点，并未此节点分配内存，并在节点中保存数据
    if(NULL == node){
        node = new avlTreeNode<T>(x);
        return;
    }

    if(node->data>x){
        insert(x,node->lson);

        /*树出现了不平衡，需要旋转*/
        if(2 == (getAvlTreeHeight(node->lson)-getAvlTreeHeight(node->rson))){
            if(x<node->lson->data){
                singRotateLeft(node);
            }
            else{
                doubleRotateLR(node);
            }
        }
    }
    else if(node->data < x){
        insert(x,node->rson);

        /*树出现了不平衡，需要旋转*/
        if(2 == (getAvlTreeHeight(node->rson)-getAvlTreeHeight(node->lson))){
                cout << node->lson->data <<endl;
            if(x>node->rson->data){
                singRotateRight(node);
            }
            else{
                doubleRotateRL(node);
            }
        }
    }

    treeMax(node);
    return;
}

template<class T>
void avlTree<T>::avlTreeInsert(T x){
    insert(x,root);
    return;
}

template<class T>
void avlTree<T>::inOrderTraversal(avlTreeNode<T> *root){
    stack<avlTreeNode<T> *> s;

    while(1){
        if(root){
            s.push(root);
            root = root->lson;
        }
        else{
            if(s.empty())break;
            root = s.top();
            cout << root->data << "";
            s.pop();
            root = root->rson;
        }
    }
    return;
}

template<class T>
void avlTree<T>::avlTreeTraversal(){
    inOrderTraversal(root);
    return;
}

avlTreeNode<int> *create(){
    avlTreeNode<int> *a = new avlTreeNode<int>(6,2);
    avlTreeNode<int> *b = new avlTreeNode<int>(2,1);
    avlTreeNode<int> *c = new avlTreeNode<int>(7);
    avlTreeNode<int> *d = new avlTreeNode<int>(1);
    avlTreeNode<int> *e = new avlTreeNode<int>(4);

    a->lson = b;
    a->rson = c;
    b->lson = d;
    b->rson = e;

    return a;
}

int main()
{
    avlTreeNode<int> *root = create();
    avlTree<int> avl(root);

    avl.avlTreeTraversal();
    cout << endl;
    avl.avlTreeInsert(3);
    avl.avlTreeTraversal();

    return 0;
}

/*
void avlTree<T>::deleteNode(T x,avlTreeNode<T>* &node){
}

avlTreeNode<T> *avlTree<T>:: find(T x,avlTreeNode<T> *node){
}

void avlTree<T>::inOrderTraversal(avlTreeNode<T> *root){
}

void avlTree<T>::preOrderTraversal(avlTreeNode<T> *root){
}
void avlTree<T>::posOrderTraversal(avlTreeNode<T> *root){
}
*/
