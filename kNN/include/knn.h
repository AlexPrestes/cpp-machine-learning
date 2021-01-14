#ifndef __KNN_H
#define __KNN_H

#include <vector>
#include "data.h"

class knn {
  int k;
  std::shared_ptr< std::vector< std::shared_ptr<data> > > neighbors;
  std::shared_ptr< std::vector< std::shared_ptr<data> > > training_data;
  std::shared_ptr< std::vector< std::shared_ptr<data> > > test_data;
  std::shared_ptr< std::vector< std::shared_ptr<data> > > validation_data;

  public:
  knn(int);
  knn();
  ~knn();

  void find_knearest(std::shared_ptr<data> query_point);
  void set_training_data(std::shared_ptr< std::vector< std::shared_ptr<data> > > vect);
  void set_test_data(std::shared_ptr< std::vector< std::shared_ptr<data> > > vect);
  void set_validation_data(std::shared_ptr< std::vector< std::shared_ptr<data> > > vect);
  void set_k(int val);

  int predict();
  double calculate_distance(std::shared_ptr<data> query_point, std::shared_ptr<data> input);
  double validate_performance();
  double test_performance();
};

#endif
