/*****************************************************************************
 * thread.c : pthread back-end for LibVLC
 *****************************************************************************
 * Copyright (C) 1999-2009 VLC authors and VideoLAN
 *
 * Authors: Jean-Marc Dressler <polux@via.ecp.fr>
 *          Samuel Hocevar <sam@zoy.org>
 *          Gildas Bazin <gbazin@netcourrier.com>
 *          Clément Sténac
 *          Rémi Denis-Courmont
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <vlc_common.h>

#include "libvlc.h"
#include <stdarg.h>
#include <stdatomic.h>
#include <stdnoreturn.h>
#include <signal.h>
#include <errno.h>
#include <limits.h>
#include <time.h>
#include <assert.h>

#include <sys/types.h>
#include <unistd.h> /* fsync() */
#include <pthread.h>
#include <sched.h>

#ifdef HAVE_EXECINFO_H
# include <execinfo.h>
#endif
#if defined(__SunOS)
# include <sys/processor.h>
# include <sys/pset.h>
#endif

static unsigned vlc_clock_prec;

static void vlc_clock_setup_once (void)
{
    struct timespec res;
    if (unlikely(clock_getres(CLOCK_MONOTONIC, &res) != 0 || res.tv_sec != 0))
        abort ();
    vlc_clock_prec = (res.tv_nsec + 500) / 1000;
}

<<<<<<< HEAD
=======
static pthread_once_t vlc_clock_once = PTHREAD_ONCE_INIT;

# define vlc_clock_setup() \
    pthread_once(&vlc_clock_once, vlc_clock_setup_once)

#else /* _POSIX_TIMERS */

# include <sys/time.h> /* gettimeofday() */

# define vlc_clock_setup() (void)0
# warning Monotonic clock not available. Expect timing issues.
#endif /* _POSIX_TIMERS */

static struct timespec mtime_to_ts (vlc_tick_t date)
{
    lldiv_t d = lldiv (date, CLOCK_FREQ);
    struct timespec ts = { d.quot, d.rem * (1000000000 / CLOCK_FREQ) };

    return ts;
}

>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4
/**
 * Print a backtrace to the standard error for debugging purpose.
 */
void vlc_trace (const char *fn, const char *file, unsigned line)
{
     fprintf (stderr, "at %s:%u in %s\n", file, line, fn);
     fflush (stderr); /* needed before switch to low-level I/O */
#ifdef HAVE_BACKTRACE
     void *stack[20];
     int len = backtrace (stack, ARRAY_SIZE (stack) );
     backtrace_symbols_fd (stack, len, 2);
#endif
     fsync (2);
}

#ifndef NDEBUG
/**
 * Reports a fatal error from the threading layer, for debugging purposes.
 */
static void
vlc_thread_fatal (const char *action, int error,
                  const char *function, const char *file, unsigned line)
{
    int canc = vlc_savecancel ();
    fprintf (stderr, "LibVLC fatal error %s (%d) in thread %lu ",
             action, error, vlc_thread_id ());
    vlc_trace (function, file, line);
    perror ("Thread error");
    fflush (stderr);

    vlc_restorecancel (canc);
    abort ();
}

# define VLC_THREAD_ASSERT( action ) \
    if (unlikely(val)) \
        vlc_thread_fatal (action, val, __func__, __FILE__, __LINE__)
#else
# define VLC_THREAD_ASSERT( action ) ((void)val)
#endif

<<<<<<< HEAD
=======
void vlc_mutex_init( vlc_mutex_t *p_mutex )
{
    pthread_mutexattr_t attr;

    if (unlikely(pthread_mutexattr_init (&attr)))
        abort();
#ifdef NDEBUG
    pthread_mutexattr_settype (&attr, PTHREAD_MUTEX_DEFAULT);
#else
    pthread_mutexattr_settype (&attr, PTHREAD_MUTEX_ERRORCHECK);
#endif
    if (unlikely(pthread_mutex_init (p_mutex, &attr)))
        abort();
    pthread_mutexattr_destroy( &attr );
}

void vlc_mutex_init_recursive( vlc_mutex_t *p_mutex )
{
    pthread_mutexattr_t attr;

    if (unlikely(pthread_mutexattr_init (&attr)))
        abort();
    pthread_mutexattr_settype (&attr, PTHREAD_MUTEX_RECURSIVE);
    if (unlikely(pthread_mutex_init (p_mutex, &attr)))
        abort();
    pthread_mutexattr_destroy( &attr );
}

