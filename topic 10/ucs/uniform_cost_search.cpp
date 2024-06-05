#include "uniform_cost_search.h"

std::vector<State> UniformCostSearch::start(const Problem& p) 
{
    Node* node {createNode(p, 0, p.getInitialState())};
    frontier.push(node);

    while (!frontier.empty())
    {
        node = frontier.top();
        frontier.pop();

        if (p.goalTest(node->state))
        {
            createPath(node);
            return shortestPath;
        }

        explored.insert(node);

        for (State s : p.adjacentStates(node->state))
        {
            Node* adj{createNode(p, node, s)};
            if (explored.find(adj) != explored.end()) 
            {
                delete adj;
                continue;
            }

            frontier.push(adj);
        } 
    }

    return shortestPath;
}

Node* UniformCostSearch::createNode(Problem p, Node* n, const State& s) const
{
    uint64_t newPathCost{};
    if (n) newPathCost = n->pathCost + p.stepCost(n->state, s);
    return new Node{s, newPathCost, n};
}

void UniformCostSearch::createPath(const Node* n) const
{   
    if (n == nullptr) return;

    createPath(n->parent);



    shortestPath.push_back(n->state);
}

