#include "Map.h"


Map::Map(std::string spartan_file)
{
    std::vector<std::string> spartans = readFile(spartan_file);
    
    this->height = sideLength((int)spartans.size());
    this->width = this->height;
    
    this->board = new unsigned int*[height];
    for (int i = 0; i < height; i++) {
        this->board[i] = new unsigned int[width];
    }
   
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            this->board[i][j] = -1;
        }
    }
    
    
    GraphicsEngine::create_context(width, height);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            GraphicsEngine::draw(j, i, AG_Char('.', AG_COLOUR_WHITE));
        }
    }

    int posX = 0;
    int posY = 0;
    
    for (int i = 0; i < spartans.size(); i++) {
        std::string name = strtok((char*)spartans[i].c_str(), " ");
        
        unsigned int msgSize = (unsigned int)(5*spartans.size());
        
        if (posX < width-1 && posY < height-1) {
            this->players.push_back(new Player(Point(posX, posY), name, strtok(NULL, " "), i, this->width, this->height, msgSize));
            posX += 5;
        }
        else if (posX == width-1 && posY < height-1) {
            this->players.push_back(new Player(Point(posX, posY), name, strtok(NULL, " "), i, this->width, this->height, msgSize));
            posY += 5;
        }
        else if (posX > 0 && posY == height-1) {
            this->players.push_back(new Player(Point(posX, posY), name, strtok(NULL, " "), i, this->width, this->height, msgSize));
            posX -= 5;
        }
        else if (posX == 0 && posY > 0) {
            this->players.push_back(new Player(Point(posX, posY), name, strtok(NULL, " "), i, this->width, this->height, msgSize));
            posY -= 5;
        }
        
        GraphicsEngine::draw(posX, posY, AG_Char(i + 65, AG_COLOUR_WHITE));
        this->board[posY][posX] = i;
    }
    GraphicsEngine::render();
}

Map::Map(std::string spartan_file, unsigned int width, unsigned int height)
{
    std::vector<std::string> spartans = readFile(spartan_file);
    
    this->board = new unsigned int*[height];
    for (int i = 0; i < height; i++) {
        this->board[i] = new unsigned int[width];
    }
}

Map::~Map()
{
    for (int i = 0; i < height; i++) {
        delete [] this->board[i];
    }
    delete [] this->board;
    
    for (int i = 0; i < this->players.size(); i++) {
        delete this->players[i];
    }
}


void Map::cycle()
{
    unsigned int** temp = new unsigned int*[height];
    for (int i = 0; i < height; i++) {
        temp[i] = new unsigned int[width];
    }
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            temp[i][j] = this->board[i][j];
        }
    }
    
    //p=[id:1,x:1,y:1,h:1,s:1]
    //mes=(p:5)*n
    
    char msg[5*players.size()];
    
    for (int i = 0; i < players.size(); i++) {
        msg[5*i] = players[i]->getId();
        msg[5*i+1] = players[i]->getPosition().x;
        msg[5*i+2] = players[i]->getPosition().y;
        msg[5*i+3] = players[i]->getHealth();
        msg[5*i+4] = players[i]->getShield();
    }
    
    for (int i = 0; i < this->players.size(); i++) {
        
        if (players[i]->getHealth() <= 0) {
            continue;
        }
        
        std::string move = this->players[i]->makeTurn(msg);
        
        char m = move[0];
        char d = move[2];
        Point v = Point(0, 0);
        
        unsigned int dir = 0;
        
        switch (d) {
            case 'u':
                if (this->players[i]->getPosition().y > 0) {
                    v = Point(0, -1);
                }
                else {
                    v = Point(0, 0);
                }
                dir = 2;
                break;
            case 'd':
                if (this->players[i]->getPosition().y < height-1) {
                    v = Point(0, 1);
                }
                else {
                    v = Point(0, 0);
                }
                dir = 3;
                break;
            case 'l':
                if (this->players[i]->getPosition().x > 0) {
                    v = Point(-1, 0);
                }
                else {
                    v = Point(0, 0);
                }
                dir = 5;
                break;
            case 'r':
                if (this->players[i]->getPosition().x < width-1) {
                    v = Point(1, 0);
                }
                else {
                    v = Point(0, 0);
                }
                dir = 6;
                break;
            default:
                break;
        }
        
        switch (m) {
            case 's':
            {
                Point direction = this->players[i]->getPosition()+v;

                if (this->board[direction.y][direction.x] != -1 && !(v == Point(0,0))) {
                    this->players[board[direction.y][direction.x]]->setBeingStabbed(dir);
                    this->players[i]->setPlayerBeingStabbed(this->players[board[direction.y][direction.x]]);
                }
            }
                break;
            case 'm':
            {
                Point newPos = this->players[i]->getPosition()+v;
                if (board[newPos.y][newPos.x] == -1) {
                    this->board[this->players[i]->getPosition().y][this->players[i]->getPosition().x] = -1;
                    this->board[newPos.y][newPos.x] = this->players[i]->getId();
                    this->players[i]->setPosition(newPos);
                }
            }
                break;
            case 'b':
            {
                this->players[i]->setBlock(dir);
            }
                break;
            default:
                break;
        }
    }
    
    for (int i = 0; i < this->players.size(); i++) {
        if (this->players[i]->getBeingStabbed() == 0 || this->players[i]->getHealth() <= 0) {
            continue;
        }
        if ( abs( (int)( this->players[i]->getBeingStabbed() - this->players[i]->getBlock() ) ) != 1 || this->players[i]->getShield() == 0) {
            this->players[i]->setHealth(this->players[i]->getHealth()-1);
            if (this->players[i]->getHealth() <= 0) {
                this->players[i]->kill();
                this->board[this->players[i]->getPosition().y][this->players[i]->getPosition().x] = -1; //remove from board
            }
        }
        else if (this->players[i]->getShield() != 0) {
            this->players[i]->setShield(this->players[i]->getShield() - 1);
        }
        this->players[i]->setBlock(0);
        this->players[i]->setBeingStabbed(0);
    }
    
    this->draw();
}

void Map::draw()
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            GraphicsEngine::draw(j, i, AG_Char('.', AG_COLOUR_WHITE));
        }
    }
    for (int i = 0; i < this->players.size(); i++) {
        if (this->players[i]->getHealth() != 0) {
            GraphicsEngine::draw(this->players[i]->getPosition().x, this->players[i]->getPosition().y, AG_Char(i + 65, AG_COLOUR_WHITE));
        }
    }
    
    GraphicsEngine::render();
    
    for (int i = 0; i < this->players.size(); i++) {
        std::cout << "Health of " << this->players[i]->getId() << " is " << this->players[i]->getHealth() << std::endl;
        std::cout << "Spartan" << this->players[i]->getId() << " did " << this->players[i]->getLastMove() << std::endl;
        std::cout << "Kills " << this->players[i]->getKills() << std::endl;
        
        std::cout << std::endl;
    }
    
}


int Map::sideLength(int n)
{
    
    int x = 0;
    for (int i = 1; i < 12; i++) {
        if (!(n > 4*x && n <= 4*(x+1))) {
            x++;
        }
    }

    return 6 + 5*x;
}


std::vector<std::string> Map::readFile(std::string file)
{
    std::vector<std::string> result;
    std::string line;
    std::fstream f(file, std::fstream::in);
    if (f.is_open()) {
        
        while (std::getline(f, line)) {
            result.push_back(line);
        }
    }
    else {
        std::cout << "Error opening file" << std::endl;
        exit(-1);
    }
    f.close();
    
    return result;
}



