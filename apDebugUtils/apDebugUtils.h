#ifndef APDEBUGUTILS_H
#define APDEBUGUTILS_H
// apDebugUtils provides debug printing macros that compile for both Arduino and PC.
// If compiled on Arduino, it prints to Serial. If compiled on PC, printf writes to stdout.
// If DEBUG is not #defined, these prints are excluded from compilation and have no runtime cost.
// DP()      Debug Print
// DPL()     Debug Println
// DPX()     Debug Print with source File and Line info
// DPLX()    Debug Println with source File and Line info
// DP_PTR()  Print int pointer as HEX value
// FILENAME  A macro that returns the filename excluding the path (__FILE__ includes the path)
// Ideas initially from https://forum.arduino.cc/index.php?topic=46900.0

  #ifdef DEBUG
    // __FILE__ includes the path, so FILENAME excludes the path
    #define FILENAME (strchr(__FILE__, '/') ? (strrchr("/" __FILE__, '/') + 1) : (strrchr("\\" __FILE__, '\\') + 1))
    #ifdef ARDUINO
      #define DP(...)  Serial.print(__VA_ARGS__)
      #define DPL(...) Serial.println(__VA_ARGS__)
      #define DP_PTR(ptr) Serial.print((int)ptr, HEX)
      #define DPX(...)            \
         DP(millis());            \
         DP(": ");                \
         DP(FILENAME);            \
         DP(':');                 \
         DP(__LINE__);            \
         DP(' ');                 \
         DP(__PRETTY_FUNCTION__); \
         DP(' ');                 \
         DP(__VA_ARGS__)
       #define DPLX(...) DPX(__VA_ARGS__); DPL()
    #else //PC Debugging
      #include <cstdio>
      #include <cstring> // For strchr() and strrchr() in FILENAME macro
      int typed_println()                { return printf("\n"); }
      int typed_print(const char *val)   { return printf("%s",   val); }
      int typed_println(const char *val) { return printf("%s\n", val); }
      int typed_print(int val)           { return printf("%d",   val); }
      int typed_println(int val)         { return printf("%d\n", val); }
      int typed_print(char val)          { return printf("%c",   val); }
      int typed_println(char val)        { return printf("%c\n", val); }
      int typed_print(bool val)          { return printf("%s",   val ? "true" : "false"); }
      int typed_println(bool val)        { return printf("%s\n", val ? "true" : "false"); }
      //Cast pointer to (void *) to print memory address
      int typed_print(void *val)         { return printf("%p",   val); }
      int typed_println(void *val)       { return printf("%p\n", val); }
      
      #define DP(...)  typed_print(__VA_ARGS__)
      #define DPL(...) typed_println(__VA_ARGS__)
      #define DP_PTR(ptr) DP(ptr)
      #define DPX(...)            \
         DP(FILENAME);            \
         DP(":");                 \
         DP(__LINE__);            \
         DP(" ");                 \
         DP(__PRETTY_FUNCTION__); \
         DP(" ");                 \
         DP(__VA_ARGS__)
       #define DPLX(...) DPX(__VA_ARGS__); DPL()
    #endif
  #else //No debug
    #define DP(...)
    #define DPL(...)
    #define DP_PTR(...)
    #define DPX(...)
    #define DPLX(...)
  #endif
#endif
