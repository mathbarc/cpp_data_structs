#include "binary_tree.hpp"

int main(int argc, char **argv)
{
    BinaryTree<int> data;

    data.insert(10);
    data.insert(2);
    data.insert(5);

    data.inOrder();

    return 0;
}
