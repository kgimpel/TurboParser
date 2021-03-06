// Copyright (c) 2012 Andre Martins
// All Rights Reserved.
//
// This file is part of TurboParser 2.0.
//
// TurboParser 2.0 is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// TurboParser 2.0 is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with TurboParser 2.0.  If not, see <http://www.gnu.org/licenses/>.

#ifndef OPTIONS_H_
#define OPTIONS_H_

#include <fstream>
#include <vector>
#include <gflags/gflags.h>

using namespace std;

DECLARE_bool(train);
DECLARE_bool(test);
DECLARE_bool(evaluate);

DECLARE_string(train_algorithm);
DECLARE_bool(only_supported_features);
DECLARE_bool(use_averaging);
DECLARE_int32(train_epochs);
DECLARE_double(train_regularization_constant);
DECLARE_double(train_initial_learning_rate);
DECLARE_string(train_learning_rate_schedule);

// General training/test options.
class Options {
 public:
  Options() {};
  virtual ~Options() {};

  // Serialization functions.
  // Load current option flags to the model file.
  // Note: this will override the user-specified flags.
  virtual void Save(FILE* fs) {};
  // Save current option flags to the model file.
  virtual void Load(FILE* fs) {};

  // Initialization: set options based on the flags.
  virtual void Initialize();

  // Get option values.
  const string &GetTrainingFilePath() { return file_train_; };
  const string &GetTestFilePath() { return file_test_; };
  const string &GetModelFilePath() { return file_model_; };
  const string &GetOutputFilePath() { return file_prediction_; };
  int GetNumEpochs() { return train_epochs_; };
  double GetRegularizationConstant() { return train_regularization_constant_; }
  const string &GetTrainingAlgorithm() { return train_algorithm_; }
  double GetInitialLearningRate() { return train_initial_learning_rate_; }
  const string &GetLearningRateSchedule() {
    return train_learning_rate_schedule_;
  }
  bool use_averaging() { return use_averaging_; }
  bool only_supported_features() { return only_supported_features_; }
  bool train() { return train_; }
  bool test() { return test_; }
  bool evaluate() { return evaluate_; }

 protected:
  string file_train_;
  string file_test_;
  string file_model_;
  string file_prediction_;
  bool train_;
  bool test_;
  bool evaluate_;
  int train_epochs_;

  // The regularization constant (C). The training optimization problem is:
  // min 1/(2C)*||w||^2 + sum_t(loss(w; x_t,y_t)).
  double train_regularization_constant_;

  // The algorithm used to train the model. Alternatives are:
  // -- perceptron
  // -- mira
  // -- svm_mira
  // -- crf_mira
  // -- svm_sgd
  // -- crf_sgd
  string train_algorithm_;

  // Learning rate and its decay schedule (for SGD only).
  double train_initial_learning_rate_;
  string train_learning_rate_schedule_;

  bool only_supported_features_; // Use only supported features.
  bool use_averaging_; // Include a final averaging step during training.
};

#endif /*OPTIONS_H_*/
