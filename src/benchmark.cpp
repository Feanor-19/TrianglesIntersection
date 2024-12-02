#include <benchmark/benchmark.h>

#include <iostream>
#include <fstream>

#include "triangles.hpp"
#include "driver.hpp"

template <class ...Args>
void BM(benchmark::State &state, Args&&... args)
{
    //benchmark arg setup
    auto args_tuple = std::make_tuple(std::forward<Args>(args)...);
    std::string bench_data_filename = std::get<0>(args_tuple); 

    //setup
    size_t cache_size = 0, queries_cnt = 0;

    std::ifstream file(bench_data_filename);
    if (!file.is_open())
    {
        state.SkipWithError("Can't open file");
        return;
    }

    for (auto _ : state)
    {
        //this code is timed
        using namespace Driver;

        std::vector<double> inp;
        get_input(inp, file);

        ListPoint3D points;
        ListLineSeg3D linesegs;
        ListTriangle3D triangles;
        parse_input(points, linesegs, triangles, inp);

        std::cout << "Points: " << points.size() << std::endl;
        std::cout << "Line segments: " << linesegs.size() << std::endl;
        std::cout << "Triangles: " << triangles.size() << std::endl;
        
        std::vector<index_t> indcs = get_inds_with_intscs(points, linesegs, triangles);

        for (auto ind : indcs)
        {
            std::cout << ind << " ";
        }
        std::cout << std::endl;

        file.clear();
        file.seekg(0, std::ios::beg);
    }
}

BENCHMARK_CAPTURE(BM, full_rand_10000, std::string("benchmark_data/full_rand_10000.dat"));

BENCHMARK_CAPTURE(BM, set_trs_10000, std::string("benchmark_data/set_trs_10000.dat"));

BENCHMARK_MAIN();