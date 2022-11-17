/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */


using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */

    return first[curDim] == second[curDim] ? first < second : first[curDim] < second[curDim]; 
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */

    double current_best_dis = 0, potential_dis = 0;
    
    // find current_best_dis and potential_dis
    for (int dim = 0; dim < Dim; ++dim) {
      current_best_dis += pow((target[dim] - currentBest[dim]), 2);
      potential_dis += pow((target[dim] - potential[dim]), 2);
    }
    
    return current_best_dis == potential_dis ? potential < currentBest : potential_dis < current_best_dis;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    points_ = newPoints;
    size = newPoints.size();
    root = BuildKDTree(0, 0, points_.size() - 1);
}



template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  if (this == &other) return;

  points_ = other.GetPoints();
  size = points_.size();
  root = BuildKDTree(1 % Dim, 0, points_.size() - 1);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */

  if (this == &rhs) return *this;

  points_ = rhs.points_;
  size = points_.size();
  root = BuildKDTree(1 % Dim, 0, points_.size() - 1);
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */ 
  DeleteKDTree(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    double arr[Dim];
    for (int i = 0; i < Dim; ++i) arr[i] = std::numeric_limits<double>::max();
    Point<Dim> best(arr);
    double best_dis = std::numeric_limits<double>::max();
    findNearestNeighbor(root, query, 0, best, best_dis);
    return best;
}



