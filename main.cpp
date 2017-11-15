#include "myapplication.h"
#include "gamewindow.h"

int main(int argc, char *argv[])
{
    MyApplication a(argc, argv, "Tihran developments", "Empty Space");
    GameWindow game;
    game.show();
    return a.exec();
}
