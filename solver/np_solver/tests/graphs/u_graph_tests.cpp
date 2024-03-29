#include <doctest/doctest.h>
#include <np_solver/graphs/u_graph.hpp>

namespace npim
{

TEST_SUITE("has_edge")
{
    TEST_CASE("Empty graph")
    {
        auto g = graphs::UGraph<5>(0);
        for (auto i = 0; i < g.vertices(); i++)
        {
            for (auto j = i + 1; j < g.vertices(); j++)
            {
                CHECK(!g.has_edge(i, j));
                CHECK(!g.has_edge(j, i));
                CHECK(g.index(i, j) == g.index(j, i));
            }
        }
    }

    TEST_CASE("Fully Connected Graph")
    {
        auto g = graphs::UGraph<5>(graphs::UGraph<5>::number_of_graphs() - 1); // all ones
        for (auto i = 0; i < g.vertices(); i++)
        {
            for (auto j = i + 1; j < g.vertices(); j++)
            {
                CHECK(g.has_edge(i, j));
                CHECK(g.has_edge(j, i));
            }
        }
    }

    TEST_CASE("General Graph")
    {
        auto g = graphs::UGraph<5>(503);
        for (auto i = 0; i < g.vertices(); i++)
        {
            for (auto j = i + 1; j < g.vertices(); j++)
            {
                CHECK(g.has_edge(i, j) == g.has_edge(i, j));
            }
        }
    }
}

TEST_SUITE("index")
{
    TEST_CASE("Testing index is same for (i,j) and (j,i)")
    {
        auto g = graphs::UGraph<5>(0);
        for (auto i = 0; i < g.vertices(); i++)
        {
            for (auto j = i + 1; j < g.vertices(); j++)
            {
                CHECK(g.index(i, j) == g.index(j, i));
            }
        }
    }
}
} // namespace npim