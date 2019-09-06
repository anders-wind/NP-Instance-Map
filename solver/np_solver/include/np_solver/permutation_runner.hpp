
#pragma once
#include <np_solver/filters/instance_filter.hpp>
#include <np_solver/solvers/instance_solver.hpp>
#include <np_solver/graphs/graph_base.hpp>
#include <map>
#include <set>

namespace npim
{


template <class SpecificGraph>
class PermutationRunner
{
    protected:
    std::vector<std::shared_ptr<filters::InstanceFilter<SpecificGraph>>> filters;
    std::vector < std::shared_ptr<solvers::InstanceSolver<SpecificGraph>>> solvers;

	public:

    PermutationRunner(const std::vector < std::shared_ptr<filters::InstanceFilter<SpecificGraph>>> & filters,
                      const std::vector < std::shared_ptr<solvers::InstanceSolver<SpecificGraph>>> & solvers)
      : filters(filters), solvers(solvers)
    {
    }

	bool filter_check(const graphs::Graph<SpecificGraph>& g) const
    {
        auto should_solve = true;
        for (auto filter : filters)
        {
            should_solve &= filter->include_instance(g);
        }
        return should_solve;
	}

	bool solve_graph(const graphs::Graph<SpecificGraph>& g,
                     std::map<uint64_t, std::vector<std::unique_ptr<InstanceSolution>>>& stats) const
    {
        stats[g.edge_bits()] = std::vector<std::unique_ptr<InstanceSolution>>();
        for (const auto& solver : solvers)
        {
            stats[g.edge_bits()].push_back(solver->solve(g));
        }
    }

	void solve_all() const
	{
        constexpr uint64_t V = SpecificGraph::vertices();
        constexpr uint64_t number_of_graphs = SpecificGraph::number_of_graphs();
		std::cout << "Processing #" << number_of_graphs << " graphs" << std::endl;

		auto stats = std::map<uint64_t, std::vector<std::unique_ptr<InstanceSolution>>>();
        auto all_graphs = std::set<uint64_t>();
        uint64_t instance = 0;
        for (auto i = 1; i <= V; i++)
        {
            std::cout << "V: " << i << std::endl;
			do {
                auto g = SpecificGraph(instance);
                if (filter_check(g))
                {
                    all_graphs.insert(instance);
                    std::cout << g.edges << std::endl;
                    solve_graph(g, stats);
                }
                instance++;
            } while (instance != (1 << (i*(i-1)/2)));
		}
        std::cout << std::endl;
		print_stats(stats);
	}


	private:

	void print_stats(const std::map<uint64_t, std::vector<std::unique_ptr<InstanceSolution>>>& stats) const
    {
        constexpr uint64_t E = SpecificGraph::max_edges();
        std::cout << "Solutions:" << std::endl;
        for (const auto& pair : stats)
        {
            auto graph = pair.first;
            for (const auto& solution : pair.second)
            {
                std::cout << std::bitset<E>(graph) << " (" << graph << ") " << std::endl;
            }
        }
        std::cout << stats.size() << std::endl;
    }
};

} // namespace npim