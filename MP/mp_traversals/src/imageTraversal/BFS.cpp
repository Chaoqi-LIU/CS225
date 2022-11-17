#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) 
: tolerance_(tolerance), image_(png), status_(png.height(), std::vector<bool>(png.width(), false)), start_(start)
{  
  /** @todo [Part 1] */
  tolerance_ = tolerance;
  status_.at(start.y).at(start.x) = true;
  qu_.push(start);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(start_, this);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(end_, this);
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  if (point.x < image_.width() || point.y < image_.height()) {
    status_.at(point.y).at(point.x) = true;
    qu_.push(point);
  }
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  Point p = qu_.front();
  qu_.pop();
  return p;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() {
  /** @todo [Part 1] */
  if (!qu_.empty()) return qu_.front();
  else return { UINT32_MAX, UINT32_MAX };
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() {
  /** @todo [Part 1] */
  return qu_.empty();
}

void BFS::ADD(const Point & p) { 
  if (p.x < 0 || p.y < 0 || p.x >= status_.at(0).size() || p.y >= status_.size()) return;
  if (p.x + 1 < image_.width() 
      && !status_.at(p.y).at(p.x+1)
      && calculateDelta(image_.getPixel(start_.x,start_.y), image_.getPixel(p.x+1,p.y)) < tolerance_) {
    qu_.push( {p.x+1, p.y} );
    status_.at(p.y).at(p.x+1) = true;
  }
  if (p.y + 1 < image_.height() 
      && !status_.at(p.y+1).at(p.x)
      && calculateDelta(image_.getPixel(start_.x,start_.y), image_.getPixel(p.x,p.y+1)) < tolerance_) {
    qu_.push( {p.x, p.y+1} );
    status_.at(p.y+1).at(p.x) = true;
  }
  if (p.x - 1 >= 0 && p.x - 1 != 4294967295
      && !status_.at(p.y).at(p.x-1)
      && calculateDelta(image_.getPixel(start_.x,start_.y), image_.getPixel(p.x-1,p.y)) < tolerance_) {
    qu_.push( {p.x-1, p.y} );
    status_.at(p.y).at(p.x-1) = true;
  }
  if (p.y - 1 >= 0 && p.y - 1 != 4294967295
      && !status_.at(p.y-1).at(p.x)
      && calculateDelta(image_.getPixel(start_.x,start_.y), image_.getPixel(p.x,p.y-1)) < tolerance_) {
    qu_.push( {p.x, p.y-1} );
    status_.at(p.y-1).at(p.x) = true;
  }
}
