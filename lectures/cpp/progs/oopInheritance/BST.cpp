//#include <iostream>
//using namespace std;
//
//class BST {
//    int data;
//    BST* left, * right;
//
//public:
//    BST();
//    BST(int);
//    BST* Insert(BST*, int);
//    void Inorder(BST*);
//};
//
//
//BST::BST()
//    : data(0)
//    , left(NULL)
//    , right(NULL)
//{
//}
//
//BST::BST(int value)
//{
//    data = value;
//    left = right = NULL;
//}
//
//BST* BST::Insert(BST* root, int value)
//{
//    if (!root) {
//        return new BST(value);
//    }
//
//    if (value > root->data) {
//        root->right = Insert(root->right, value);
//    }
//    else if (value < root->data) {
//        root->left = Insert(root->left, value);
//    }
//
//    return root;
//}
//
//void BST::Inorder(BST* root)
//{
//    if (!root) {
//        return;
//    }
//    Inorder(root->left);
//    cout << root->data << " ";
//    Inorder(root->right);
//}
//
//// Driver code
//int main()
//{
//    BST b, * root = NULL;
//    root = b.Insert(root, 59);
//    b.Insert(root, 100);
//    b.Insert(root, 75);
//    b.Insert(root, 30);
//    b.Insert(root, 16);
//    b.Insert(root, 45);
//    b.Insert(root, 250);
//
//    b.Inorder(root);
//    return 0;
//}