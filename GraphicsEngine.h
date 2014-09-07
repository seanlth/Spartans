#ifndef __Abode__GraphicsEngine__
#define __Abode__GraphicsEngine__

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

const short AG_COLOUR_BLACK = 0, AG_COLOUR_RED = 1, AG_COLOUR_GREEN = 2, AG_COLOUR_BROWN = 3, AG_COLOUR_BLUE = 4, AG_COLOUR_MAGENTA = 5, AG_COLOUR_CYAN = 6, AG_COLOUR_LIGHT_GREY = 7, AG_COLOUR_DARK_GREY = 8, AG_COLOUR_LIGHT_RED = 9, AG_COLOUR_LIGHT_GREEN = 10, AG_COLOUR_YELLOW = 11, AG_COLOUR_LIGHT_BLUE = 12, AG_COLOUR_LIGHT_MAGENTA = 13, AG_COLOUR_LIGHT_CYAN = 14, AG_COLOUR_WHITE = 15, AG_COLOUR_TRANSPARENT = 256;

class AG_Char {
    char value;
    short colour;
    short background_colour;

public:
    
    char get_value()
    {
        return this->value;
    }
    
    char get_colour()
    {
        return this->colour;
    }
    
    char get_background_colour()
    {
        return this->background_colour;
    }
    
    AG_Char()
    {
        
    }
    
    AG_Char(char value, short colour)
    {
        this->value = value;
        this->colour = colour;
        this->background_colour = AG_COLOUR_BLACK;
    }
    AG_Char(short background_colour)
    {
        this->value = ' ';
        this->colour = AG_COLOUR_BLACK;
        this->background_colour = background_colour;
    }
    AG_Char(char value, short colour, short background_colour)
    {
        this->value = value;
        this->colour = colour;
        this->background_colour = background_colour;
    }
    
};

class AG_Context {
    int width;
    int height;
    AG_Char **context;

public:
    int get_height()
    {
        return this->height;
    }
    int get_width()
    {
        return this->width;
    }
    AG_Char** get_context()
    {
        return this->context;
    }
    
    AG_Context()
    {
        
    }
    
    
    AG_Context(int width, int height, AG_Char **context)
    {
        this->width = width;
        this->height = height;
        this->context = context;
    }
    
};

class GraphicsEngine {
private:
    static AG_Context context;
    static vector<AG_Context> layers;
    static int number_of_layers;
public:
    
    static void create_context(int width, int height);
    static void delete_context();
    static void create_layer();
    static void delete_layer();
    static int get_number_of_layers();
    static void draw(int x, int y, AG_Char c);
    static void render();
    static int RGB_colour(char R, char G, char B);
};

#endif /* defined(__Abode__GraphicsEngine__) */
