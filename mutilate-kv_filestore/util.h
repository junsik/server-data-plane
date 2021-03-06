#ifndef UTIL_H
#define UTIL_H

#include <sys/time.h>
#include <time.h>

inline double tv_to_double(struct timeval *tv) {
  return tv->tv_sec + (double) tv->tv_usec / 1000000;
}

inline void double_to_tv(double val, struct timeval *tv) {
  long long secs = (long long) val;
  long long usecs = (long long) ((val - secs) * 1000000);

  tv->tv_sec = secs;
  tv->tv_usec = usecs;
}

inline double get_time_accurate() {
#if USE_CLOCK_GETTIME
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
  //  clock_gettime(CLOCK_REALTIME, &ts);
  return ts.tv_sec + (double) ts.tv_nsec / 1000000000;
#else
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv_to_double(&tv);
#endif
}

inline double get_time() {
  //#if USE_CLOCK_GETTIME
  //  struct timespec ts;
  //  clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
  //  //  clock_gettime(CLOCK_REALTIME, &ts);
  //  return ts.tv_sec + (double) ts.tv_nsec / 1000000000;
  //#else
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv_to_double(&tv);
  //#endif
}

inline uint64_t htonll(uint64_t x)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
  uint64_t y = ((0x00000000000000ff & x) << 56) |
               ((0x000000000000ff00 & x) << 40) |
               ((0x0000000000ff0000 & x) << 24) |
               ((0x00000000ff000000 & x) <<  8) |
               ((0x000000ff00000000 & x) >>  8) |
               ((0x0000ff0000000000 & x) >> 24) |
               ((0x00ff000000000000 & x) >> 40) |
	       ((0xff00000000000000 & x) >> 56);
  return y;
#else
  return x;
#endif
}

inline uint64_t ntohll(uint64_t x)
{
#if __BYTE_ORDER == __ORDER_LITTLE_ENDIAN__
  uint64_t y = htonll(x);
  return y;
#else
  return x;
#endif
}

void sleep_time(double duration);

uint64_t fnv_64_buf(const void* buf, size_t len);
inline uint64_t fnv_64(uint64_t in) { return fnv_64_buf(&in, sizeof(in)); }

void generate_key(int n, int length, char *buf);

#endif // UTIL_H
