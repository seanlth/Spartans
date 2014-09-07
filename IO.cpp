#include "IO.h"

IO::IO()
{
    
}

IO::IO(std::string file)
{
    this->file_location = file;
}

void IO::closeCommunication()
{
    close(this->read_from);
    close(this->write_to);
}


void IO::openCommunication(char *arg)
{
    openPipe(this->file_location, arg, &this->write_to, &this->read_from, this->pipe1, this->pipe2);
}

void IO::openPipe(std::string cmd, char *arg, int *write_to, int *read_from, int readpipe[2], int writepipe[2])
{
    pipe(readpipe);
    pipe(writepipe);
        
    pid_t childpid = fork();
    
    if (childpid == -1) {
        printf("Fork error\n");
        exit(1);
    }
    else if( childpid == 0 ) {
        dup2(writepipe[0], 0);
        dup2(readpipe[1], 1);
        
        close(writepipe[1]);
        close(readpipe[0]);
        
        execl(cmd.c_str(), arg, NULL);
        
        exit(1);
    }
    else {
        close(writepipe[0]);
        close(readpipe[1]);
        
        *write_to = writepipe[1];
        *read_from = readpipe[0];
    }

}

void IO::send(char *data, unsigned int size)
{
    while (write(write_to, data, size) == -1);
}

void IO::send(std::string data)
{
    while (write(write_to, data.c_str(), data.size()+1) == -1); //null terminated
}

const std::string IO::recieve()
{
    char data[4];
    while (read(read_from, data, 4) == -1);
        
    std::string move = data;
    return move;
}










