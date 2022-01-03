#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <maze.h>
#include <generator.h>

// *****
namespace ecn {


Maze Generator::maze;

int Generator::init()
{
    int i, j;
    Node *n;

    //Allocate memory for maze
    nodes = (Node*)calloc(width * height, sizeof(Node));
    if (nodes == NULL) return 1;

    //Setup crucial nodes
    for (i = 0; i < width; i++)
    {
        for (j = 0; j < height; j++)
        {
            n = nodes + i + j * width;
            if (i * j % 2)
            {
                n->x = i;
                n->y = j;
                n->dirs = 15; //Assume that all directions can be explored (4 youngest bits set)
                n->c = ' ';
            }
            else n->c = '#'; //Add walls between nodes
        }
    }
    return 0;
}

//Generator::Node Generator::*linkNodes(Generator::Node *n);
/*
Generator::Node Generator::linkNodes(Generator::Node *n)
{
    //Connects node to random neighbor (if possible) and returns
    //address of next node that should be visited

    int x, y;
    char dir;
    Node *dest;

    //Nothing can be done if null pointer is given - return
    if (n == NULL) return NULL;

    //While there are directions still unexplored
    while (n->dirs)
    {
        //Randomly pick one direction
        dir = (1 << (rand() % 4));

        //If it has already been explored - try again
        if (~n->dirs & dir) continue;

        //Mark direction as explored
        n->dirs &= ~dir;

        //Depending on chosen direction
        switch (dir)
        {
            //Check if it's possible to go right
            case 1:
                if (n->x + 2 < width)
                {
                    x = n->x + 2;
                    y = n->y;
                }
                else continue;
                break;

            //Check if it's possible to go down
            case 2:
                if (n->y + 2 < height)
                {
                    x = n->x;
                    y = n->y + 2;
                }
                else continue;
                break;

            //Check if it's possible to go left
            case 4:
                if (n->x - 2 >= 0)
                {
                    x = n->x - 2;
                    y = n->y;
                }
                else continue;
                break;

            //Check if it's possible to go up
            case 8:
                if (n->y - 2 >= 0)
                {
                    x = n->x;
                    y = n->y - 2;
                }
                else continue;
                break;
        }

        //Get destination node into pointer (makes things a tiny bit faster)
        dest = nodes + x + y * width;

        //Make sure that destination node is not a wall
        if (dest->c == ' ')
        {
            //If destination is a linked node already - abort
            if (dest->parent != NULL) continue;

            //Otherwise, adopt node
            dest->parent = n;

            //Remove wall between nodes
            nodes[n->x + (x - n->x) / 2 + (n->y + (y - n->y) / 2) * width].c = ' ';

            //Return address of the child node
            return dest;
        }
    }

    //If nothing more can be done here - return parent's address
    return (Node*)n->parent;
}

*/

void Generator::draw()
{
    int i, j;

    //Outputs maze to terminal - nothing special
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            printf("%c", nodes[j + i * width].c);
        }
        printf("\n");
    }
}

int Generator::convert_to_2d(int i,int j) {
    return j + width*i;
}
void Generator::makeEntries() {
    int i;
    for(i = 0;i<width;i++)
    {
        if (nodes[convert_to_2d(1,i)].c == ' ') {
            printf("I'm here with at wall 1 : %d\n",i);
            nodes[convert_to_2d(0,i)].c = ' ';
            break;
        }
    }

    for(i = width-1;i > 0;i--)
    {
        if (nodes[convert_to_2d(height - 2,i)].c == ' ') {
            printf("I'm here with at wall 2 : %d\n",i);
            nodes[convert_to_2d(height-1,i)].c = ' ';
            break;
        }
    }



}




void Generator::generateMaze(char* path) {
    int i,j;
    ecn::Maze maze = ecn::Maze(height,width);
    for(i = 0; i< height;i++) {
        for(j = 0;j <width;j++) {
            if(nodes[j+i*width].c == ' ')
                maze.dig(i,j);
        }
    }
    maze.save(path);
}
// *****


void Generator::theGenerator(int argc, char **argv)
{
    // **************
    Generator gene;
    Node *begin, *end;
    char maze_name[50];

    //Check argument count
    if (argc < 3)
    {
        std::cout<<"please specify maze dimensions!"<<std::endl;
        exit(1);
    }

    //Read maze dimensions from command line arguments
    if (sscanf(argv[1], "%d", &width) + sscanf(argv[2], "%d", &height) < 2)
    {
        fprintf(stderr, "%s: invalid maze size value!\n", argv[0]);
        exit(1);
    }
    //if(sscanf(argv[3],"%d",&percent) > 100 || sscanf(argv[3],"%d",&percent) < 0){
    //	printf("Please enter a valid percentage between 0 and 100\n");
    //}
    //Allow only odd dimensions
    if (!(width % 2) || !(height % 2))
    {
        fprintf(stderr, "%s: dimensions must be odd!\n", argv[0]);
        exit(1);
    }

    //Do not allow negative dimensions
    if (width <= 0 || height <= 0)
    {
        fprintf(stderr, "%s: dimensions must be greater than 0!\n", argv[0]);
        exit(1);
    }


    std::cout<<"Width "<< width<<std::endl;
    std::cout<<"Height "<< height<<std::endl;

    if (init())
    {
        fprintf(stderr, "%s: out of memory!\n", argv[0]);
        exit(1);
    }
    begin = nodes + 1 + width;
    begin->parent = begin;
    end = begin;
    //*************************************


    //Connects node to random neighbor (if possible) and returns
    //address of next node that should be visited

    int x, y;
    char dir;
    Node *dest;

    Node *n=end;
    Node *compare;

    //Nothing can be done if null pointer is given - return
    if (n == NULL)
    {
        compare = NULL;
    }
    //While there are directions still unexplored
    while (n->dirs)
    {
        //Randomly pick one direction
        dir = (1 << (rand() % 4));

        //If it has already been explored - try again
        if (~n->dirs & dir) continue;

        //Mark direction as explored
        n->dirs &= ~dir;

        //Depending on chosen direction
        switch (dir)
        {
            //Check if it's possible to go right
            case 1:
                if (n->x + 2 < width)
                {
                    x = n->x + 2;
                    y = n->y;
                }
                else continue;
                break;

            //Check if it's possible to go down
            case 2:
                if (n->y + 2 < height)
                {
                    x = n->x;
                    y = n->y + 2;
                }
                else continue;
                break;

            //Check if it's possible to go left
            case 4:
                if (n->x - 2 >= 0)
                {
                    x = n->x - 2;
                    y = n->y;
                }
                else continue;
                break;

            //Check if it's possible to go up
            case 8:
                if (n->y - 2 >= 0)
                {
                    x = n->x;
                    y = n->y - 2;
                }
                else continue;
                break;
        }

        //Get destination node into pointer (makes things a tiny bit faster)
        dest = nodes + x + y * width;

        //Make sure that destination node is not a wall
        if (dest->c == ' ')
        {
            //If destination is a linked node already - abort
            if (dest->parent != NULL) continue;

            //Otherwise, adopt node
            dest->parent = n;

            //Remove wall between nodes
            nodes[n->x + (x - n->x) / 2 + (n->y + (y - n->y) / 2) * width].c = ' ';

            //Return address of the child node
            compare = dest;
        }
    }

    //If nothing more can be done here - return parent's address
   compare  = (Node*)n->parent;


    //*************************************

    while ((end = compare) != begin);
    //here the maze is fully generated
    makeEntries();

    draw();
    sprintf(maze_name,"../mazes/maze_%d_%d.png",height,width);
    generateMaze(maze_name);



    // **************
}
}
