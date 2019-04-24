C/C++ commandline application that encodes a set of WAV files to MP3
1. Uses all available CPU cores for the encoding process in an efficient way by utilizing multi-threading
2. Statically link to lame encoder library
3. The resulting MP3 files are placed within the same directory as the source WAV files, the filename extension should be changed appropriately to .MP3
4. Multi-threading implemented by means of using Posix Threads
5. No boost library used

====

    How to compile & test (tested on CentOS Linux release 7.5.1804 and MacOS)

1) cmake .
2) make -j4 (use more than 4 cores if available to speed up make)
3) ./lame_encoder testdata/

Output:

Number of threads to pump events: 12  
Wav file found: file_example_WAV_2MG.wav  
mp3 file to be generated: file_example_WAV_2MG.mp3  
Wav file found: file_example_WAV_10MG.wav  
mp3 file to be generated: file_example_WAV_10MG.mp3  
Wav file found: file_example_WAV_1MG.wav  
mp3 file to be generated: file_example_WAV_1MG.mp3  
Wav file found: file_example_WAV_5MG.wav  
mp3 file to be generated: file_example_WAV_5MG.mp3  
Totally processed wav file conversions 4



