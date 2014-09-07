#include "GraphicsEngine.h"


AG_Context GraphicsEngine::context;
vector<AG_Context> GraphicsEngine::layers;
int GraphicsEngine::number_of_layers;


void GraphicsEngine::create_context(int width, int height)
{
    if (number_of_layers == 0) {
        AG_Char **ctx = new AG_Char*[height];
        
        for (int i = 0; i < height; i++) {
            ctx[i] = new AG_Char[width];
        }
        
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                ctx[j][i] = AG_Char(' ', AG_COLOUR_BLACK, AG_COLOUR_BLACK);
            }
        }
        
        context = AG_Context(width, height, (AG_Char**)ctx);
        
        layers.push_back(context);
        number_of_layers = 1;
    }
}

void GraphicsEngine::delete_context()
{
    for (int i = 0; i < context.get_height(); i++) {
        delete [] context.get_context()[i];
    }
    delete [] context.get_context();
}


void GraphicsEngine::draw(int x, int y, AG_Char c)
{
    if (x >= 0 && x < context.get_width() && y >= 0 && y < context.get_height()) {
        context.get_context()[y][x] = c;
    }
}

void GraphicsEngine::create_layer()
{
    AG_Char **ctx = new AG_Char*[context.get_height()];
    
    for (int i = 0; i < context.get_height(); i++) {
        ctx[i] = new AG_Char[context.get_width()];
    }
    
    for (int j = 0; j < context.get_height(); j++) {
        for (int i = 0; i < context.get_width(); i++) {
            ctx[j][i] = AG_Char(' ', AG_COLOUR_BLACK, AG_COLOUR_BLACK);
        }
    }
    
    layers.push_back(AG_Context(context.get_width(), context.get_height(), (AG_Char**)ctx));
    number_of_layers++;
}

void GraphicsEngine::delete_layer()
{
    
}

int GraphicsEngine::get_number_of_layers()
{
    return number_of_layers;
}


int GraphicsEngine::RGB_colour(char R, char G, char B)
{
    if (R < 0) R = 0;
    else if (R > 5) R = 5;
    
    if (G < 0) G = 0;
    else if (G > 5) G = 5;
    
    if (B < 0) B = 0;
    else if (B > 5) B = 5;
    
    return 16 + 36*R + 6*G + B;
}


void GraphicsEngine::render()
{
    printf("\033[?25l"); //hide cursor
    printf("\033[2J");   //clear screen
    printf("\033[3J\033[1;1H"); //remove history
    
    for (int i = 0; i < context.get_height(); i++) {
        for (int j = 0; j < context.get_width(); j++) {
            short colour = context.get_context()[i][j].get_colour();
            short background_colour = context.get_context()[i][j].get_background_colour();
            char character = context.get_context()[i][j].get_value();
            if (background_colour != AG_COLOUR_TRANSPARENT) {
                printf("\x1B[48;5;%dm", background_colour);
            }
            if (colour != AG_COLOUR_TRANSPARENT) {
                printf("\x1B[38;5;%dm", colour);
                printf("%c", character);
            }
            printf("\x1B[0m");  //reset colours
        }
        cout << endl;
    }
    printf("\033[?25h"); //show cursor
}

