#include <a_star.h>
#include <maze.h>
#include <generator.h>

using namespace std;
using namespace ecn;

// a node is a x-y position, we move from 1 each time
class Position : public Point
{
    typedef std::unique_ptr<Position> PositionPtr;

public:
    // constructor from coordinates
    Position(int _x, int _y) : Point(_x, _y) {}

    // constructor from base ecn::Point
    Position(ecn::Point p) : Point(p.x, p.y) {}

    int distToParent()
    {
        // in cell-based motion, the distance to the parent is always 1
        return 1;
    }

    std::vector<PositionPtr> children()
    {
        // this method should return  all positions reachable from this one
        std::vector<PositionPtr> generated;

        //Defining list of displacements to perform

        std::vector<std::pair<int, int>>displacements
        {
            {-1,0},   //dx, dy
            {1,0},
            {0,1},
            {0,-1},
        };

        for(const auto& [dx,dy] : displacements)
        {
            //from current position x,y (member variables) we compute neighbours

            int new_x= x + dx;
            int new_y= y + dy;

            if(maze.isFree(new_x,new_y))
            {
                generated.push_back(std::make_unique<Position>(new_x,new_y)); //C++ 17 way to create a pointer
            }
        }

        return generated;
    }
};



int main( int argc, char **argv )
{
    Generator gene;
    gene.theGenerator(argc,argv);


    // load file
    std::string filename = "../mazes/maze.png";
    //argc=2;
    cout<<"argv : "<<argv[1]<<endl;
    if(argc == 2)
        filename = std::string(argv[1]);

    // let Point know about this maze
    Position::maze.load(filename);

    // initial and goal positions as Position's
    Position start = Position::maze.start(),
             goal = Position::maze.end();

    // call A* algorithm
    ecn::Astar(start, goal);

    // save final image
    Position::maze.saveSolution("cell");
    cv::waitKey(0);

}
