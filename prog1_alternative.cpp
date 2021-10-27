#include <utility>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <cfloat>

using namespace std;



class Coordinate{

    public:

    int identifier;
    double x;
    double y;

    Coordinate()
    {
        identifier = -1;
        x = 0;
        y = 0;
    }

    Coordinate(int i, double x_pos, double y_pos)
    {
        identifier = i;
        x = x_pos;
        y = y_pos;
    }

    Coordinate( const Coordinate &c )
    {
        identifier = c.identifier;
        x = c.x;
        y = c.y;
    }

    void printWithoutId()
    {
        cout << x << ", " << y << "\n";
    }

    void printWithId()
    {
        cout << identifier << ", " << x << ", " << y << "\n";
    }
};



class Line{

    public:

    double slope;
    double y_intercept;
    Coordinate a;
    Coordinate b;

    Line(Coordinate c1, Coordinate c2)
    {
        slope = (c2.y - c1.y)/(c2.x - c1.x);
            //  y-y1 = m*(x-x1)
            //  y = m*(x-x1) + y1
        y_intercept = c1.y - (slope*c1.x);
        a = c1;
        b = c2;
    }

    void printEquation()
    {
        cout << "y = " << slope << "x + " << y_intercept << "\n";
    }

    void printEndpoints()
    {
        cout << "Endpoints of ";
        printEquation();
        a.printWithId();
        b.printWithId();
    }
    
    double getDistanceFrom(Coordinate c)
    {
        //taken from https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line
        //  ax + by + c = 0
        //  by = -ax - c
        //  a = -slope
        //  b = 1
        //  c = -y_intercept
        //positve distance is above the line, negative is below
        double numerator = -(slope * c.x) + c.y - y_intercept;
        double denominator = pow(slope,2) + 1;

        return numerator/sqrt(denominator);
    }

    pair<Coordinate,Coordinate> getFarthestFrom(vector< Coordinate > coordinates)
    {
        //stores the farthest points for the line and their distance
        double farthestDistanceAbove = 0;
        Coordinate farthestAbove(-1,DBL_MIN,DBL_MIN);

        double farthestDistanceBelow = 0;
        Coordinate farthestBelow(-1,DBL_MAX,DBL_MAX);

        //stores the farthest points for the line and their distance
        for (vector< Coordinate >::iterator it = coordinates.begin(); it != coordinates.end(); ++it)
        {
            double tempDistance = getDistanceFrom(*it);
            cout << it->identifier << ": " << tempDistance << "\n";
            
            // if distance from the line is 0 and it's not an endpoint:
            if(tempDistance == 0 && it->identifier != a.identifier && it->identifier != b.identifier )
            {
                coordinates.erase(it);
            }
            if(tempDistance > farthestDistanceAbove)
            {
                farthestDistanceAbove = tempDistance;
                farthestAbove = *it;
            }
            if(tempDistance < farthestDistanceBelow)
            {
                farthestDistanceBelow = tempDistance;
                farthestBelow = *it;
            }
        }
        /*
        cout << "\n";
        for (vector< Coordinate >::iterator it = coordinates.begin(); it != coordinates.end(); ++it)
        {
            it->printWithId();
        }
        */
        pair<Coordinate,Coordinate> farthests(farthestAbove, farthestBelow);
        return farthests;
    }

    Coordinate getFarthestAbove (vector< Coordinate > coordinates)
    {
        //stores the farthest points for the line and their distance
        double farthestDistanceAbove = 0;
        Coordinate farthestAbove(-1,DBL_MIN,DBL_MIN);

        //stores the farthest points for the line and their distance
        for (vector< Coordinate >::iterator it = coordinates.begin(); it != coordinates.end(); ++it)
        {
            double tempDistance = getDistanceFrom(*it);
            cout << it->identifier << ": " << tempDistance << "\n";
            
            // if distance from the line is 0 and it's not an endpoint:
            if(tempDistance == 0 && it->identifier != a.identifier && it->identifier != b.identifier )
            {
                coordinates.erase(it);
            }
            if(tempDistance > farthestDistanceAbove)
            {
                farthestDistanceAbove = tempDistance;
                farthestAbove = *it;
            }
        }
        /*
        cout << "\n";
        for (vector< Coordinate >::iterator it = coordinates.begin(); it != coordinates.end(); ++it)
        {
            it->printWithId();
        }
        */
        return farthestAbove;
    }

