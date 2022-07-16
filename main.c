#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"my_math.h"
#include"my_string.h"

MyString add(MyString num_one, MyString num_two);

int main(void){
    MyString num_one,num_two;
    num_one=my_string_init(num_one,0);
    num_two=my_string_init(num_two,0);

    num_one = read_number("Enter your first number: ");
    num_two = read_number("Enter your second number: ");

    print_number(multiply(num_one,num_two));
    return 0;
}





