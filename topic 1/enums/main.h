#ifndef MAIN_H
#define MAIN_H

enum State // adding class before the name gives it a namespace or scope of its own, removing conflicts
{
    INPLAY = 0,
    DEAD = 1,
    WINNER = 2,
    PAUSED = 4
};

#endif