/**
 * @file DFS.h
 */

#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <stack>
#include <vector>

#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A depth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class DFS : public ImageTraversal {
public:
  DFS(const PNG & png, const Point & start, double tolerance);

  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();

  void add(const Point & point);
  Point pop();
  Point peek();
  bool empty();
  void ADD(const Point & pt);
  void clean();

private:
	/** @todo [Part 1] */
	/** add private members here*/
  std::stack<Point> st_;
  double tolerance_;
  PNG image_;
  std::vector<std::vector<bool>> status_;
  Point start_;
  Point end_ = {UINT32_MAX, UINT32_MAX};
};