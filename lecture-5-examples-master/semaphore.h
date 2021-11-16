/*
 * semaphore.h
 *
 *  @since 2019-03-24
 *  @author Philip Gust
 */

#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_
#ifdef __APPLE__
#include <dispatch/dispatch.h>  // Grand Central Dispatch function
#include <errno.h>

/** Define sem_t as dispatch_semaphore_t -- works for litte-endian */
typedef dispatch_semaphore_t sem_t;

/* this should go in limits.h> */
#define SEM_VALUE_MAX 32767
#define SEM_FAILED ((sem_t *)-1)

//#include <sys/cdefs.h>

/**
 * Initialize an unnamed semaphore.
 * Passing zero for the value is useful for when two threads
 * need to reconcile the completion of a particular event.
 * Passing a value greater than zero is useful for managing
 * a finite pool of resources, where the pool size is equal
 * to the value.
 *
 * @param sem pointer to semaphore
 * @param pshared 0 if shared by process threads, 1 if shared by processes
 * @param value initial value for semaphore
 *
 * @return 0 on success; on error, -1 is returned, and errno
       is set to indicate the error
 */
static inline int sem_init(sem_t *sem, int pshared, unsigned int value) {
	if (pshared != 0) {
		errno = ENOSYS;  // shared process not supported
		return -1;
	}
	return ((*sem = dispatch_semaphore_create(value)) == NULL) ? -1 : 0;
}

/**
 * Destroy an unnamed semaphore.
 *
 * @param sem pointer to semaphore
 * @return 0 on success; on error, -1 is returned, and errno
 *     is set to indicate the error
 */
static inline int sem_destroy(sem_t *sem) {
	dispatch_release(*sem);
	return 0;
}

/**
 * Unlock a semaphore.
 *
 * @param sem pointer to semaphore
 * @return 0 on success; on error, -1 is returned, and errno
 *     is set to indicate the error
 */
static inline int sem_post(sem_t *sem) {
    return dispatch_semaphore_signal(*sem);
}

/**
 * Decrements (locks) the semaphore pointed to by sem.  If
 * the semaphore's value is greater than zero, then the decrement
 * proceeds, and the function returns, immediately.  If the semaphore
 * currently has the value zero, then the call blocks until either it
 * becomes possible to perform the decrement (i.e., the semaphore value
 * rises above zero), or a signal handler interrupts the call.
 *
 * @param sem pointer to semaphore
 * @return 0 on success; on error, -1 is returned, and errno
 *     is set to indicate the error
 */
static inline int sem_wait(sem_t *sem) {
	return dispatch_semaphore_wait(*sem, DISPATCH_TIME_FOREVER);
}

/**
 * Same as sem_wait(), except that abs_timeout specifies a
 * limit on the amount of time that the call should block if
 * the decrement cannot be immediately performed.
 *
 * @param sem pointer to semaphore
 * @param abs_timeout argument points to a structure that specifies
 *     an absolute timeout in seconds and nanoseconds since the Epoch,
 *     1970-01-01 00:00:00 +0000 (UTC).
 * @return 0 on success; on error, -1 is returned, and errno
 *     is set to indicate the error
 */
static inline int sem_timedwait(sem_t *sem, struct timespec *abs_timeout) {
	if (dispatch_semaphore_wait(*sem, dispatch_walltime(abs_timeout,0)) == 0) {
		return 0;
	} else {
		errno = ETIMEDOUT;
		return -1;
	}
}
/**
 * Same as sem_wait(), except that if the decrement cannot be immediately
 * performed, then call returns an error (errno set to EAGAIN) instead of
 * blocking.
 *
 * @param sem pointer to semaphore
 * @return 0 on success; on error, -1 is returned, and errno
 *     is set to indicate the error
 */
static inline int sem_trywait(sem_t *sem) {
	// returns zero on success, or non-zero if the timeout occurred
	if (dispatch_semaphore_wait(*sem, DISPATCH_TIME_NOW) == 0) {
		return 0;
	} else {
		errno = EAGAIN;
		return -1;
	}
}

__BEGIN_DECLS
int sem_getvalue(sem_t * __restrict, int * __restrict) __deprecated;
int sem_close(sem_t *);
sem_t * sem_open(const char *, int, ...);
int sem_post(sem_t *);
int sem_unlink(const char *);
__END_DECLS


#else
#include <semaphore.h>
#endif

#endif /* SEMAPHORE_H_ */
