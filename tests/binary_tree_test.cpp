#include "binary_tree.hpp"

int main(int argc, char **argv)
{
    BinaryTree<int> data;

    data.insert(5);
    data.insert(10);
    data.insert(2);
    data.insert(20);

    std::cout << "Height: " << data.height() << std::endl;

    data.inOrderPrint();
    data.preOrderPrint();
    data.postOrderPrint();

    data.remove(10);
    data.inOrderPrint();

    return 0;
}
