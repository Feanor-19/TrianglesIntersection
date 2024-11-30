#include <iostream>
#include <vector>
#include <list>

#include "triangles.hpp"

namespace Driver
{
using index_t = size_t;

void get_input(std::vector<double> &out);

void parse_input(std::list<std::pair<index_t, Geom::Point3D>> &points_out, 
                 std::list<std::pair<index_t, Geom::LineSeg3D>> &linesegs_out,
                 std::list<std::pair<index_t, Geom::Triangle3D>> &triangles_out,
                 const std::vector<double> &inp);

std::vector<index_t> 
get_inds_with_intscs(std::list<std::pair<index_t, Geom::Point3D>> &points, 
                     std::list<std::pair<index_t, Geom::LineSeg3D>> &linesegs,
                     std::list<std::pair<index_t, Geom::Triangle3D>> &triangles);
};

int main()
{
    using namespace Geom;

    // int i = 0;

    // Triangle3D t0{{0,0,0}, {1,0,0}, {0,1,0}};

    // std::cout << std::boolalpha;
    // std::cout << t0.intersects_Triangle3D({{0,1,0}, {0,1,1}, {0,2,1}}) << std::endl;


    // first func reads input, gets std::vector<std::array<<std::array<double, 3>>>> ?? just nine doubles for
    // each triangle... or just "raw" std::vector of size N * 9

    // second func parses it into three std::vectors, one with points, second one with linesegs, third one 
    // with triangles; elements of these vectors are pairs (bc we need to remember the number)

    // third func gets these three vectors and checks intersections
 
    return 0;
}

void Driver::get_input(std::vector<double> &out)
{
    int N = 0;
    std::cin >> N;
    if (!std::cin.good() || N <= 0 || N % 9 != 0)
        throw std::runtime_error("Wrong input");

    out.clear();
    out.reserve(N);

    double input = 0;
    while (N-- && std::cin >> input)
        out.push_back(input);

    if (N > 0 || !std::cin)
        throw std::runtime_error("Not full input");
}

void Driver::parse_input(std::list<std::pair<index_t, Geom::Point3D>> &points_out, 
                         std::list<std::pair<index_t, Geom::LineSeg3D>> &linesegs_out,
                         std::list<std::pair<index_t, Geom::Triangle3D>> &triangles_out,
                         const std::vector<double> &inp)
{
    using namespace Geom;
    index_t ind = 0;
    for (auto it = inp.begin(); it+8 != inp.end(); it+=9)
    {
        Point3D p1{*it, *(it+1), *(it+2)}, p2{*(it+3), *(it+4), *(it+5)}, p3{*(it+6), *(it+7), *(it+8)};
        int eq_cnt = (p1 == p2) + (p2 == p3) + (p1 == p3);
        if (eq_cnt == 3)
        {
            points_out.push_back(std::make_pair(ind++, p1));
            continue;
        }

        if (eq_cnt == 1)
        {
            if (p1 == p2)
                linesegs_out.push_back(std::make_pair(ind++, LineSeg3D{p1, p3}));
            else if (p1 == p3)
                linesegs_out.push_back(std::make_pair(ind++, LineSeg3D{p1, p2}));
            else
                linesegs_out.push_back(std::make_pair(ind++, LineSeg3D{p2, p3}));
            continue;
        }

        triangles_out.push_back(std::make_pair(ind++, Triangle3D{p1, p2, p3}));
    }
}

std::vector<Driver::index_t> 
Driver::get_inds_with_intscs(std::list<std::pair<index_t, Geom::Point3D>> &points, 
                             std::list<std::pair<index_t, Geom::LineSeg3D>> &linesegs,
                             std::list<std::pair<index_t, Geom::Triangle3D>> &triangles)
{
    // TODO ЭТОТ УЖАС НЕ ПРОВЕРЯЕТ ПЕРЕСЕЧЕНИЯ ВНУТРИ МНОЖЕСТВА ОДНОГО ТИПА!!!
    using namespace Geom;

    std::vector<index_t> indcs;
    indcs.reserve(points.size() + linesegs.size() + triangles.size());

    //REVIEW - попытка сократить повторяющиеся маленькие кусочки кода ниже
    auto push_and_erase = [&indcs]<typename List>(List list, typename List::iterator it)
    {
        indcs.push_back(it->first);
        list.erase(it);
    };
    
    for (auto it_out = points.begin(); it_out != points.end(); it_out++)
    {
        Point3D point = it_out->second;
        for (auto it_in = std::next(it_out); it_in != points.end(); it_in++)
        {
            if (it_in->second == it_out->second){ push_and_erase(points, it_in); goto found;}
        }

        for (auto it_lineseg = linesegs.begin(); it_lineseg != linesegs.end(); it_lineseg++)
        {
            if (it_lineseg->second.has_point(it_out->second))
                std::cout << ind_point << " " << ind_lineseg;
        }

        for (auto [ind_triangle, triangle] : triangles)
        {
            if (triangle.has_point(point))
                std::cout << ind_point << " " << ind_triangle;
        }

        continue;

        found: 
        indcs.push_back(it_out->first);
    }

    for (auto [ind_lineseg, lineseg] : linesegs)
    {
        for (auto [ind_triangle, triangle] : triangles)
        {
            if (triangle.intersects_LineSeg3D(lineseg))
                std::cout << ind_lineseg << " " << ind_triangle;
        }
    }
}