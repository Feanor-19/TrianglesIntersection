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
    //     std::cout << Triangle3D{{53.601698940104036, 9.911046958658488, 33.530820621308884}, 
    //                             {46.105144922688375, 60.52559357584846, 43.14589538851587}, 
    //                             {59.622204356886996, 25.76035347003011, 61.646959420729516}}
    //     .intersects_Triangle3D({{42.041039938496, 53.110147108889144, 21.18782405474603}, 
    //                             {50.13128491967562, 39.98454256291291, 39.56937754342547}, 
    //                             {40.004948446918384, 47.44790947146209, 48.61370188564293}}) << std::endl;
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
