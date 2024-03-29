﻿#include <iostream>
#include <np_solver/dataset_repository.hpp>
#include <np_solver/graphs/di_graph.hpp>
#include <np_solver/graphs/graph_distance.hpp>
#include <np_solver/graphs/u_graph.hpp>
#include <np_solver/isomorphism.hpp>
#include <np_solver/permutation_runner.hpp>
#include <np_solver/solvers/max_independent_set.hpp>
#include <np_solver/solvers/max_clique.hpp>

namespace npim
{
void run()
{
    constexpr int v = 7;

	auto datastore = DatasetRepository("result_v7.csv");

	// filters
    auto duplicate_filter = std::make_shared<filters::DuplicateFilter<graphs::UGraph<v>>>();

	// solvers
    auto max_ind_set_solver = std::make_shared<solvers::MaxIndependentSet<graphs::UGraph<v>>>();
    auto max_clique_solver = std::make_shared<solvers::MaxClique<graphs::UGraph<v>>>();

    auto perm_runner =
        IsomorphicGraphPermutationRunner<graphs::UGraph<v>>({ duplicate_filter },
                                                            { max_ind_set_solver, max_clique_solver });
    auto result = perm_runner.solve_all();
    datastore.save_dataset(result);
	
	// todo:
	// Serialize data.
	// csv format: graph id, problem_#1_best_solution, problem_#2_best_solution
	// file name include V

}
} // namespace npim

int main()
{
    npim::run();
    return 0;
}