#include "driver.hpp"

#include <iostream>

void Driver::get_input(std::vector<double> &out, std::istream& stream)
{
    int N_inp = 0;
    stream >> N_inp;
    if (!stream.good() || N_inp <= 0)
        throw std::runtime_error("Wrong input");

    int N_points = N_inp * 9;

    out.clear();
    out.reserve(N_points);

    double input = 0;
    while (N_points-- && stream >> input)
        out.push_back(input);

    if (N_points > 0 || !stream)
        throw std::runtime_error("Not full input");
}

void Driver::parse_input(ListPoint3D &points_out, ListLineSeg3D &linesegs_out,
                         ListTriangle3D &triangles_out, const std::vector<double> &inp)
{
    using namespace Geom;
    index_t ind = 0;
    for (auto it = inp.begin(); it != inp.end(); it+=9)
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

        Vector3D v12 = p2 - p1;
        Vector3D v13 = p3 - p1;
        if (!cross_prod(v12, v13).is_zero())
            triangles_out.push_back(std::make_pair(ind++, Triangle3D{p1, p2, p3}));
        else
        {
            scalar_t dot = dot_prod(v12, v13);
            if (leq(dot, 0))
                linesegs_out.push_back(std::make_pair(ind++, LineSeg3D{p3, p2}));
            else if (leq(dot, v12.len()*v12.len()))
                linesegs_out.push_back(std::make_pair(ind++, LineSeg3D{p1, p2}));
            else 
                linesegs_out.push_back(std::make_pair(ind++, LineSeg3D{p1, p3}));
        }
    }
}

std::set<Driver::index_t> Driver::get_inds_with_intscs(ListPoint3D &points, 
                                                       ListLineSeg3D &linesegs, 
                                                       ListTriangle3D &triangles)
{
    using namespace Geom;

    std::set<index_t> indcs;

    for (auto it_out = points.begin(); it_out != points.end(); it_out++)
    {
        Point3D point = it_out->second;
        bool found = false;
        for (auto it_in = std::next(it_out); it_in != points.end(); it_in++)
        {
            if (it_in->second == it_out->second)
            {
                indcs.insert(it_in->first);
                found = true;
            }
        }

        for (auto it_lineseg = linesegs.begin(); it_lineseg != linesegs.end(); it_lineseg++)
        {
            if (it_lineseg->second.has_point(point)) 
            {
                indcs.insert(it_lineseg->first);
                found = true;
            }
        }

        for (auto it_tr = triangles.begin(); it_tr != triangles.end(); it_tr++)
        {
            if (it_tr->second.has_point(point)) 
            {
                indcs.insert(it_tr->first);
                found = true;
            }
        }
        if (found) indcs.insert(it_out->first);
    }

    for (auto it_out = linesegs.begin(); it_out != linesegs.end(); it_out++)
    {
        bool found = false;
        for (auto it_in = std::next(it_out); it_in != linesegs.end(); it_in++)
        {
            if (it_out->second.intersects_LineSeg3D(it_in->second)) 
            {
                indcs.insert(it_in->first);
                found = true;
            }
        }

        for (auto it_tr = triangles.begin(); it_tr != triangles.end(); it_tr++)
        {
            if (it_tr->second.intersects_LineSeg3D(it_out->second))
            {
                indcs.insert(it_tr->first);
                found = true;
            }
        }
        if (found) indcs.insert(it_out->first);
    }

    for (auto it_out = triangles.begin(); it_out != triangles.end(); it_out++)
    {   
        bool found = false;
        for (auto it_in = std::next(it_out); it_in != triangles.end(); it_in++)
        {
            if (it_in->second.intersects_Triangle3D(it_out->second))
            {
                indcs.insert(it_in->first);
                found = true;
            }
        }
        if (found) indcs.insert(it_out->first);
    }

    return indcs;
}