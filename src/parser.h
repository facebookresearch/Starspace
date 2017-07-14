/**
 * Copyright (c) 2016-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */


/**
 * This is the basic class of data parsing.
 * It provides essential functions as follows:
 * - parse(input, output):
 *   takes input as a line of string (or a vector of string tokens)
 *   and return output result which is one or multiple examples contains l.h.s. features
 *   and r.h.s. features.
 *   For most cases, one line of input produces one example;
 *   For the case of freebase, one line of input produces two examples.
 *
 * - parseForDict(input, tokens):
 *   takes input as a line of string, output tokens to be added for building
 *   the dictionary.
 *
 * - check(example):
 *   checks whether the example is a valid example.
 *
 * - addNgrams(input, output):
 *   add ngrams from input as output.
 *
 * One can write different parsers for data with different format.
 */

#pragma once

#include "dict.h"
#include <string>
#include <vector>

namespace starspace {

struct ParseResults {
  std::vector<int32_t> LHSTokens;
  std::vector<int32_t> RHSTokens;
  std::vector<std::vector<int32_t>> RHSFeatures;
};

typedef std::vector<ParseResults> Corpus;

class DataParser {
public:
  explicit DataParser(
    std::shared_ptr<Dictionary> dict,
    std::shared_ptr<Args> args);

  virtual void parse(
      std::string& s,
      std::vector<ParseResults>& rslt,
      const std::string& sep="\t ");

  virtual void parseForDict(
      std::string& s,
      std::vector<std::string>& tokens,
      const std::string& sep="\t ");

  bool parse(
      const std::vector<std::string>& tokens,
      ParseResults& rslt);

  bool parse(
      const std::vector<std::string>& tokens,
      std::vector<int32_t>& rslt);

  bool check(const ParseResults& example);

  void addNgrams(
      const std::vector<std::string>& tokens,
      std::vector<int32_t>& line,
      int32_t n);

  std::shared_ptr<Dictionary> getDict() { return dict_; };

  void resetDict(std::shared_ptr<Dictionary> dict) { dict_ = dict; };

protected:
  std::shared_ptr<Dictionary> dict_;
  std::shared_ptr<Args> args_;
};

}
