#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>

#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 *
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG &png, const Point &start, double tolerance)
: tolerance_(tolerance), image_(png), status_(png.height(), std::vector<bool>(png.width(), false)), start_(start)
{
  /** @todo [Part 1] */
  tolerance_ = tolerance;
  st_.push(start);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin()
{
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(start_, this);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end()
{
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(end_, this);
}


void DFS::clean() {
  Point p;
  while (!st_.empty()) {
    p = st_.top();
    if (status_.at(p.y).at(p.x) == true) st_.pop();
    else break;
  }
}


/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point &point)
{
  /** @todo [Part 1] */
  if (point.x < image_.width() || point.y < image_.height()) {
    st_.push(point);
  }
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop()
{
  /** @todo [Part 1] */
  clean();
  Point p = st_.top();
  st_.pop();
  status_.at(p.y).at(p.x) = true;
  return p;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek()
{
  /** @todo [Part 1] */
  clean();
  if (!st_.empty()) return st_.top();
  else return { UINT32_MAX, UINT32_MAX };
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty()
{
  /** @todo [Part 1] */
  clean();
  return st_.empty();
}


void DFS::ADD(const Point & p) {
  if (p.x < 0 || p.y < 0 || p.x >= status_.at(0).size() || p.y >= status_.size()) return;


  if (p.x + 1 < image_.width()  // right
      && calculateDelta(image_.getPixel(start_.x,start_.y), image_.getPixel(p.x+1,p.y)) < tolerance_) {
    st_.push( {p.x+1, p.y} );
  }

  if (p.y + 1 < image_.height()   // down
      && calculateDelta(image_.getPixel(start_.x,start_.y), image_.getPixel(p.x,p.y+1)) < tolerance_) {
    st_.push( {p.x, p.y+1} );
  }

  if (p.x - 1 >= 0 && p.x - 1 != 4294967295  // left
      && calculateDelta(image_.getPixel(start_.x,start_.y), image_.getPixel(p.x-1,p.y)) < tolerance_) {
    st_.push( {p.x-1, p.y} );
  }

  if (p.y - 1 >= 0 && p.y - 1 != 4294967295   // up
      && calculateDelta(image_.getPixel(start_.x,start_.y), image_.getPixel(p.x,p.y-1)) < tolerance_) {
    st_.push( {p.x, p.y-1} );
  }
  
}