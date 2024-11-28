#include <iostream>
#include "NumericPlay.h"
#include "pyramidplay.h"
int main()
{
    PlayPyramidGame<char>p;
    PyramidBoard<char> b;
    p.startGame(b);
    return 0;
}
