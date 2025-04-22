#include "copy_on_write_wrapper.hpp"
#include <cassert>
#include <string>
#include <vector>

int main()
{
    CoWWrapper<std::string> cowArray;

    // Keep track of original pointers for manual cleanup
    std::vector<std::string *> originalPayloads;

    // Add original payloads to the CoW array
    originalPayloads.push_back(new std::string("1"));
    cowArray.add(originalPayloads.back());

    originalPayloads.push_back(new std::string("2"));
    cowArray.add(originalPayloads.back());

    // Access and print the elements
    std::cout << "Element 0: " << *cowArray.get(0) << std::endl;
    std::cout << "Element 1: " << *cowArray.get(1) << std::endl;

    assert(cowArray.get(0) == originalPayloads[0]);
    assert(cowArray.get(1) == originalPayloads[1]);

    // Modify an element (triggers CoW)
    cowArray.write(1, "Modified-22");
    std::cout << "Element 2 (after modif): " << *cowArray.get(1) << std::endl;

    // Ensure the original payload remains unmodified
    std::cout << "Payload 2 (after modif): " << *originalPayloads[1] << std::endl;

    assert(cowArray.get(1) != originalPayloads[1]);
    assert(*cowArray.get(1) == "Modified-22");

    // Clean up original payloads
    for(auto payload : originalPayloads)
    {
        delete payload;
    }

    return 0;
}
