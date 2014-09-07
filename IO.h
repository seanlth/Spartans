#ifndef __Spartans__IO__
#define __Spartans__IO__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

class IO {
private:
    std::string file_location;
    
    int pipe1[2];
    int pipe2[2];
    
    int write_to;
    int read_from;
    
    void openPipe(std::string cmd, char *arg, int *write_to, int *read_from, int readpipe[2], int writepipe[2]);
    
public:
    IO();
    IO(std::string file);
    
    void openCommunication(char *arg);
    void closeCommunication();
    
    void send(char *data, unsigned int size);

    void send(std::string data);
    const std::string recieve();
    
};

#endif /* defined(__Spartans__IO__) */
