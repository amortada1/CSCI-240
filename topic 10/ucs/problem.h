#include <cstdint>
#include <ostream>
#include <vector>

#ifndef PROBLEM_H
#define PROBLEM_H

struct State
{
    friend std::ostream& operator<<(std::ostream&, const State&);
    
    bool operator==(const State& s) const {return s.board == board;}
    bool operator!=(const State& s) const {return !(*this == s);}
    uint64_t get(uint8_t pos) const;

    State move(uint8_t pos) const;

    uint64_t board;
    uint8_t blankPos;
};

class Problem
{
public:
    State getInitialState() const;
    bool goalTest(const State&) const;
    static uint64_t stepCost(const State&, const State&);
    std::vector<State> adjacentStates(const State&) const;

private:
    const State initialState{0x854207613, 4};
    const State goalState{0x876543210, 0};

    const int8_t transitionTable[9][4]
    {
        1,  3, -1, -1, // 0
        0,  2,  4, -1, // 1
        1,  5, -1, -1, // 2
        0,  4,  6, -1, // 3
        1,  3,  5,  7, // 4
        2,  4,  8, -1, // 5
        3,  7, -1, -1, // 6
        4,  6,  8, -1, // 7
        5,  7, -1, -1  // 8
    }; 
};

#endif