void vlc_mutex_destroy (vlc_mutex_t *p_mutex)
{
    int val = pthread_mutex_destroy( p_mutex );
    VLC_THREAD_ASSERT ("destroying mutex");
}

#ifndef NDEBUG
# ifdef HAVE_VALGRIND_VALGRIND_H
#  include <valgrind/valgrind.h>
# else
#  define RUNNING_ON_VALGRIND (0)
# endif

/**
 * Asserts that a mutex is locked by the calling thread.
 */
void vlc_assert_locked (vlc_mutex_t *p_mutex)
{
    if (RUNNING_ON_VALGRIND > 0)
        return;
    assert (pthread_mutex_lock (p_mutex) == EDEADLK);
}
#endif

void vlc_mutex_lock (vlc_mutex_t *p_mutex)
{
    int val = pthread_mutex_lock( p_mutex );
    VLC_THREAD_ASSERT ("locking mutex");
}

int vlc_mutex_trylock (vlc_mutex_t *p_mutex)
{
    int val = pthread_mutex_trylock( p_mutex );

    if (val != EBUSY)
        VLC_THREAD_ASSERT ("locking mutex");
    return val;
}

void vlc_mutex_unlock (vlc_mutex_t *p_mutex)
{
    int val = pthread_mutex_unlock( p_mutex );
    VLC_THREAD_ASSERT ("unlocking mutex");
}

void vlc_cond_init (vlc_cond_t *p_condvar)
{
    pthread_condattr_t attr;

    if (unlikely(pthread_condattr_init (&attr)))
        abort ();
#if (_POSIX_CLOCK_SELECTION > 0)
    vlc_clock_setup ();
    pthread_condattr_setclock (&attr, vlc_clock_id);
#endif
    if (unlikely(pthread_cond_init (p_condvar, &attr)))
        abort ();
    pthread_condattr_destroy (&attr);
}

void vlc_cond_init_daytime (vlc_cond_t *p_condvar)
{
    if (unlikely(pthread_cond_init (p_condvar, NULL)))
        abort ();
}

void vlc_cond_destroy (vlc_cond_t *p_condvar)
{
    int val = pthread_cond_destroy( p_condvar );
    VLC_THREAD_ASSERT ("destroying condition");
}

void vlc_cond_signal (vlc_cond_t *p_condvar)
{
    int val = pthread_cond_signal( p_condvar );
    VLC_THREAD_ASSERT ("signaling condition variable");
}

void vlc_cond_broadcast (vlc_cond_t *p_condvar)
{
    pthread_cond_broadcast (p_condvar);
}

void vlc_cond_wait (vlc_cond_t *p_condvar, vlc_mutex_t *p_mutex)
{
    int val = pthread_cond_wait( p_condvar, p_mutex );
    VLC_THREAD_ASSERT ("waiting on condition");
}

int vlc_cond_timedwait (vlc_cond_t *p_condvar, vlc_mutex_t *p_mutex,
                        vlc_tick_t deadline)
{
    struct timespec ts = mtime_to_ts (deadline);
    int val = pthread_cond_timedwait (p_condvar, p_mutex, &ts);
    if (val != ETIMEDOUT)
        VLC_THREAD_ASSERT ("timed-waiting on condition");
    return val;
}

int vlc_cond_timedwait_daytime (vlc_cond_t *p_condvar, vlc_mutex_t *p_mutex,
                                time_t deadline)
{
    struct timespec ts = { deadline, 0 };
    int val = pthread_cond_timedwait (p_condvar, p_mutex, &ts);
    if (val != ETIMEDOUT)
        VLC_THREAD_ASSERT ("timed-waiting on condition");
    return val;
}

void vlc_sem_init (vlc_sem_t *sem, unsigned value)
{
    if (unlikely(sem_init (sem, 0, value)))
        abort ();
}

void vlc_sem_destroy (vlc_sem_t *sem)
{
    int val;

    if (likely(sem_destroy (sem) == 0))
        return;

    val = errno;

    VLC_THREAD_ASSERT ("destroying semaphore");
}

int vlc_sem_post (vlc_sem_t *sem)
{
    int val;

    if (likely(sem_post (sem) == 0))
        return 0;

    val = errno;

    if (unlikely(val != EOVERFLOW))
        VLC_THREAD_ASSERT ("unlocking semaphore");
    return val;
}

