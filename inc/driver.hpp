#pragma once

#include <vector>
#include <list>

#include "triangles.hpp"

namespace Driver
{
using index_t = size_t;

void get_input(std::vector<double> &out);

using ListPoint3D = std::list<std::pair<index_t, Geom::Point3D>>;
using ListLineSeg3D = std::list<std::pair<index_t, Geom::LineSeg3D>>;
using ListTriangle3D = std::list<std::pair<index_t, Geom::Triangle3D>>;  

void parse_input(ListPoint3D &points_out, ListLineSeg3D &linesegs_out,
                 ListTriangle3D &triangles_out, const std::vector<double> &inp);

std::vector<index_t> get_inds_with_intscs(ListPoint3D &points, 
                                          ListLineSeg3D &linesegs, 
                                          ListTriangle3D &triangles);
};
