
# Initialise the FileReader

Use the provided FileReader class to read the out-of-order audio and video data blocks. Initialise it with the appropriate DataStructure instance that:

- Meets memory constraints.
- Allows for efficient storage and retrieval of data.
- Can discard older packets if the data is not retrieved quickly enough.
- The selected data structure should be instantiated with the std::vector<uint8_t>* data type, which holds the raw audio/video data.
- After instantiating the FileReader, call the startReading method to start the data read and call the isRunning method regularly to check whether the file is completely read.

# Data Polling and Retrieval

Continuously poll the data structure instance passed into the FileReader and retrieve chunks of data grouped as std::vector<uint8_t>* instances when isEmpty returns false. The program should terminate when the isRunning method of FileReader returns false and dsInstance.isEmpty() returns true.

# Data Parsing

AvDataInterfaceImpl class under the data_interface folder is used to parse the stream header and store the payload. Instantiate the Complete the implementation of the parseData method of the AvDataInterfaceImpl class to parse and store the 128-byte raw data blocks based on the following structure:

- 4-byte channel name: Identifies the TV channel.
- 1-byte identifier: Indicates whether the block contains audio (0) or video (1).
- 1-byte sequence number: Determines the correct order of the blocks.
- 122-byte payload: Contains the actual audio or video data.

# Ordering and Grouping

After creating an AvDataInterfaceImpl instance for each raw data chunk, parse the data by calling its parseData method. Ensure that each AvDataInterfaceImpl instance is inserted into the appropriate data structure for its corresponding channel and stream type. For example, all audio packets for the XYZ1 audio stream should be grouped together, and the same applies to other channels and stream types.

The data structure chosen amongst the provided options under the data_structures folder should be able to hold packets for each stream and also support sorting. For instance, if a video packet for channel XYZ1 with sequence number 1 arrives after packet 2, the data structure should insert packet 1 before packet 2. The selected structure should efficiently handle out-of-order packet insertion.

# Grouping Data Streams By Channel Name and Type

Select another data structure from the data_structures folder that allows grouping of audio and video streams for each TV channel. This structure should also provide O(1) access time when a channel name and stream type are provided. For example, a string like ‘XYZ1_0’ should return the audio stream for channel XYZ1 wrapped inside the data structure picked in the previous step, with O(1) time complexity.

# Verification and Output

After processing the file, output the first two bytes of the following data packets to verify the correctness of your implementation:

- Video stream of channel XYZ1: packets 1, 50, and 100.
- Audio stream of channel DEF9: packets 1, 50, and 100.
