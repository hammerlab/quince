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

#include <cctype>
#include <cmath>
#include <cstdlib>
#include <sstream>

#include "broad.h"

template <typename T>
StringVal ToStringVal(FunctionContext* context, const T& val) {
  std::stringstream ss;
  ss << val;
  std::string str = ss.str();
  StringVal string_val(context, str.size());
  memcpy(string_val.ptr, str.c_str(), str.size());
  return string_val;
}

StringVal GenerateId(FunctionContext* context, const StringVal& chr, const IntVal& pos, const StringVal& ref, const StringVal& alt) {
    if (chr.is_null || pos.is_null || ref.is_null || alt.is_null) return StringVal::null();
    StringVal pos_string = ToStringVal(context, pos.val);
    int total_len = chr.len + pos_string.len + ref.len + alt.len + 3; // 3 is for the separators
    StringVal id_string(context, total_len);
    int offset = 0;
    memcpy(id_string.ptr + offset, chr.ptr, chr.len); offset += chr.len;
    id_string.ptr[offset] = '_'; offset += 1;
    memcpy(id_string.ptr + offset, pos_string.ptr, pos_string.len); offset += pos_string.len;
    id_string.ptr[offset] = '_'; offset += 1;
    memcpy(id_string.ptr + offset, ref.ptr, ref.len); offset += ref.len;
    id_string.ptr[offset] = '/'; offset += 1;
    memcpy(id_string.ptr + offset, alt.ptr, alt.len);
    return id_string;
}

IntVal GenotypeAsInt(FunctionContext* context, const StringVal& gt) {
    if (gt.is_null) return IntVal::null();
    if (gt.len != 3) return IntVal::null();
    if (gt.ptr[0] == '0' && gt.ptr[2] == '0') return IntVal(0);
    if (gt.ptr[0] == '0' && gt.ptr[2] == '1') return IntVal(1);
    if (gt.ptr[0] == '1' && gt.ptr[2] == '0') return IntVal(1);
    if (gt.ptr[0] == '1' && gt.ptr[2] == '1') return IntVal(2);
    return IntVal::null();
}

DoubleVal LogLikelihoodRef(FunctionContext* context, const StringVal& likelihoods) {
    if (likelihoods.is_null) return DoubleVal::null();
    int start = 0;
    int end = 0;
    while (likelihoods.ptr[end] != ',' && end < likelihoods.len) {
        end++;
    }
    if (end == likelihoods.len) return DoubleVal::null();
    char lh[end - start + 1];
    memcpy(lh, likelihoods.ptr + start, end - start);
    lh[end - start] = '\0';
    return DoubleVal(atof(lh));
}

DoubleVal LogLikelihoodHet(FunctionContext* context, const StringVal& likelihoods) {
    if (likelihoods.is_null) return DoubleVal::null();
    int start = 0;
    while (likelihoods.ptr[start] != ',' && start < likelihoods.len) {
        start++;
    }
    if (start == likelihoods.len) return DoubleVal::null();
    start++;
    int end = start;
    while (likelihoods.ptr[end] != ',' && end < likelihoods.len) {
        end++;
    }
    if (end == likelihoods.len) return DoubleVal::null();
    char lh[end - start + 1];
    memcpy(lh, likelihoods.ptr + start, end - start);
    lh[end - start] = '\0';
    return DoubleVal(atof(lh));
}

DoubleVal LogLikelihoodAlt(FunctionContext* context, const StringVal& likelihoods) {
    if (likelihoods.is_null) return DoubleVal::null();
    int start = 0;
    while (likelihoods.ptr[start] != ',' && start < likelihoods.len) {
        start++;
    }
    if (start == likelihoods.len) return DoubleVal::null();
    start++;
    while (likelihoods.ptr[start] != ',' && start < likelihoods.len) {
        start++;
    }
    if (start == likelihoods.len) return DoubleVal::null();
    start++;
    int end = likelihoods.len;
    char lh[end - start + 1];
    memcpy(lh, likelihoods.ptr + start, end - start);
    lh[end - start] = '\0';
    return DoubleVal(atof(lh));
}

BooleanVal IsTransition(FunctionContext* context, const StringVal& reference, const StringVal& alternate) {
    if (reference.is_null || alternate.is_null) return BooleanVal::null();
    // ref and alt alleles should be SNPs
    if (reference.len != 1 || alternate.len != 1) return BooleanVal::null();
    char ref = toupper(*reference.ptr);
    char alt = toupper(*alternate.ptr);
    // make sure ref and alt are valid bases
    if (ref != 'A' && ref != 'C' && ref != 'G' && ref != 'T') return BooleanVal::null();
    if (alt != 'A' && alt != 'C' && alt != 'G' && alt != 'T') return BooleanVal::null();
    // check for transition
    if (ref == 'A' && alt == 'G') {
        return BooleanVal(true);
    } else if (ref == 'G' && alt == 'A') {
        return BooleanVal(true);
    } else if (ref == 'C' && alt == 'T') {
        return BooleanVal(true);
    } else if (ref == 'T' && alt == 'C') {
        return BooleanVal(true);
    } else {
        return BooleanVal(false);
    }
}

BooleanVal IsInsertion(FunctionContext* context, const StringVal& type, const StringVal& ref, const StringVal& alt) {
    if (type.is_null || ref.is_null || alt.is_null) return BooleanVal::null();
    // INDEL has 5 characters
    if (type.len != 5) return BooleanVal(false);
    // just check to make sure it really is INDEL
    const char *indel = "INDEL";
    for (int i = 0; i < 5; i++) {
        if (indel[i] != toupper(type.ptr[i])) {
            return BooleanVal(false);
        }
    }
    if (ref.len < alt.len) {
        return BooleanVal(true);
    } else {
        return BooleanVal(false);
    }
}

BooleanVal NoCall(FunctionContext* context, const StringVal& genotype) {
    if (genotype.is_null) return BooleanVal::null();
    // genotype must be a string like 0/1 or ./.
    if (genotype.len != 3) return BooleanVal::null();
    if (genotype.ptr[0] == '.' or genotype.ptr[2] == '.') {
        return BooleanVal(true);
    } else {
        return BooleanVal(false);
    }
}