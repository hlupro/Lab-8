
#include "binaryTree.h"

BinaryTree :: BinaryTree()
{
  root = new TreeNode;
  root->key = 1000;
  root->left = NULL;
  root->right = NULL;
  root->parent = NULL;
}

BinaryTree :: BinaryTree(int n)
{
  root = new TreeNode;
  root->key = n;
  root->left = NULL;
  root->right = NULL;
  root->parent = NULL;
}

BinaryTree :: TreeNode* BinaryTree :: search(TreeNode* x, int k)
{
  if (x == NULL || x->key == k)
  {
    return x;
  }
  if(k < x->key)
  {
    return search(x->left, k);
  }
  else
  {
    return search(x->right, k);
  }
}

BinaryTree :: TreeNode* BinaryTree :: minimum(TreeNode* x)
{
  while (x->left != NULL)
  {
    x = x->left;
  }
  return x;
}

BinaryTree :: TreeNode* BinaryTree :: maximum(TreeNode* x)
{
  while(x->right != NULL)
  {
    x = x->right;
  }
  return x;
}

BinaryTree :: TreeNode* BinaryTree :: sucessor(TreeNode* x)
{
  if (x->right != NULL)
  {
    return minimum(x->right);
  }
  TreeNode* y = x->parent;
  while(y != NULL && x == y->right)
  {
    x = y;
    y = y->parent;
  }
  return y;
}

void BinaryTree :: deleteNode(TreeNode* z)
{
  if(z->left == NULL)
  {
    transplant(z,z->right);
    delete z;
  }
  else if(z->right == NULL)
  {
    transplant(z,z->left);
    delete z;
  }
  else
  {
    TreeNode* y = minimum(z->right);
    if(y->parent != z)
    {
      transplant(y,y->right);
      y->right = z->right;
      y->right->parent = y;
      delete z;
    }
    transplant(z,y);
    y->left = z->left;
    y->left->parent = y;
    delete z;
  }
}

void BinaryTree :: transplant(TreeNode* u, TreeNode* v)
{
  if(u->parent == NULL)
  {
    root = v;
  }
  else if(u == u->parent->left)
  {
    u->parent->left = v;
  }
  else
  {
    u->parent->right = v;
  }
  if(v != NULL)
  {
    v->parent = u->parent;
  }
}

int BinaryTree :: getHeight(TreeNode* x)
{
  if(x == NULL)
  {
    return 0;
  }
  else
  {
    int left = getHeight(x->left);
    int right = getHeight(x->right);
    if (left > right)
    {
      return (left + 1);
    }
    else
    {
      return(right + 1);
    }
  }
}

void BinaryTree :: printLevel(TreeNode* x, int l)
{
  if(x == NULL)
  {
    return;
  }
  if(l == 1)
  {
    std::cout << x->key << " ";
  }
  else if(l > 1)
  {
    printLevel(x->left, l-1);
    printLevel(x->right, l-1);
  }
}

void BinaryTree :: insert(int n)
{
  TreeNode* z = new TreeNode;
  TreeNode* y = NULL;
  z->key = n;
  z->right = NULL;
  z->left = NULL;
  TreeNode* x = root;
  while (x != NULL)
  {
    y = x;
    if(z->key <= x->key)
    {
      x = x->left;
    }
    else
    {
      x = x->right;
    }
  }
  z->parent = y;
  if (y == NULL)
  {
    root = z;
  }
  else if(z->key < y->key)
  {
    y->left = z;
  }
  else
  {
    y->right = z;
  }
}

void BinaryTree :: getSearch(TreeNode* x, int k)
{
  std::cout << "Searching for a node in the tree with the key " << k  << "..."<< std::endl;
  if(search(x, k) != NULL)
  {
    std::cout << "Sucess! There exists a node in the tree with the key " << k << std::endl;
  }
  else
  {
    std::cout << "Failure. A node with the key " << k << " does not exist within the tree." << std::endl;
  }
}

void BinaryTree :: getMin(TreeNode* x)
{
  std::cout << "The minimum is " << minimum(x)->key << std::endl;
}

void BinaryTree :: getMax(TreeNode* x)
{
  std::cout << "The maximum is " << maximum(x)->key << std::endl;
}

BinaryTree ::TreeNode* BinaryTree :: getRoot()
{
  return root;
}

void BinaryTree :: getSucessor(int k)
{
  std::cout << "\nLooking for the sucessor of " << k << std::endl;
  TreeNode* y = search(root,k);
  if(y)
  {
    TreeNode* z = sucessor(y);
    if(sucessor(search(root,k)))
    {
      std::cout << "The sucessor of " << k << " is " << z->key << std::endl;
    }
    else
    {
      std::cout << k << " has no sucessor." << std::endl;
    }
  }
  else
  {
    std::cout << "Error.\n" << k << " does not exist in the tree and therefore a sucessor will not be found." << std::endl;
  }
}

void BinaryTree :: inorder(TreeNode* x)
{
  if(x != NULL)
  {
    inorder(x->left);
    std::cout << x->key << std::endl;
    inorder(x->right);
  }
}

void BinaryTree :: getDelete(int k)
{
  std::cout << "\nDeleting the node with the key " << k << std::endl;
  TreeNode* y = search(root, k);
  if(y)
  {
    std::cout << "Deleting " << k << " from the tree." << std::endl;
    deleteNode(y);
  }
  else
  {
    std::cout << "Error.\n" << k << "does not exist in the tree and therefore cannont be deleted." << std::endl;
  }
}

void BinaryTree :: print()
{
  int h = getHeight(root);
  for(int i = 1; i <= h; i++)
  {
    printLevel(root, i);
    std::cout << "\n";
  }
}

BinaryTree :: ~BinaryTree()
{
  while(root != NULL)
  {
    deleteNode(root);
  }
}
