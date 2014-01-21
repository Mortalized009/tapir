#include "TagState.hpp"

#include <cstddef>                      // for size_t

#include <functional>   // for hash
#include <ostream>                      // for operator<<, ostream, basic_ostream>
#include <vector>

#include "problems/shared/GridPosition.hpp"  // for GridPosition, operator==, operator<<
#include "solver/State.hpp"             // for State

namespace tag {
template<class T>
void hash_combine(std::size_t &seed, T const &v) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

TagState::TagState(GridPosition robotPos, GridPosition opponentPos,
        bool _isTagged) :
    solver::VectorState(),
    robotPos_(robotPos),
    opponentPos_(opponentPos),
    isTagged_(_isTagged) {
}

TagState::TagState(TagState const &other) :
    solver::VectorState(),
    robotPos_(other.robotPos_),
    opponentPos_(other.opponentPos_),
    isTagged_(other.isTagged_) {
}

double TagState::distanceTo(State const &otherState) const {
    TagState const *otherTagState =
        static_cast<TagState const *>(&otherState);
    double distance = robotPos_.manhattanDistanceTo(otherTagState->robotPos_);
    distance += opponentPos_.manhattanDistanceTo(otherTagState->opponentPos_);
    distance += (isTagged_ == otherTagState->isTagged_) ? 0 : 1;
    return distance;
}

bool TagState::equals(State const &otherState) const {
    TagState const *otherTagState =
        static_cast<TagState const *>(&otherState);
    return (robotPos_ == otherTagState->robotPos_
            && opponentPos_ == otherTagState->opponentPos_
            && isTagged_ == otherTagState->isTagged_);
}

std::size_t TagState::hash() const {
    std::size_t hashValue = 0;
    hash_combine(hashValue, robotPos_.i);
    hash_combine(hashValue, robotPos_.j);
    hash_combine(hashValue, opponentPos_.i);
    hash_combine(hashValue, opponentPos_.j);
    hash_combine(hashValue, isTagged_);
    return hashValue;
}

std::vector<double> TagState::asVector() const {
    std::vector<double> vec(5);
    vec[0] = robotPos_.i;
    vec[1] = robotPos_.j;
    vec[2] = opponentPos_.i;
    vec[3] = opponentPos_.j;
    vec[4] = isTagged_ ? 1 : 0;
    return vec;
}

void TagState::print(std::ostream &os) const {
    os << "ROBOT: " << robotPos_ << " OPPONENT: " << opponentPos_;
    if (isTagged_) {
        os << " TAGGED!";
    }
}
} /* namespace tag */
