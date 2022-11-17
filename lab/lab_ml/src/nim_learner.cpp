/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */

#include "nim_learner.h"
#include <ctime>


/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true, true) {
  Vertex pattern1 = "p1-", pattern2 = "p2-";

  for (int i = 0; i <= 10; ++i) {
    g_.insertVertex(pattern1 + std::to_string(i));
    g_.insertVertex(pattern2 + std::to_string(i));
  }

  for (int i = 10; i >= 2; --i) {
    g_.insertEdge(pattern1 + std::to_string(i), pattern2 + std::to_string(i - 1));
    g_.insertEdge(pattern1 + std::to_string(i), pattern2 + std::to_string(i - 2));
    g_.setEdgeWeight(pattern1 + std::to_string(i), pattern2 + std::to_string(i - 1), 0);
    g_.setEdgeWeight(pattern1 + std::to_string(i), pattern2 + std::to_string(i - 2), 0);

    g_.insertEdge(pattern2 + std::to_string(i), pattern1 + std::to_string(i - 1));
    g_.insertEdge(pattern2 + std::to_string(i), pattern1 + std::to_string(i - 2));
    g_.setEdgeWeight(pattern2 + std::to_string(i), pattern1 + std::to_string(i - 1), 0);
    g_.setEdgeWeight(pattern2 + std::to_string(i), pattern1 + std::to_string(i - 2), 0);
  }

  g_.insertEdge(pattern1 + std::to_string(1), pattern2 + std::to_string(0));
  g_.setEdgeWeight(pattern1 + std::to_string(1), pattern2 + std::to_string(0), 0);

  g_.insertEdge(pattern2 + std::to_string(1), pattern1 + std::to_string(0));
  g_.setEdgeWeight(pattern2 + std::to_string(1), pattern1 + std::to_string(0), 0);

  startingVertex_ = "p1-" + std::to_string(startingTokens);
}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const {
  vector<Edge> path;
  Vertex p1 = "p1-", p2 = "p2-";
  string idx = startingVertex_.substr(3, 2);
  int start_idx = std::stoi(idx), end_idx = std::stoi(idx);
  int player = 1;
  while (end_idx != 0) {
    end_idx = start_idx - (rand() % 2) - 1;
    if (end_idx < 0) end_idx = 0;
    if (player == 1) path.push_back(g_.getEdge(p1 + std::to_string(start_idx), p2 + std::to_string(end_idx)));
    else path.push_back(g_.getEdge(p2 + std::to_string(start_idx), p1 + std::to_string(end_idx)));
    start_idx = end_idx;
    player = 3 - player;
  }
  return path;
}

/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {
  int p1_pt, p2_pt;
  if (path.back().dest == "p2-0") p1_pt = 1, p2_pt = -1;
  else p1_pt = -1, p2_pt = 1;
  for (auto & edge : path) {
    if (edge.source.at(1) == '1') g_.setEdgeWeight(edge.source, edge.dest, edge.getWeight() + p1_pt);
    else g_.setEdgeWeight(edge.source, edge.dest, edge.getWeight() + p2_pt);
  }
}

/**
 * Label the edges as "WIN" or "LOSE" based on a threshold.
 */
void NimLearner::labelEdgesFromThreshold(int threshold) {
  for (const Vertex & v : g_.getVertices()) {
    for (const Vertex & w : g_.getAdjacent(v)) {
      int weight = g_.getEdgeWeight(v, w);

      // Label all edges with positve weights as "WINPATH"
      if (weight > threshold)           { g_.setEdgeLabel(v, w, "WIN"); }
      else if (weight < -1 * threshold) { g_.setEdgeLabel(v, w, "LOSE"); }
    }
  }
}

/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
