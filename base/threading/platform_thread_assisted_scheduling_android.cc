// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
// Licensed under MIT ($LICENSE_URL)

#include "base/logging.h"
#include "base/threading/platform_thread.h"

#if !defined(_GNU_SOURCE)
#define _GNU_SOURCE
#endif

#include <asm/unistd.h>
#include <sched.h>
#include <set>
#include <string>
#include <unistd.h>
#include <sys/syscall.h>

// Before android-21, ndk not have sched_setaffinity, CPU_ZERO and CPU_SET
#if !defined(CPU_ZERO) 
// The following macros are copied from android-21 sched.h
#ifdef __LP64__
#define CPU_SETSIZE 1024
#else
#define CPU_SETSIZE 32
#endif

#define __CPU_BITTYPE  unsigned long int  /* mandated by the kernel  */
#define __CPU_BITS     (8 * sizeof(__CPU_BITTYPE))
#define __CPU_ELT(x)   ((x) / __CPU_BITS)
#define __CPU_MASK(x)  ((__CPU_BITTYPE)1 << ((x) & (__CPU_BITS - 1)))

typedef struct {
  __CPU_BITTYPE  __bits[ CPU_SETSIZE / __CPU_BITS ];
} cpu_set_t;

#define CPU_ZERO(set)          CPU_ZERO_S(sizeof(cpu_set_t), set)
#define CPU_SET(cpu, set)      CPU_SET_S(cpu, sizeof(cpu_set_t), set)

#define CPU_ZERO_S(setsize, set)  __builtin_memset(set, 0, setsize)

#define CPU_SET_S(cpu, setsize, set) \
  do { \
    size_t __cpu = (cpu); \
    if (__cpu < 8 * (setsize)) \
      (set)->__bits[__CPU_ELT(__cpu)] |= __CPU_MASK(__cpu); \
  } while (0)


namespace {

int sched_setaffinity(pid_t pid, size_t cpusetsize, const cpu_set_t *mask) {
  // bionic actually uses Assembly code for this
  return syscall(__NR_sched_setaffinity, pid, cpusetsize, mask);
}

}  // namespace

#endif // !defined(CPU_ZERO)

namespace base {

void PlatformThread::SetCurrentThreadAffinity(const std::vector<size_t>& eligible_core_ids) {
  if (!SetThreadAffinity(0, eligible_core_ids)) {
    LOG(ERROR) << "Set current thread affinity failed";
  }
}

bool PlatformThread::SetThreadAffinity(PlatformThreadId tid,
                                       const std::vector<size_t>& eligible_core_ids) {
  cpu_set_t mask;
  CPU_ZERO(&mask);

  for (size_t i = 0; i < eligible_core_ids.size(); ++i) {
    CPU_SET(eligible_core_ids[i], &mask);
  }
  
  // There is no pthread_setaffinity_np in ndk yet
  if (sched_setaffinity(tid, sizeof(mask), &mask) < 0) {
      PLOG(ERROR) << "sched_setaffinity failed";
      return false;
  }
  return true;
}

}  // namespace base
