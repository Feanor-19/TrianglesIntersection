#include <iostream>
#include <vector>
#include <list>

#include "triangles.hpp"
#include "driver.hpp"

int main()
{
    // using namespace Geom;

    // int i = 0;
    // try
    // {    
    //     std::cout << std::boolalpha;
    //     std::cout << Triangle3D{{0,0,0}, {1,0,0}, {0,1,0}}
    //     .intersects_Triangle3D({{0,0.5,-0.5}, {0,0.5,0.5}, {-1,0,0}}) << std::endl;
    // }
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << '\n';
    // }
    
    try
    {   
        using namespace Driver;

        std::vector<double> inp;
        get_input(inp, std::cin);

        ListPoint3D points;
        ListLineSeg3D linesegs;
        ListTriangle3D triangles;
        parse_input(points, linesegs, triangles, inp);
        
        std::set<index_t> indcs = get_inds_with_intscs(points, linesegs, triangles);

        for (auto ind : indcs)
        {
            std::cout << ind << std::endl;
        }
    }
    catch(const std::logic_error& e)
    {
        std::cerr << "LOGIC ERROR: " << e.what() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
 
    return 0;
}