void vlc_sem_wait (vlc_sem_t *sem)
{
    int val;

    do
        if (likely(sem_wait (sem) == 0))
            return;
    while ((val = errno) == EINTR);

    VLC_THREAD_ASSERT ("locking semaphore");
}

void vlc_rwlock_init (vlc_rwlock_t *lock)
{
    if (unlikely(pthread_rwlock_init (lock, NULL)))
        abort ();
}

void vlc_rwlock_destroy (vlc_rwlock_t *lock)
{
    int val = pthread_rwlock_destroy (lock);
    VLC_THREAD_ASSERT ("destroying R/W lock");
}

void vlc_rwlock_rdlock (vlc_rwlock_t *lock)
{
    int val = pthread_rwlock_rdlock (lock);
    VLC_THREAD_ASSERT ("acquiring R/W lock for reading");
}

void vlc_rwlock_wrlock (vlc_rwlock_t *lock)
{
    int val = pthread_rwlock_wrlock (lock);
    VLC_THREAD_ASSERT ("acquiring R/W lock for writing");
}

void vlc_rwlock_unlock (vlc_rwlock_t *lock)
{
    int val = pthread_rwlock_unlock (lock);
    VLC_THREAD_ASSERT ("releasing R/W lock");
}

>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4
int vlc_threadvar_create (vlc_threadvar_t *key, void (*destr) (void *))
{
    return pthread_key_create (key, destr);
}

void vlc_threadvar_delete (vlc_threadvar_t *p_tls)
{
    pthread_key_delete (*p_tls);
}

int vlc_threadvar_set (vlc_threadvar_t key, void *value)
{
    return pthread_setspecific (key, value);
}

void *vlc_threadvar_get (vlc_threadvar_t key)
{
    return pthread_getspecific (key);
}

void vlc_threads_setup (libvlc_int_t *p_libvlc)
{
    (void) p_libvlc;
}

static int vlc_clone_attr (vlc_thread_t *th, pthread_attr_t *attr,
                           void *(*entry) (void *), void *data)
{
    int ret;

    /* Block the signals that signals interface plugin handles.
     * If the LibVLC caller wants to handle some signals by itself, it should
     * block these before whenever invoking LibVLC. And it must obviously not
     * start the VLC signals interface plugin.
     *
     * LibVLC will normally ignore any interruption caused by an asynchronous
     * signal during a system call. But there may well be some buggy cases
     * where it fails to handle EINTR (bug reports welcome). Some underlying
     * libraries might also not handle EINTR properly.
     */
    sigset_t oldset;
    {
        sigset_t set;
        sigemptyset (&set);
        sigdelset (&set, SIGHUP);
        sigaddset (&set, SIGINT);
        sigaddset (&set, SIGQUIT);
        sigaddset (&set, SIGTERM);

        sigaddset (&set, SIGPIPE); /* We don't want this one, really! */
        pthread_sigmask (SIG_BLOCK, &set, &oldset);
    }

    /* The thread stack size.
     * The lower the value, the less address space per thread, the highest
     * maximum simultaneous threads per process. Too low values will cause
     * stack overflows and weird crashes. Set with caution. Also keep in mind
     * that 64-bits platforms consume more stack than 32-bits one.
     *
     * Thanks to on-demand paging, thread stack size only affects address space
     * consumption. In terms of memory, threads only use what they need
     * (rounded up to the page boundary).
     *
     * For example, on Linux i386, the default is 2 mega-bytes, which supports
     * about 320 threads per processes. */
#define VLC_STACKSIZE (128 * sizeof (void *) * 1024)

#ifdef VLC_STACKSIZE
    ret = pthread_attr_setstacksize (attr, VLC_STACKSIZE);
    assert (ret == 0); /* fails iff VLC_STACKSIZE is invalid */
#endif

    ret = pthread_create(&th->handle, attr, entry, data);
    pthread_sigmask (SIG_SETMASK, &oldset, NULL);
    pthread_attr_destroy (attr);
    return ret;
}

int vlc_clone (vlc_thread_t *th, void *(*entry) (void *), void *data)
{
    pthread_attr_t attr;

    pthread_attr_init (&attr);
    return vlc_clone_attr (th, &attr, entry, data);
}

