No special instructions to run.

I chose to implement the semaphore mechanism.
similar to how files are implemented in xv6:

Each process keeps a semaphore pointer array, osem.
There's a global semaphore table, stable.

Whenever the user uses a semaphore, an semaphore descriptor (sd).
is used. The sd is actually an index in the process' semaphore array,
where the semaphore pointer is kept.