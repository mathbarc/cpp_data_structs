#include "data_structures/queue.hpp"
#include "file_reader.hpp"
#include <cassert>

int main(int argc, char **argv)
{
    if(argc < 2)
        return -1;
    std::string path(argv[1]);
    Queue<std::vector<uint8_t> *> dataQueue;
    FileReader fr = FileReader(&dataQueue, path, 128);
    fr.startReading();

    int i = 0;
    size_t length = 0;
    while(fr.isRunning())
    {
        i++;
        while(!dataQueue.isEmpty())
        {
            std::vector<uint8_t> *data = dataQueue.remove();
            length += data->size();
            delete data;
        }
    }

    assert(length == 51200);

    return 0;
}
