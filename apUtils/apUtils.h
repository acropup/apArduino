#ifndef APUTILS_H
#define APUTILS_H
// apUtils includes useful functions and macros for Arduino programming, plus copies of some
// of the common built-in Arduino macros so that a library lightly targeted for Arduino
// has a better chance of compiling and running on PC without including Arduino.h.
// This list grows on an as-needed basis, and is in no way comprehensive.

#ifndef ARDUINO
  //Redefine macros that come from Arduino.h so that code expecting them can still work on non-arduino platforms.
  #define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#endif

#define ARRAY_LENGTH(arr) (sizeof(arr)/sizeof(arr[0]))
//Make an ASCII letter lowercase, so you can test equality against just the lowercase value.
#define LCASE(chr) (chr | 0x20)

// Signed modulus without mod operator. Returns a positive val % max.
// Only fast if val is relatively close to being within [0, max).
int16_t wrap0(int16_t val, int16_t max) {
  while (val < 0)    val+=max;
  while (val >= max) val-=max;
  return val;
}

#endif