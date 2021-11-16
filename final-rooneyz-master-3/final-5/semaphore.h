/*
 * semaphore.h
 *
 *  @since 2019-03-24
 *  @author Philip Gust
 */

#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_
#include <semaphore.h>

#ifdef __APPLE__
/*
 * Apple no longer supports unnamed semaphores, so the following
 * code implements unnamed semaphores in terms of named semaphores.
 * One wonders why Apple did not do this for compatibility.
 */

/**
 * Returns sem_t* to use with other semaphore functions.
 *
 * semaphore_open() returns a pointer-encoded integer semaphore
 * descriptor while semaphore_init() sets the sem_t location
 * pointed to by its sem_t* argument to the integer semaphore
 * descriptor. However, the other semaphore functions expect a
 * pointer encoded integer semaphore descriptor.
 *
 * This function returns the pointer-encoded integer file
 * descriptor from semaphore_open(), or fetches the integer
 * semaphore descriptor returned by semaphore_init() and
 * pointer-encodes it to use with other semaphore functions.
 *
 * @param sem pointer to semaphore
 * @return pointer-encoded semaphore
 */
static inline sem_t *sem_t_p(sem_t *sem) {
	return ((sem == SEM_FAILED) || ((unsigned long)sem <= SEM_VALUE_MAX)) ? sem : (void*)((char*)0+(*sem));
}

/**
 * Initializes  the  unnamed semaphore at the address pointed to by sem.
 * The value argument specifies the initial value for the semaphore.
 *
 * The pshared argument indicates whether this semaphore is to be shared
 * among  the threads of a process, or between processes. If pshared
 * has the value 0, then the semaphore is shared between the threads of
 * process, and should be located at some address that is visible to all
 * threads (e.g., a global variable, or a variable allocated dynamically
 * on the heap). If pshared is non-zero, then the semaphore is shared
 * between processes, and should be located in a region of shared memory.
 * Unused in this implementation.
 *
 * @param sem pointer to semaphore
 * @param pshared 0 if shared by process threads, 1 if shared by processes
 * @param value initial value for semaphore
 * @return 0 on success; on error, -1 is returned, and errno
 *     is set to indicate the error
 */
static inline int _sem_init(sem_t *sem, int pshared, unsigned int value) {
	char name[10];
	sprintf(name,"/%08x", (unsigned int)rand());  // random name
	*sem = (int)sem_open(name, O_CREAT | O_EXCL, 0644, value);
	sem_unlink(name);
	return (sem == SEM_FAILED) ? -1 : 0;
}
#define sem_init(sem_t_p, pshared, value) _sem_init(sem_t_p, pshared, value)

/**
 * Destroy an unnamed semaphore.
 *
 * @param sem pointer to semaphore
 * @return 0 on success; on error, -1 is returned, and errno
 *     is set to indicate the error
 */
static inline int _sem_destroy(sem_t *sem) {
	return sem_close(sem_t_p(sem));
}
#define sem_destroy(sem_t_p) _sem_destroy(sem_t_p)

/**
 * Deallocates the system resources associated with the named
 * semaphore referenced by sem and invalidates the descriptor.
 *
 * @param sem pointer to semaphore
 * @return 0 on success; on error, -1 is returned, and errno
       is set to indicate the error
 */
static inline int _sem_close(sem_t *sem) {
	return sem_close(sem_t_p(sem));
}
#define sem_close(sem_t_p) _sem_close(sem_t_p);

/**
 * Unlock a semaphore.
 *
 * @param sem pointer to semaphore
 * @return 0 on success; on error, -1 is returned, and errno
 *     is set to indicate the error
 */
static inline int _sem_post(sem_t *sem) {
    return sem_post(sem_t_p(sem));
}
#define sem_post(sem_t_p) _sem_post(sem_t_p)

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
static inline int _sem_wait(sem_t *sem) {
	return sem_wait(sem_t_p(sem));
}
#define sem_wait(sem_t_p) _sem_wait(sem_t_p)


/**
 * Same as sem_wait(), except that if the decrement cannot be immediately
 * performed, then call returns an error (errno set to EAGAIN) instead of
 * blocking.
 *
 * @param sem pointer to semaphore
 * @return 0 on success; on error, -1 is returned, and errno
 *     is set to indicate the error
 */
static inline int _sem_trywait(sem_t *sem) {
	return sem_trywait(sem_t_p(sem));
}
#define sem_try_wait(sem_t_p) _sem_try_wait(sem_t_p)

#endif  /* __APPLE__ */

#endif /* SEMAPHORE_H_ */
