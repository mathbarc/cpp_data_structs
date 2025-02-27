#include "binary_tree.hpp"

int main(int argc, char **argv)
{
    BinaryTree<int> data;

    data.insert(5);
    data.insert(10);
    data.insert(2);
    data.insert(20);

    data.inOrder();
    data.preOrder();
    data.postOrder();

    data.remove(10);
    data.inOrder();

    return 0;
}
