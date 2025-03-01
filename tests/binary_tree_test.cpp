#include "binary_tree.hpp"
#include <chrono>
#include <random>

void test_simple_data()
{
    BinaryTree<int> data;

    data.insert(2);
    data.insert(5);
    data.insert(10);
    data.insert(20);

    data.inOrderPrint();
    data.preOrderPrint();
    data.postOrderPrint();

    data.remove(10);
    data.inOrderPrint();
}

void test_tree_rebalance()
{
    BinaryTree<int> data;

    for(int i = 0; i < 1000; i++)
    {
        data.insert(std::rand());
    }

    std::cout << "Height: " << data.height() << std::endl;
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    data.balance();
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::cout << "Rebalanced three in " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " us" << std::endl;
    std::cout << "Height after balancing: " << data.height() << std::endl;
}

int main(int argc, char **argv)
{
    test_simple_data();
    test_tree_rebalance();

    return 0;
}
