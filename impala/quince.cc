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

#include "quince.h"

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

IntVal ChrSegment(FunctionContext* context, const IntVal& pos) {
    return ChrSegment(context, pos, IntVal(1000));
}

IntVal ChrSegment(FunctionContext* context, const IntVal& pos, const Intval& size_kb) {
    if (pos.is_null || size_kb.is_null) return IntVal::null();
    return IntVal(static_cast<int>(floor(pos.val / (size_kb * 1000.))))
}