#ifndef GENERATOR_H
#define GENERATOR_H

#include <cstdlib>
#include <iostream>
#include <math.h>

namespace ecn
{

class Maze;

class Generator
{
public:
    Generator()
    {

    }

    struct Node
    {
        int x, y; //Node position - little waste of memory, but it allows faster generation
        void *parent; //Pointer to parent node
        char c; //Character to be displayed
        char dirs; //Directions that still haven't been explored
    };

    Node *nodes; //Nodes array
    int width, height, percent; //Maze dimensions

    int init();

    void generateMaze(char* path);

    void makeEntries();

    int convert_to_2d(int i,int j);

    void draw();

    Node linkNodes(Node *n);

    void theGenerator(int argc, char **argv);



    static Maze maze;
};
}

#endif // GENERATOR_H
