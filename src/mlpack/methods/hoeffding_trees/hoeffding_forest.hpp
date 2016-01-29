/**
 * @file hoeffding_forest.hpp
 * @author Ryan Curtin
 *
 * Implementation of a bagged random forest of Hoeffding trees.
 */
#ifndef __MLPACK_METHODS_HOEFFDING_TREE_HOEFFDING_FOREST_HPP
#define __MLPACK_METHODS_HOEFFDING_TREE_HOEFFDING_FOREST_HPP

#include <mlpack/core.hpp>
#include "hoeffding_tree.hpp"

namespace mlpack {
namespace tree {

template<typename HoeffdingTreeType>
class HoeffdingForest
{
 public:
  HoeffdingForest(const size_t forestSize,
                  const size_t numClasses,
                  data::DatasetInfo& info);

  /**
   * Create a Hoeffding forest, using the given tree's parameters for each of
   * the trees in the forest.  The given tree should have the number of classes
   * set correctly, 
   *
   * @param tree Exemplar tree to take parameters from.
   * @param forestSize Number of trees in the forest.
   * @param */

  ~HoeffdingForest();

  template<typename VecType>
  void Train(const VecType& point, const size_t label);

  template<typename MatType>
  void Train(const MatType& data,
             const arma::Row<size_t>& labels,
             const bool batchTraining = true);

  template<typename VecType>
  size_t Classify(const VecType& point) const;

  template<typename VecType>
  void Classify(const VecType& point, size_t& prediction, double& probability)
      const;

  template<typename MatType>
  void Classify(const MatType& data,
                arma::Row<size_t>& predictions) const;

  template<typename MatType>
  void Classify(const MatType& data,
                arma::Row<size_t>& predictions,
                arma::rowvec& probabilities) const;

  size_t NumTrees() const { return trees.size(); }

  template<typename Archive>
  void Serialize(Archive& ar, const unsigned int /* version */);

 private:
  std::vector<HoeffdingTreeType> trees;

  std::vector<arma::Col<size_t>> dimensions;
  arma::Col<size_t> dimensionCounts;

  const data::DatasetInfo* info;
  bool ownsInfo;

  size_t numClasses;
};

} // namespace tree
} // namespace mlpack

// Include implementation.
#include "hoeffding_forest_impl.hpp"

#endif
