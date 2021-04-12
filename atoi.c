#include "./atoi.h"

int my_atoi(const char arr[]) {
  long long number = 0;
  int is_negative = 0;
  int i = 0;
  if (arr[0] == '-') {
    if (strlen(arr) == 1) return 0;
    is_negative = 1;
    i++;
  }
  for (; i < strlen(arr); i++) {
    if (arr[i] < '0' || arr[i] > '9') return 0;
    number = number*10 + (int) arr[i] - (int) '0'; 
    if (number > INT_MAX) return INT_MAX;
    if (is_negative && -number < INT_MIN) return INT_MIN;
  }
  if (is_negative) number *= -1;
  return (int) number;
}

