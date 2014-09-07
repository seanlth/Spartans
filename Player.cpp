#include "Player.h"


Player::Player(Point initial_position, std::string name, std::string bot_location, unsigned int number, unsigned int width, unsigned int height, unsigned int msgSize)
{
    this->position = initial_position;
    this->name = name;
    this->io = IO(bot_location);
    this->number = number;
    this->health = 4;
    this->shield = 4;
    this->blocking = 0;
    this->beingStabbed = 0;
    
    this->lastMove = "";
    
    this->msgSize = msgSize;
    
    char w = width;
    char h = height;
    char m = this->msgSize;
    
    char i[] = {static_cast<char>(number+1), w, h, m};
    
    this->io.openCommunication(i);
}

Player::~Player()
{
    if (this->health > 0) {
        this->kill();
    }
    this->io.closeCommunication();
}

Point Player::getPosition()
{
    return this->position;
}

void Player::setPosition(Point p)
{
    this->position = p;
}

unsigned int Player::getId()
{
    return this->number;
}

int Player::getHealth()
{
    return this->health;
}

void Player::setHealth(int health)
{
    this->health = health;
}

int Player::getShield()
{
    return this->shield;
}

void Player::setShield(int shield)
{
    this->shield = shield;
}

unsigned int Player::getBlock()
{
    return this->blocking;
}

void Player::setBlock(unsigned int block)
{
    this->blocking = block;
}

unsigned int Player::getBeingStabbed()
{
    return this->beingStabbed;
}

void Player::setBeingStabbed(unsigned int stab)
{
    this->beingStabbed = stab;
}

unsigned int Player::getKills()
{
    return this->kills;
}

void Player::setKills(unsigned int kills)
{
    this->kills = kills;
}

Player* Player::getPlayerBeingStabbed()
{
    return this->playerBeingStabbed;
}

void Player::setPlayerBeingStabbed(Player* player)
{
    this->playerBeingStabbed = player;
}

std::string Player::makeTurn(char *msg)
{
    if (this->playerBeingStabbed != NULL) {
        if (this->playerBeingStabbed->getHealth() <= 0) {
            this->kills++;
        }
    }
    
    this->playerBeingStabbed = NULL;
    
    io.send(msg, this->msgSize);
    
    std::string move = io.recieve();
    this->lastMove = move;
    
    return move;
}

std::string Player::getLastMove()
{
    return this->lastMove;
}

void Player::kill()
{
    char kill_msg[this->msgSize];
    
    kill_msg[0] = 'k';
    kill_msg[1] = 'i';
    kill_msg[2] = 'l';
    kill_msg[3] = 'l';
    kill_msg[4] = '\0';

    io.send(kill_msg, this->msgSize);    
}




