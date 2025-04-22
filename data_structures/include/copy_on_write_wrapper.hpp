#ifndef COWWRAPPER_H
#define COWWRAPPER_H

#include <iostream>
#include <stdexcept>
#include <vector>

// Copy-On-Write Wrapper
template <typename T> class CoWWrapper
{
  public:
    ~CoWWrapper()
    {
        // Clean up dynamically allocated CoW elements
        for(size_t i = 0; i < elements.size(); ++i)
        {
            if(isCopy[i])
            {
                delete elements[i];
            }
        }
    }

    // Add a new element to the array
    void add(T *element)
    {
        elements.push_back(element); // Store the pointer
        isCopy.push_back(false);     // Mark as not a copy
    }

    // Access an element (read-only)
    const T *get(size_t index) const
    {
        if(index >= elements.size())
        {
            std::cerr << "Index out of bounds." << std::endl;
            return nullptr;
        }
        return elements[index];
    }

    // TODO: Modify an element (triggers Copy-On-Write)
    void write(size_t index, const T &newValue)
    {
        // Intro:
        // This class maintains an 'std::vector<T*> elements' to store pointers to
        // data payloads. Additionally, 'std::vector<bool> isCopy' tracks whether
        // a particular element is a copy or the original data.
        //
        // When a value is modified, Copy-On-Write (CoW) is applied. This involves:
        // - Creating a copy of the original payload at the specified 'index'.
        // - Replacing the entry in 'elements' with the new instance.
        // - Marking the corresponding 'isCopy' entry as true to indicate ownership
        //   of the copy.
        //
        // The destructor ensures proper cleanup of CoW-created copies while leaving
        // original payloads untouched. Ownership of original data lies with the user
        // of this class, who is responsible for deleting it.

        // Step 1: Validate the index range.
        // Ensure the 'index' is within the bounds of the 'elements' vector.
        // If the index is out of bounds, print an error message and return early
        // to avoid undefined behavior.

        if(index >= this->elements.size())
            throw std::runtime_error("out of bounds");

        // Step 2: Check if the element is already a copy.
        // Inspect the 'isCopy' vector at the specified 'index'.
        // If 'isCopy[index]' is false, apply Copy-On-Write:
        // - Create a new instance by copying the original payload.
        // - Replace the original pointer in 'elements' with the new instance.
        // - Set 'isCopy[index]' to true, indicating ownership of the copy.
        if(!isCopy[index])
        {
            // Create a new copy of the original payload.
            T *copy = new T();
            *copy = *this->elements[index];
            this->elements[index] = copy;

            // Mark this element as a copy.
            this->isCopy[index] = true;
        }

        // Step 3: Modify the copied element.
        // Update the CoW copy with the new value. Since the 'elements' vector
        // stores pointers, dereference the pointer at 'index' to assign 'newValue'.

        *this->elements[index] = newValue;
    }

    // Get the size of the array
    size_t size() const
    {
        return elements.size();
    }

  private:
    std::vector<T *> elements; // Vector of pointers to elements
    std::vector<bool> isCopy;  // Flags to indicate whether each element is a copy
};

#endif // COWWRAPPER_H
