#ifndef MY_STRING
#define MY_STRING
#include <stdio.h>
#include <stdlib.h>
typedef struct {
  char *number;
  int len;
} MyString;

// FUNCTION DECLARATIONS ARE PLACED HERE;
MyString copy(MyString);
MyString my_string_init(MyString, int);
MyString re_init(MyString, int);
MyString read_number(char *);
void print_number(MyString);
MyString my_append(MyString, char);

MyString copy(MyString st) {
  MyString num;
  num = my_string_init(num, 0);
  for (int i = 0; i < st.len; i++)
    num = my_append(num, st.number[i]);
  return num;
}

MyString my_string_init(MyString var, int len) {
  var.number = (char *)malloc(sizeof(char) * len);
  var.len = len;
  return var;
}

MyString re_init(MyString var, int len) {
  var.number = (char *)realloc(var.number, sizeof(char) * len);
  for (int i = var.len; i < len; i++) {
    var.number[i] = 48;
  }
  var.len = len;
  return var;
}

MyString my_append(MyString st, char ch) {

  if (!st.number) {
    printf("uninitialized object of MyString\n");
    exit(1);
  } else {
    st.number = (char *)realloc(st.number, st.len + 1);
    st.number[st.len] = ch;
  }
  st.len += 1;
  return st;
}

void print_number(MyString num) {
  for (int i = 0; i < num.len; i++) {
    printf("%c", num.number[i]);
  }
  printf("\n");
}
/// READS A VALID DECIMAL NUMBER OR SHOWS ERROR.
MyString read_number(char *msg) {
  printf("%s", msg);
  MyString st;
  my_string_init(st, 0);
  char ch;
  int index = 0;
  ch = getchar();
  st.len = 0;
  st.number = (char *)malloc(sizeof(char));
  while (ch != '\r' && ch != '\n') {
    if (ch >= 48 && ch <= 57) {
      st.number = (char *)realloc(st.number, index + 1);
      st.number[index] = ch;
      st.len += 1;
      index += 1;
      st.number = (char *)realloc(st.number, index + 1);
    } else {
      index = 0;
      st.len = 0;
      st.number = (char *)realloc(st.number, 0);
      printf("PLZ, enter a decimal number: ");
    }
    ch = getchar();
  }
  return st;
}

MyString create_sub_string(MyString st, int s, int e) {
  MyString tmp1;
  tmp1 = my_string_init(tmp1, 0);
  for (int i = s; i <= e; i++)
    tmp1 = my_append(tmp1, st.number[i]);
  return tmp1;
}

#endif