    Coordinate getFarthestBelow (vector< Coordinate > coordinates)
    {
        //stores the farthest points for the line and their distance
        double farthestDistanceBelow = 0;
        Coordinate farthestBelow(-1,DBL_MAX,DBL_MAX);

        //stores the farthest points for the line and their distance
        for (vector< Coordinate >::iterator it = coordinates.begin(); it != coordinates.end(); ++it)
        {
            double tempDistance = getDistanceFrom(*it);
            cout << it->identifier << ": " << tempDistance << "\n";
            
            // if distance from the line is 0 and it's not an endpoint:
            if(tempDistance == 0 && it->identifier != a.identifier && it->identifier != b.identifier )
            {
                coordinates.erase(it);
            }
            if(tempDistance < farthestDistanceBelow)
            {
                farthestDistanceBelow = tempDistance;
                farthestBelow = *it;
            }
        }
        /*
        cout << "\n";
        for (vector< Coordinate >::iterator it = coordinates.begin(); it != coordinates.end(); ++it)
        {
            it->printWithId();
        }
        */
        return farthestBelow;
    }

};



/*
class Triangle {

    public:
        Line a;
        Line b;
        Line c;
};
*/



int main()
{    
    //obtain the coordinates of all points as a pair
    vector< Coordinate > coordinates;
    vector< Coordinate > hull;
    
    //temporary veriables for storing an entry
    std::string input;
    int num_entries;
    double x_input;
    double y_input;

    //input the number of entries to add to the array
    cin >> input;
    num_entries = stoi(input);

    //input each entry
    for(int i = 0; i<num_entries; i++)
    {
        //input x
        cin >> input;
        input = input.substr(0,input.length()-1);
        x_input = stod(input);
        //input y
        cin >> input;
        y_input = stod(input);
        //combine the two into a coordinate
        Coordinate coord_input(i, x_input, y_input);

        coordinates.push_back( coord_input );
        hull.push_back( coord_input );

    }

    for (vector< Coordinate >::iterator it = coordinates.begin(); it != coordinates.end(); ++it)
        it->printWithId();
    cout << "\n";

    //gather the largest and smallest y positions
    //if there's a tie, get the smallest x positions
    Coordinate smallestY(-1,DBL_MAX,DBL_MAX);
    Coordinate largestY(-1,DBL_MIN,DBL_MIN);

    int loop_index = 0;
    
    for (std::vector< Coordinate >::iterator it = coordinates.begin(); it != coordinates.end(); ++it)
    {
        if(smallestY.identifier == -1)
        {
            smallestY = *it;
            largestY = *it;
        }
        else if(it->y < smallestY.y)
        {
            smallestY = *it;
        }
        else if(it->y > largestY.y)
        {
            largestY = *it;
        }
        else if(it->y == smallestY.y && it->x < smallestY.x)
        {
            smallestY = *it;
        }
        else if(it->y == largestY.y && it->x > largestY.x)
        {
            largestY = *it;
        }
        
    }
    
    //generating line
    Line mainLine(smallestY, largestY);
    mainLine.printEndpoints();
    cout << "\n";
    
    //getting farthest points from line
    /*
        pair<Coordinate,Coordinate> farthests = mainLine.getFarthestFrom(coordinates,smallestY,largestY);
        cout << "\nfarthest from the line= \n";
        cout << "above:";
        farthests.first.printWithId();
        cout << "below:";
        farthests.second.printWithId();
        cout << "\n";
    */

    //create a hull
    pair< triangle, triangle > firstHull =
        mainLine.createHullFrom(coordinates);
    
    addLine(lines, firstHull.first.first);
    addLine(lines, firstHull.first.second);
    addLine(lines, firstHull.second.first);
    addLine(lines, firstHull.second.second);
    
    cout << "\n369\n\n";
    
    for (vector< Line >::iterator it = lines.begin(); it != lines.end(); it = it)
    {
        it->printEndpoints();
        pair<Line,Line> newHull( it->createOneSidedHullFrom(coordinates) );
        
        if( addLine(lines, newHull.first) && addLine(lines, newHull.first) )
        {
            lines.erase(it);
        }
        else
        {
            it++;
        }
    }
    

    
    return 0;
}