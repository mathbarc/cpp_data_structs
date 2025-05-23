#include "data_interface/av_data_interface.hpp"
#include "data_interface/av_data_interface_impl.hpp"
#include "data_structures/circular_buffer.hpp"
#include "data_structures/hashmap.hpp"
#include "data_structures/sorted_singly_linked_list.hpp"
#include "file_reader.hpp"
#include <chrono>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sys/types.h>
#include <vector>

using DataStreamHolder = SortedSinglyLinkedList;

std::vector<uint8_t> *getData(DataStreamHolder *streamHolder, size_t pos)
{
    Node *node = streamHolder->search(pos);
    if(node == nullptr)
        throw std::runtime_error("Node not found at sequence " + std::to_string(pos));
    AvDataInterface *dataInterface = static_cast<AvDataInterface *>(node->data);
    if(dataInterface == nullptr)
        throw std::runtime_error("Data not found at sequence " + std::to_string(pos));
    return dataInterface->getPayload();
}

int main(int argc, char **argv)
{
    std::string filePath;
    if(argc < 2)
        filePath = "data/tv_packets.bin";
    else
        filePath = argv[1];
    // Set the debug flag to true to print out extra information

    // todo: Choose and instantiate an appropriate data structure to hold the raw
    // data from the provided file. You should pick a data structure amongst
    // the options in the data_structures folder. Ensure it can store multiple
    // elements and handle dynamic data efficiently.
    //
    // Example:

    auto dsInstance = CircularBuffer<std::vector<uint8_t> *>(32);

    // Instantiate the FileReader with the created DataStructure instance,
    // path to the data file, chunk size, and debug flag
    FileReader fr = FileReader(&dsInstance, filePath, 128);
    fr.startReading();

    // todo: Select a suitable data structure to store and retrieve streams by
    // unique identifiers. Each stream (e.g., audio or video for a specific
    // channel) will be identified by a string (e.g., "XYZ1_0" for the audio
    // stream of channel XYZ1). The data structure must allow for efficient
    // insertion and retrieval based on this identifier. Instantiate this data
    // structure to hold the streams for various identifiers such as XYZ1_0,
    // XYZ1_1, DEF9_0, DEF9_1, etc.
    // Hint: The DataStreamHolder here will be the same as the DataStreamHolder
    // selected further down.
    //
    // Example:
    HashMap<std::string, DataStreamHolder> highLevelDataStructureInstance;

    // Continue reading as long as the FileReader is running or the dsInstance
    // still has data to parse
    while(fr.isRunning() || false == dsInstance.isEmpty())
    {
        // Wait for the reader to finish
        while(false == dsInstance.isEmpty())
        {
            // todo: Implement the parseData method of the AvDataInterfaceImpl class
            // under the data_interface folder.
            AvDataInterface *avDataInterface = new AvDataInterfaceImpl(dsInstance.remove());

            std::string channelName;
            StreamType streamType;
            avDataInterface->parseData(&channelName, &streamType);

            // Concatenate channelName and streamType to create the unique identifier
            std::string uniqueIdentifier = channelName + "_" + std::to_string(static_cast<int>(streamType));

            // Check if the uniqueIdentifier exists in the hashmap
            DataStreamHolder *dataStreamHolderPtr = highLevelDataStructureInstance.get(uniqueIdentifier);
            if(nullptr == dataStreamHolderPtr)
            {
                // If the uniqueIdentifier doesn't exist, it means that it's the first
                // time we're receiving data for this particular data stream, i.e.
                // audio, for this particula channel, i.e. ABC1. So, instantiate a new
                // data container for this stream and store it in the high level
                // structure with the appropriate uniqueIdentifier.
                //
                // todo: Choose and instantiate the most appropriate data structure to
                // hold the data for each stream (e.g., audio, video) within a specific
                // channel. This structure will store data for individual streams and
                // should allow efficient insertion and retrieval of data elements as
                // they are processed.
                //
                // Example:
                DataStreamHolder *newDsh = new DataStreamHolder();

                // todo: Add the newly created data stream holder instance to the
                // higher-level data structure using the generated unique identifier
                // (e.g., "XYZ1_0"). Ensure that future lookups based on this identifier
                // can correctly return the appropriate stream data.
                //
                // Example:
                highLevelDataStructureInstance.insert(uniqueIdentifier, newDsh);
                dataStreamHolderPtr = newDsh;
            }
            dataStreamHolderPtr->insert(avDataInterface);

#ifdef DEBUG
            std::cout << channelName << " " << static_cast<int>(streamType) << " "
                      << static_cast<int>(avDataInterface->getSequenceNumber()) << std::endl;
#endif // DEBUG
        }

        // Allow the file reader to read and push data
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    // todo: (Stand-out task)
    // Extract and print the first byte of video stream packets 1, 50, and 100
    // for channel XYZ1, and audio stream packets 1, 50, and 100 for channel DEF9.
    // N.B.: Formatting values in hexadecimal is preferred over decimal.

    std::string identifier = "XYZ1_1";
    auto dataStreamHolder = highLevelDataStructureInstance.get(identifier);
    std::cout << identifier << std::endl;
    u_char c;
    c = getData(dataStreamHolder, 1)->front();
    std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c) << std::endl;
    c = getData(dataStreamHolder, 50)->front();
    std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c) << std::endl;
    c = getData(dataStreamHolder, 100)->front();
    std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c) << std::endl;

    identifier = "DEF9_0";
    dataStreamHolder = highLevelDataStructureInstance.get(identifier);
    std::cout << identifier << std::endl;
    c = getData(dataStreamHolder, 1)->front();
    std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c) << std::endl;
    c = getData(dataStreamHolder, 50)->front();
    std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c) << std::endl;
    c = getData(dataStreamHolder, 100)->front();
    std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c) << std::endl;
    return 0;
}
