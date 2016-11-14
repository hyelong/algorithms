/**
 * Template code for SCU COEN283 Winter 2015 PRJ2
 * @author Yi-Hua Edward Yang <edward.yang@xilinx.com>, 5/1/2014
 **/

#define _GNU_SOURCE

#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <err.h>

#ifndef PRJ2_TIME_H
#define PRJ2_TIME_H

/**
 * Time elasped in msec from struct timespec *t1 to struct timespec *t2
 */
#define TIMEMSEC(t1,t2) ( ((t2)->tv_nsec - (t1)->tv_nsec)/1000000 + \
                          ((t2)->tv_sec  - (t1)->tv_sec)*1000 )

/**
 * Time elasped in usec from struct timespec *t1 to struct timespec *t2
 */
static inline
long long TIMEUSEC(const struct timespec* t1, const struct timespec* t2) {
  //printf("nsec: %ld\n",((t2)->tv_nsec - (t1)->tv_nsec)/1000);
  //printf("sec: %ld\n", ((t2)->tv_sec  - (t1)->tv_sec)*1000000);
  long long time_diff = ((t2)->tv_nsec - (t1)->tv_nsec)/1000 + ((t2)->tv_sec  - (t1)->tv_sec)*1000000;
  //printf("time diff: %lld\n", time_diff);
  return time_diff ;
}
/**
 * Compare two struct timespec *t1 and *t2.
 * @return positive integer if *t1 > *t2; negative if *t1 < *t2; 0 otherwise
 */
static inline
int timecmp(const struct timespec *t1, const struct timespec *t2)
{
  struct timespec td = {
    t1->tv_sec - t2->tv_sec,
    t1->tv_nsec - t2->tv_nsec
  };
  return ((((td.tv_sec > 0) - (td.tv_sec < 0)) << 1) +
	  ((td.tv_nsec > 0) - (td.tv_sec < 0)));
}


/**
 * *t1 = *t2 + *t3
 */
static inline
void timeadd(struct timespec *t1,
             const struct timespec *t2, const struct timespec *t3)
{
  t1->tv_sec = t2->tv_sec + t3->tv_sec;
  t1->tv_nsec = t2->tv_nsec + t3->tv_nsec;
  if (t1->tv_nsec >= 1000000000LL) {
    t1->tv_sec ++;
    t1->tv_nsec -= 1000000000LL;
  }
}

static inline
void timeaddusec(struct timespec *t1,
                 const struct timespec *t2, const int time_usec)
{
  t1->tv_nsec = t2->tv_nsec + time_usec*1000;
  if (t1->tv_nsec >= 1000000000LL) {
    t1->tv_sec ++;
    t1->tv_nsec -= 1000000000LL;
  }
}


/**
 * *t1 = *t2 - *t3
 */
static inline
void timesub(struct timespec *t1,
             const struct timespec *t2, const struct timespec *t3)
{
  t1->tv_sec = t2->tv_sec - t3->tv_sec;
  t1->tv_nsec = t2->tv_nsec - t3->tv_nsec;
  if (t1->tv_nsec < 0) {
    t1->tv_sec --;
    t1->tv_nsec += 1000000000LL;
  }
}

static inline
void timesubusec(struct timespec *t1,
                 const struct timespec *t2, const int time_usec)
{
  t1->tv_nsec = t2->tv_nsec - time_usec*1000;
  if (t1->tv_nsec < 0) {
    t1->tv_sec --;
    t1->tv_nsec += 1000000000LL;
  }
}


/**
 * Generate a random time in *tsptr, using random seed in *seedp,
 * between min_ms and max_ms milliseconds
 */
static inline
void timerand_ms(struct timespec *tsptr, unsigned int *seedp,
                 int min_ms, int max_ms)
{
  if (max_ms >= 1000000) {
    warnx("Generated random time should be shorter than 1000 sec");
    max_ms = 999999;
  }

  if (min_ms < 10) {
    warnx("Generated random time should be longer than 10 msec");
    min_ms = 10;
  }
  if (max_ms < min_ms) {
    warnx("Maximum random time should be longer than minimum random time");
    max_ms = min_ms;
  }

  tsptr->tv_sec = 0;
  tsptr->tv_nsec = (((uint64_t)rand_r(seedp))*(max_ms-min_ms)/RAND_MAX +
		    min_ms) * 1000000;
}

#endif
