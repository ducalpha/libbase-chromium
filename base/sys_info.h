// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_SYS_INFO_H_
#define BASE_SYS_INFO_H_

#include "base/base_export.h"
#include "base/threading/thread_restrictions.h"

#include <unistd.h>

namespace base {

class BASE_EXPORT SysInfo {
 public:
  // Return the smallest amount of memory (in bytes) which the VM system will
  // allocate.
  static size_t VMAllocationGranularity();
};

}  // namespace base

#endif  // BASE_SYS_INFO_H_
