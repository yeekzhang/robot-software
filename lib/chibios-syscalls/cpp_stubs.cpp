#include <ch.h>
#include <hal.h>

#include <stdio.h>
#include <errno.h>

typedef int __guard;

extern "C" {
int __cxa_guard_acquire(__guard*);
void __cxa_guard_release(__guard*);
void __cxa_guard_abort(__guard*);
void __cxa_pure_virtual();
void* __attribute__((weak)) __dso_handle = NULL;
void _exit(int status);
pid_t _getpid(void);
int _kill(int pid, int sig);
}

void __attribute__((weak)) __cxa_pure_virtual()
{
    osalSysHalt("Pure virtual function call.");
}

#ifndef CVRA_NO_DYNAMIC_ALLOCATION
# define CVRA_NO_DYNAMIC_ALLOCATION 0
#endif

#if CVRA_NO_DYNAMIC_ALLOCATION
void* operator new(size_t)
{
    osalSysHalt("operator new");
    return reinterpret_cast<void*>(0xFFFFFFFF);
}

void* operator new[](size_t)
{
    osalSysHalt("operator new[]");
    return reinterpret_cast<void*>(0xFFFFFFFF);
}

void operator delete(void*)
{
    osalSysHalt("operator delete");
}

void operator delete[](void*)
{
    osalSysHalt("operator delete[]");
}
#endif /* CVRA_NO_DYNAMIC_ALLOCATION */

void __attribute__((weak)) _exit(int status)
{
    (void)status;
    osalSysHalt("Unrealized");
    while (TRUE) {
    }
}

pid_t __attribute__((weak)) _getpid(void)
{
    return 1;
}

#undef errno
extern int errno;
int __attribute__((weak)) _kill(int pid, int sig)
{
    (void)pid;
    (void)sig;
    errno = EINVAL;
    return -1;
}

void _open_r(void)
{
    return;
}

namespace std {
void __throw_bad_function_call(void)
{
    osalSysHalt("Bad function call");
}
} // namespace std
