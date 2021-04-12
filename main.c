#include <string.h>
#include <stdlib.h>
#include "./atoi.h"
#include "./dynamic_array.h"

#define NUM_SIZE 11

void print_list(List list) {
  char * element;
  while ((element = pop(&list))) printf("%s\n",element);
}

void invalid_syntax() {
  printf("Invalid syntax");
  exit(1);
} 

char * parseNumber(const char arr[],int start_index) {
  if (arr[start_index] == '\0') return 0;
  char * number_string = malloc(NUM_SIZE);
  memset(number_string,'0',NUM_SIZE);
  int arr_index = start_index;
  int num_index = 0;
  if (arr[arr_index] == '-') 
    number_string[num_index++] = arr[arr_index++];
  while (arr[arr_index] != '\0') {
    number_string[num_index++] = arr[arr_index++];
    number_string[num_index] = '\0';
    if (!my_atoi(number_string)) {
      if (strcmp(number_string,"0") != 0) 
        number_string[--num_index] = '\0';
      break;
    }
  }
  return strlen(number_string) ? number_string : NULL;
  
}

int operator_rank(char operator) {
  switch(operator) {
    case '+': 
    case '-': return 0;
    case '*':
    case '/': return 1;
  }
  return -1;
}

int parseOperator(List *mainList, List *opList, char operator) {
  char * operator_string = malloc(2);
  operator_string[0] = operator;
  operator_string[1] = '\0';
  switch (operator) {
    case '*': 
    case '/':
    case '+':
    case '-': { 
        char * op;
        while ((op = get_last_element(opList)) && operator_rank(op[0]) >= operator_rank(operator)) 
          push(mainList,pop(opList));
    }
    case '(': 
      push(opList,operator_string);
      break;
    case ')': {
      char * op;
      while ((op = pop(opList)) && op[0] != '(') push(mainList,op);
      if (!op) invalid_syntax();
      break; 
    }
    default: 
        return 0;
  }
  return 1;
}

double calculate(double num1, double num2, char * operator) {
  switch (operator[0]) {
    case '+': return num1+num2;
    case '-': return num1-num2;
    case '*': return num1*num2;
    case '/': return num1/num2;
  }
  invalid_syntax();
}

int is_operator(char * str) {
  if (strlen(str) != 1) return 0;
  switch (str[0]) {
    case '+':
    case '-':
    case '*':
    case '/': return 1;
  }
  return 0;
}


double compute_postfix(List *mainList) {
  double stack[mainList->size];
  int i = -1;
  char * element;
  double num1, num2;
  while (element = pop(mainList)) {
    if (is_operator(element)) {
      if (i <= 0) return 0;
      num1 = stack[i--];
      num2 = stack[i];
      stack[i] = calculate(num2,num1,element);
    }
    else stack[++i] = my_atoi(element); 
  }
  if (i != 0) return 0;
  return stack[0];
}


double shunting_yard(const char arr[]) {
  List mainList = new_list();
  List opList = new_list();
  int i = 0;
  int is_operator;
  char * number;
  while (arr[i] != '\0') {
    is_operator = parseOperator(&mainList,&opList,arr[i]);
    if (!is_operator || i == 0) {
      number = parseNumber(arr,i);
      if (number) {
        if (is_operator) pop(&opList);
        push(&mainList,number);
        i = i + strlen(number) - 1;
      }
      else if (arr[i] != ' ' && !is_operator) invalid_syntax();
    }
    i++;
  }
  char * element;
  while (element = pop(&opList)) push(&mainList,element);
  reverse(&mainList);
  return compute_postfix(&mainList);
}

double my_calc(const char arr[]) {
  return shunting_yard(arr);
}

int main(int argc, char * argv[]) {
  double result = my_calc(argv[1]);
  if (result == (int) result) 
    printf("%d\n",(int) result);
 else 
   printf("%g\n",result);
}
