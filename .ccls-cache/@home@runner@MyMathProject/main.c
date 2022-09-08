#include "__conio.h"
#include "my_math.h"
#include "my_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void) {
  LL a;
  MyString num_one, num_two, result;
  char falesafe_msg[] =
      "\n\033[0;31mthis utility is under developed\033[0m \n\n";

  op_msg_section:
  print_op_code_msg();
  int op_code = __getche() - 48;

  if (!(op_code >=0 && op_code <=3)) {
  printf("\n\033[0;31mwrong input\033[0m \n\n");
  goto op_msg_section;
  }

  //CHECKING FOR AVAILABLE UTILITY
  int  available_utility[4]={[0]=1,[2]=1};
  if(! available_utility[op_code]){
    printf(falesafe_msg);
    goto op_msg_section;
  }
  num_one = read_number("Enter your first number: ");
  num_two = read_number("Enter your second number: ");

  switch (op_code) {
  case 0:
    result = add(num_one, num_two);
    break;
  case 2:
    result = product(num_one, num_two);
    break;
  }
  printf("\033[0;32mANSWER: \n");
  print_number(result);
  printf("\033[0;0m");
  free(result.number);
  free(num_one.number);
  free(num_two.number);
  return 0;
}
