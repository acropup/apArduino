#ifndef APTEXTPARSER_H
#define APTEXTPARSER_H
// apTextParser contains utility functions for parsing basic text files,
// including reading signed and unsigned ints, and reporting parse errors nicely.
#include "apDebugUtils.h"

bool is_whitespace(char const c) {
  return c == ' '  ||
         c == '\t' ||
         c == '\r' ||
         c == '\n';
}

bool is_whitespace_or_null (char const c) {
  return c == '\0' ||
         c == ' '  ||
         c == '\t' ||
         c == '\r' ||
         c == '\n';
}

/* Parses an ASCII decimal integer in string str.
 * Set allow_sign = true if you want to allow +/- preceding the digits.
 * Assigns parsed integer value to result if successful.
 * Returns the number of characters consumed if successful, or 0 if failed. 
 */
uint8_t read_int(int *result, char const *str, bool allow_sign = false) {
  int res = 0;
  uint8_t i = 0;
  bool is_negative = false;
  if (allow_sign) {
    uint8_t s = str[i];
    if (s == '+' || s == '-') {
      is_negative = s == '-';
      i++;
    }
  }
  uint8_t d = str[i] - '0';
  while (d < 10) {
    res = res * 10 + d;
    i++;
    d = str[i] - '0';
  }
  //Check if found a number
  if (is_negative && i > 1) {
    *result = -res;
    return i;
  } else if (i > 0) {
    *result = res;
    return i; //Return number of characters consumed
  }
  //Integer not found
  return 0;
}

/* Parses an ASCII decimal integer in string *str, and advances *str
 * pointer by number of bytes parsed.
 * Set allow_sign = true if you want to allow +/- preceding the digits.
 * Assigns parsed integer value to result if successful.
 * Returns true if integer parsed, false if not.
 */
bool eat_int(int *result, char const **str, bool allow_sign = false) {
  uint8_t n = read_int(result, *str, allow_sign);
  if (n) {
    (*str)+=n;
    return true;
  }
  return false;
}

/* If the first character in **str is equal to the token,
 * advance str pointer by one and return true. Return false
 * if first char doesn't match token.
 * WARNING: Do not pass '\0' as token, or it'll advance past end of string!
 */
bool eat_char(char token, char const **str) {
  if (**str == token) {
    ++(*str);
    return true;
  }
  return false;
}

// Moves **str pointer ahead to next whitespace character, or null-terminator.
// Returns number of non-whitespace characters skipped.
size_t skip_until_whitespace(char const **str) {
  size_t skipped = 0;
  while (!is_whitespace_or_null(**str)) {
    ++(*str);
    ++skipped;
  }
  return skipped;
}

// Moves **str pointer ahead to next non-whitespace character, or null-terminator.
// Returns number of whitespace characters skipped. 
size_t skip_whitespace(char const **str) {
  size_t skipped = 0;
  while (**str != '\0' && is_whitespace(**str)) {
    ++(*str);
    ++skipped;
  }
  return skipped;
}

//Like strlen() but also stops on whitespace because whitespace is a command delimiter
size_t cmdlen(char const *cmd) {
  size_t i = 0;
  while (!is_whitespace_or_null(cmd[i])) { i++; }
  return i;
}

//Like strnlen() but also stops on whitespace because whitespace is a command delimiter
size_t cmdnlen(char const *cmd, size_t max_len) {
  size_t i = 0;
  while (i < max_len && !is_whitespace_or_null(cmd[i])) { i++; }
  return i;
}

//Reports error parsing message, showing message, problem command,
//and points to the character at which the problem occurred.
void report_error(char const *error_msg, char const *cmd, char const *error_pos) {
  int max_error_len = 80;
  char msg[max_error_len + 1];
  int offset = error_pos - cmd;
  snprintf(msg, max_error_len, "Error: %s at index %d:", error_msg, offset);
  DPL(msg); //Print the error message

  //cmd might have many commands separated by whitespace, so make sure just to print the current command
  size_t cmd_len = cmdlen(cmd);
  char the_cmd[cmd_len + 1];
  memcpy(the_cmd, cmd, cmd_len);
  the_cmd[cmd_len] = '\0';
  DPL(the_cmd); //Print the failed command

  //Print ^ arrow at character that the error occured on
  while(offset--) DP(' ');
  DPL('^');
}

#endif
