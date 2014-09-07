#ifndef __Spartans__Map__
#define __Spartans__Map__

#include <iostream>
#include <string.h>
#include <stdio.h>
#include "Player.h"
#include <vector>
#include <fstream>
#include "GraphicsEngine.h"
#include <math.h>

class Map {
private:
    std::vector<Player*> players;
    
    unsigned int **board;
    unsigned int width;
    unsigned int height;
    
    int sideLength(int n);
    std::vector<std::string> readFile(std::string file);
    void draw();
    
    
public:
    Map(std::string spartan_file);
    Map(std::string spartan_file, unsigned int width, unsigned int height);
    ~Map();
    
    void cycle();
};

#endif /* defined(__Spartans__Map__) */
