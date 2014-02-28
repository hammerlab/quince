// Copyright 2014 Cloudera Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef CLOUDERA_BROAD_H
#define CLOUDERA_BROAD_H

#include <impala_udf/udf.h>

using namespace impala_udf;

template <typename T>
StringVal ToStringVal(FunctionContext* context, const T& val);

StringVal GenerateId(FunctionContext* context, const StringVal& chr, const IntVal& pos, const StringVal& ref, const StringVal& alt);
IntVal GenotypeAsInt(FunctionContext* context, const StringVal& gt);
DoubleVal LogLikelihoodRef(FunctionContext* context, const StringVal& likelihoods);
DoubleVal LogLikelihoodHet(FunctionContext* context, const StringVal& likelihoods);
DoubleVal LogLikelihoodAlt(FunctionContext* context, const StringVal& likelihoods);
BooleanVal IsTransition(FunctionContext* context, const StringVal& reference, const StringVal& alternate);
BooleanVal IsInsertion(FunctionContext* context, const StringVal& type, const StringVal& ref, const StringVal& alt);
BooleanVal NoCall(FunctionContext* context, const StringVal& genotype);

#endif