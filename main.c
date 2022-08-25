#include "my_math.h"
#include "my_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  LL a;
  MyString num_one, num_two, result;
  char falesafe_msg[] = "this utility is under developed\n";

  num_one = my_string_init(num_one, 123);
  num_two = my_string_init(num_two, 2);

  print_op_code_msg();
  char op_code = getchar();

  // cleening screen before taking input();
  char p[10];
  fgets(p, 10, stdin);

  num_one = read_number("Enter your first number: ");
  num_two = read_number("Enter your second number: ");
  switch (op_code) {
  case '1':
    result = add(num_one, num_two);
    break;
  case '2':
    printf("%s", falesafe_msg);
  case '3':
    result = product(num_one, num_two);
    break;
  case '4':
    printf("%s", falesafe_msg);
    return 0;
    break;
  }
  print_number(result);
  free(num_one.number);
  free(num_two.number);
  return 0;
}
