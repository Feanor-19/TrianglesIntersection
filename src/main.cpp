#include <iostream>
#include <vector>

#include "triangles.hpp"

namespace Driver
{
void get_input(std::vector<double> &out);

void parse_input(std::vector<std::pair<size_t, Geom::Point3D>> &points_out, 
                 std::vector<std::pair<size_t, Geom::LineSeg3D>> &linesegs_out,
                 std::vector<std::pair<size_t, Geom::Triangle3D>> &triangles_out,
                 const std::vector<double> &inp);

void print_intersections(std::vector<std::pair<size_t, Geom::Point3D>> &points, 
                         std::vector<std::pair<size_t, Geom::LineSeg3D>> &linesegs,
                         std::vector<std::pair<size_t, Geom::Triangle3D>> &triangles);
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

void Driver::parse_input(std::vector<std::pair<size_t, Geom::Point3D>> &points_out, 
                 std::vector<std::pair<size_t, Geom::LineSeg3D>> &linesegs_out,
                 std::vector<std::pair<size_t, Geom::Triangle3D>> &triangles_out,
                 const std::vector<double> &inp)
{
    using namespace Geom;
    size_t ind = 0;
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

void Driver::print_intersections(const std::vector<std::pair<size_t, Geom::Point3D>> &points, 
                                 const std::vector<std::pair<size_t, Geom::LineSeg3D>> &linesegs,
                                 const std::vector<std::pair<size_t, Geom::Triangle3D>> &triangles)
{
    // TODO ЭТОТ УЖАС НЕ ПРОВЕРЯЕТ ПЕРЕСЕЧЕНИЯ ВНУТРИ МНОЖЕСТВА ОДНОГО ТИПА!!!

    for (auto [ind_point, point] : points)
    {
        for (auto [ind_lineseg, lineseg] : linesegs)
        {
            if (lineseg.has_point(point))
                std::cout << ind_point << " " << ind_lineseg;
        }

        for (auto [ind_triangle, triangle] : triangles)
        {
            if (triangle.has_point(point))
                std::cout << ind_point << " " << ind_triangle;
        }
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