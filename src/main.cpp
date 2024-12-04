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
    //     // Triangle3D t0{{331.45348239878297, 946.1053420056721, 952.8130103892371},
    //     //               {329.3675304584714, 950.149787753491, 955.6291984713811},
    //     //               {329.22924771213985, 947.6454053402665, 958.2453650715645}};

    //     // Triangle3D t1{{505.04444670411795, 712.7749969460839, 644.9757087997505},
    //     //               {503.8788993236424, 706.4415126134443, 636.7896903311087},
    //     //               {504.6340512609518, 712.8683327073852, 645.114914183536}};

    //     // Triangle3D t0{{262.8291506593867, 738.8902664246145, 184.07270169509806},
    //     //               {263.92326377188147, 744.9257758705741, 191.98754127204313},
    //     //               {255.05569075140053, 745.0833699978822, 178.5923009811677}};

    //     // Triangle3D t1{{271.50486167797413, 743.7270637671139, 180.50289912002347},
    //     //               {263.62623527710156, 745.1230254904556, 175.10729737918282},
    //     //               {261.92930739757537, 741.4502078216377, 187.08101408287405}};

    //     std::cout << std::boolalpha;
    //     std::cout << Triangle3D{{0,0,0}, {1,0,0}, {0,1,0}}
    //  .intersects_Triangle3D({{0.5,0.5,0}, {1,1,1}, {0,2,1}})<< std::endl;
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
