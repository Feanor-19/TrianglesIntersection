#include <iostream>
#include <vector>
#include <list>

#include "triangles.hpp"
#include "driver.hpp"

int main()
{
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
