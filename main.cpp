#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include "Map.h"


void handler(int s) {
}

int main(int argc, const char * argv[])
{
    signal(SIGPIPE, handler);
    
    Map m = Map("Spartans.txt");
    
    for (int i = 0; i < 500; i++) {
        m.cycle();
        usleep(50000); 
    }
    
    return 0;
}
