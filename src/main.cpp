#include <iostream>
#include <vector>
#include <list>

#include "triangles.hpp"
#include "driver.hpp"

int main()
{
    using namespace Geom;

    // int i = 0;
    // try
    // {    
    //     Triangle3D t0{{165.52895828622218, 222.72828123187833, 978.3470960824499},
    //                   {160.59530093992382, 213.95406143687748, 985.3755839581144},
    //                   {171.7362017220332, 213.28021501073673, 991.2335227260002}};

    //     Triangle3D t1{{141.4149216639509, 221.26252675385675, 960.8945208300286},
    //                   {139.41445256218026, 224.01730295887015, 966.3445919990689},
    //                   {145.91301052216886, 220.4282693189779, 964.7589516425213}};

    //     std::cout << std::boolalpha;
    //     std::cout << t0.intersects_Triangle3D(t1) << std::endl;
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
        
        std::vector<index_t> indcs = get_inds_with_intscs(points, linesegs, triangles);

        for (auto ind : indcs)
        {
            std::cout << ind << " ";
        }
        std::cout << std::endl;
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