void vlc_join(vlc_thread_t th, void **result)
{
    int val = pthread_join(th.handle, result);
    VLC_THREAD_ASSERT ("joining thread");
}

VLC_WEAK unsigned long vlc_thread_id(void)
{
     static thread_local unsigned char dummy;

     static_assert (UINTPTR_MAX <= ULONG_MAX, "Type size mismatch");
     return (uintptr_t)(void *)&dummy;
}

VLC_WEAK void (vlc_thread_set_name)(const char *name)
{
    VLC_UNUSED(name);
}

void vlc_cancel(vlc_thread_t th)
{
    pthread_cancel(th.handle);
}

int vlc_savecancel (void)
{
    int state;
    int val = pthread_setcancelstate (PTHREAD_CANCEL_DISABLE, &state);

    VLC_THREAD_ASSERT ("saving cancellation");
    return state;
}

void vlc_restorecancel (int state)
{
#ifndef NDEBUG
    int oldstate, val;

    val = pthread_setcancelstate (state, &oldstate);
    /* This should fail if an invalid value for given for state */
    VLC_THREAD_ASSERT ("restoring cancellation");

    if (unlikely(oldstate != PTHREAD_CANCEL_DISABLE))
         vlc_thread_fatal ("restoring cancellation while not disabled", EINVAL,
                           __func__, __FILE__, __LINE__);
#else
    pthread_setcancelstate (state, NULL);
#endif
}

void vlc_testcancel (void)
{
    pthread_testcancel ();
}

<<<<<<< HEAD
vlc_tick_t vlc_tick_now (void)
=======
void vlc_control_cancel (int cmd, ...)
{
    (void) cmd;
    vlc_assert_unreachable ();
}

vlc_tick_t mdate (void)
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4
{
    struct timespec ts;

    if (unlikely(clock_gettime(CLOCK_MONOTONIC, &ts) != 0))
        abort ();

    return vlc_tick_from_timespec( &ts );
}

<<<<<<< HEAD
#undef vlc_tick_wait
void vlc_tick_wait (vlc_tick_t deadline)
=======
#undef mwait
void mwait (vlc_tick_t deadline)
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4
{
    static pthread_once_t vlc_clock_once = PTHREAD_ONCE_INIT;

    /* If the deadline is already elapsed, or within the clock precision,
     * do not even bother the system timer. */
    pthread_once(&vlc_clock_once, vlc_clock_setup_once);
    deadline -= vlc_clock_prec;

    struct timespec ts;

    vlc_tick_to_timespec(&ts, deadline);
    while (clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &ts, NULL) == EINTR);
}

<<<<<<< HEAD
#undef vlc_tick_sleep
void vlc_tick_sleep (vlc_tick_t delay)
=======
#undef msleep
void msleep (vlc_tick_t delay)
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4
{
    struct timespec ts;

    vlc_tick_to_timespec(&ts, delay);
    while (clock_nanosleep(CLOCK_MONOTONIC, 0, &ts, &ts) == EINTR);
}

unsigned vlc_GetCPUCount(void)
{
#if defined(HAVE_SCHED_GETAFFINITY)
    cpu_set_t cpu;

    CPU_ZERO(&cpu);
    if (sched_getaffinity (0, sizeof (cpu), &cpu) < 0)
        return 1;

    return CPU_COUNT (&cpu);

#elif defined(__SunOS)
    unsigned count = 0;
    int type;
    u_int numcpus;
    processor_info_t cpuinfo;

    processorid_t *cpulist = vlc_alloc (sysconf(_SC_NPROCESSORS_MAX), sizeof (*cpulist));
    if (unlikely(cpulist == NULL))
        return 1;

    if (pset_info(PS_MYID, &type, &numcpus, cpulist) == 0)
    {
        for (u_int i = 0; i < numcpus; i++)
            if (processor_info (cpulist[i], &cpuinfo) == 0)
                count += (cpuinfo.pi_state == P_ONLINE);
    }
    else
        count = sysconf (_SC_NPROCESSORS_ONLN);
    free (cpulist);
    return count ? count : 1;
#elif defined(_SC_NPROCESSORS_ONLN)
    return sysconf(_SC_NPROCESSORS_ONLN);
#elif defined(_SC_NPROCESSORS_CONF)
    return sysconf(_SC_NPROCESSORS_CONF);
#else
#   warning "vlc_GetCPUCount is not implemented for your platform"
    return 1;
#endif
}
