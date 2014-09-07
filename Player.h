#ifndef __Spartans__Player__
#define __Spartans__Player__

#include <iostream>
#include "IO.h"

struct Point {
    int x;
    int y;
    
    Point() {
        this->x = 0;
        this->y = 0;
    }
    
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
    
    Point operator+(Point p)
    {
        Point r = Point(0,0);
        r.x=this->x + p.x;
        r.y=this->y + p.y;
        return r;
    }
    
    bool operator==(Point p)
    {
        return this->x == p.x && this->y == p.y;
    }
    
};

class Player {
private:
    Point position;
    std::string name;
    IO io;
    
    unsigned int msgSize;
    
    std::string lastMove;
    
    unsigned int number;
    unsigned int health;
    unsigned int shield;
    unsigned int blocking;
    unsigned int beingStabbed;
    unsigned int kills;
    
    Player* playerBeingStabbed;
    
public:
    Player(Point initial_position, std::string name, std::string spartan, unsigned int number, unsigned int width, unsigned int height, unsigned int msgSize);
    ~Player();
    
    Point getPosition();
    void setPosition(Point p);
    
    unsigned int getId();
    
    int getHealth();
    void setHealth(int health);
    
    int getShield();
    void setShield(int shield);
    
    unsigned int getBlock();
    void setBlock(unsigned int block);
    
    unsigned int getBeingStabbed();
    void setBeingStabbed(unsigned int stab);
    
    unsigned int getKills();
    void setKills(unsigned int kills);
    
    Player* getPlayerBeingStabbed();
    void setPlayerBeingStabbed(Player* player);
    
    std::string makeTurn(char *msg);
    std::string getLastMove();
    
    void kill();
};

#endif /* defined(__Spartans__Player__) */
