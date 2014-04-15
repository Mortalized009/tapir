#ifndef ROCKSAMPLE_OPTIONS_HPP_
#define ROCKSAMPLE_OPTIONS_HPP_

#include <sstream>                      // for basic_stringbuf<>::int_type, basic_stringbuf<>::pos_type, basic_stringbuf<>::__streambuf_type
#include <string>                       // for string

#include <boost/program_options.hpp>    // for value, options_description, options_description_easy_init, typed_value

#include "problems/shared/ProgramOptions.hpp"  // for ProgramOptions

namespace po = boost::program_options;

namespace rocksample {
class RockSampleOptions : public ProgramOptions {
    /** Returns configurations options for the RockSample POMDP */
    po::options_description getProblemOptions() {
        po::options_description problem(
                "Settings specific to the RockSample POMDP");
        problem.add(ProgramOptions::getProblemOptions());
        problem.add_options()
            ("problem.mapPath,m", po::value<std::string>(), "path to map file")
            ("problem.goodRockReward", po::value<double>(),
                "reward for sampling a good rock")
            ("problem.badRockPenalty", po::value<double>(),
                "penalty for sampling a bad rock")
            ("problem.exitReward", po::value<double>(),
                "reward for moving into the exit area")
            ("problem.illegalMovePenalty", po::value<double>(),
                "penalty for making an illegal move")
            ("problem.halfEfficiencyDistance,d0", po::value<double>(),
                "half efficiency distance d0; sensor efficiency = 2^(-d/d0)");
        return problem;
    }

    /** Returns configuration options for the RockSample heuristic */
    po::options_description getHeuristicOptions() {
        po::options_description heuristics("RockSample heuristic configuration");
        heuristics.add(ProgramOptions::getHeuristicOptions());
        heuristics.add_options()
            ("heuristics.useOnlyLegal", po::value<bool>()->default_value(false)->implicit_value(true),
                "whether to only use legal actions")
            ("heuristics.usePreferredInit", po::value<bool>()->default_value(false)->implicit_value(true),
                "whether to only use legal actions")
            ("heuristics.preferredQValue", po::value<double>()->default_value(25.0),
                "the initial q-value for preferred actions")
            ("heuristics.preferredVisitCount", po::value<long>()->default_value(10),
                "the initial visit count for preferred actions")
            ("heuristics.exactMdp,e", po::value<bool>()->default_value(false)->implicit_value(true),
                "whether to use an exact MDP solution");
        return heuristics;
    }
};
} /* namespace rocksample */

#endif /* ROCKSAMPLE_OPTIONS_HPP_ */
