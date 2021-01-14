#include "knn.h"
#include <cmath>
#include <limits>
#include <map>
#include "stdint.h"
#include "data_handler.h"

knn::knn(int val){
  k = val;
}
knn::knn(){
  // NOTHING TO DO
}
knn::~knn(){
  // NOTHING TO DO
}

void knn::find_knearest(std::shared_ptr<data> query_point){
  neighbors = std::unique_ptr<std::vector<std::shared_ptr<data> > >(new std::vector<std::shared_ptr<data>>);
  double min = std::numeric_limits<double>::max();
  double previous_min = min;
  int index = 0;
  for(int i = 0; i < k; i++){
    if(i == 0){
      for(unsigned int j = 0; j < training_data->size(); j++){
        double distance = calculate_distance(query_point, training_data->at(j));
        training_data->at(j)->set_distance(distance);
        if(distance < min){
          min = distance;
          index = j;
        }
      }
      neighbors->push_back(training_data->at(index));
      previous_min = min;
      min = std::numeric_limits<double>::max();
    } else {
      for(unsigned int j = 0; j < training_data->size(); j++){
        double distance = calculate_distance(query_point, training_data->at(j));
        if(distance < previous_min && distance < min){
          min = distance;
          index = j;
        }
      }
      neighbors->push_back(training_data->at(index));
      previous_min = min;
      min = std::numeric_limits<double>::max();
    }
  }
}
void knn::set_training_data(std::shared_ptr< std::vector< std::shared_ptr<data> > > vect){
  training_data = vect;
}
void knn::set_test_data(std::shared_ptr< std::vector< std::shared_ptr<data> > > vect){
  test_data = vect;
}
void knn::set_validation_data(std::shared_ptr< std::vector< std::shared_ptr<data> > > vect){
  validation_data = vect;
}
void knn::set_k(int val){
  k = val;
}

int knn::predict(){
  std::map<uint8_t, int> class_freq;
  for(unsigned int i = 0; i < neighbors->size(); i++){
    if(class_freq.find(neighbors->at(i)->get_label()) == class_freq.end()){
      class_freq[neighbors->at(i)->get_label()] = 1;
    } else {
      class_freq[neighbors->at(i)->get_label()]++;
    }
  }
  int best = 0;
  int max = 0;
  for(auto kv : class_freq){
    if(kv.second > max){
      max = kv.second;
      best = kv.first;
    }
  }
  return best;
}
double knn::calculate_distance(std::shared_ptr<data> query_point, std::shared_ptr<data> input){
  double distance = 0.0;
  if(query_point->get_feature_vector_size() != input->get_feature_vector_size()){
    printf("Error Vector Size Mismatch.\n");
    exit(1);
  }
#ifdef EUCLID
  for(int i = 0; i < query_point->get_feature_vector_size(); i++){
    distance = pow(query_point->get_feature_vector()->at(i) - input->get_feature_vector()->at(i), 2);
  }
  distance = sqrt(distance);
#elif defined MANHATTAN
  // PUT 
#endif
  return distance;
}
double knn::validate_performance(){
  double current_performance = 0.0;
  int count = 0;
  int data_index = 0;
  for(std::shared_ptr<data> query_point : *validation_data){
    find_knearest(query_point);
    int prediction = predict();
    if(prediction == query_point->get_label()){
      count++;
    }
    data_index++;
    printf("Current Performance = %.3f %%\n", ((double)count*100.0)/((double)data_index));
  }
  current_performance = ((double)count*100.0)/((double)validation_data->size());
  printf("Validation Performance for k = %d: %.3f %%\n", k, current_performance);
  return current_performance;
}
double knn::test_performance(){
  double current_performance = 0.0;
  int count = 0;
  for(std::shared_ptr<data> query_point : *test_data){
    find_knearest(query_point);
    int prediction = predict();
    if(prediction == query_point->get_label()){
      count++;
    }
  }
  current_performance = ((double)count*100.0)/((double)validation_data->size());
  printf("Tested Performance = %.3f %%\n", current_performance);
  return current_performance;
}

int main() {

  std::shared_ptr<data_handler> dh =std::shared_ptr<data_handler>(new data_handler());
  dh->read_feature_vector("../mnist/train-images.idx3-ubyte");
  dh->read_feature_labels("../mnist/train-labels.idx1-ubyte");
  dh->split_data();
  dh->count_classes();

  std::shared_ptr<knn> knearest = std::shared_ptr<knn>(new knn());
  knearest->set_training_data(dh->get_training_data());
  knearest->set_test_data(dh->get_test_data());
  knearest->set_validation_data(dh->get_validation_data());
  double performance = 0.0;
  double best_performance = 0.0;
  int best_k = 1;
  for(int k = 1; k <= 5; k++){
    if(k == 1){
      knearest->set_k(k);
      performance = knearest->validate_performance();
      best_performance = performance;
    } else {
      knearest->set_k(k);
      performance = knearest->validate_performance();
      if(performance > best_performance){
        best_performance = performance;
        best_k = k;
      }
    }
  }
  knearest->set_k(best_k);
  knearest->test_performance();
}