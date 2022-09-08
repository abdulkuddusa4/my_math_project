#ifndef MY_MATH
#define MY_MATH
typedef long long int LL;

#include "my_string.h"
#include <stdio.h>
#define KARATSUBA_CUTOFF 2

// FUNCTIONs THAT IS PUBLIC
MyString add(MyString, MyString);
MyString product(MyString, MyString);

// FUNCTIONs ONLY FOR INTERNAL USES.
MyString ADD(MyString, MyString, int);
MyString _ADD(MyString, MyString);
MyString _MULTIPLY(MyString, MyString);
MyString _Product(MyString, MyString);
int countdown(char *, int, int, int);
unsigned long long __to_int(MyString);
int POW(int, int);
char DECAY(char);

// RETURNS ADDITION AND FOR PUBLIC USE.
MyString add(MyString a, MyString b) { return ADD(a, b, 0); }

// A WRAPPER TO FUNCTION '_ADD'.ONLY FOR INTERRNEL USE.
MyString ADD(MyString num_one, MyString num_two, int product_flag) {
  // reversing char digits
  MyString tmp1, tmp2, sum, tmp_sum;
  tmp1 = my_string_init(tmp1, num_one.len);
  tmp2 = my_string_init(tmp2, num_two.len);

  tmp1 = re_init(tmp1, num_one.len);
  tmp2 = re_init(tmp2, num_two.len);
  for (int i = 0; i < num_one.len; i++) {
    tmp1.number[tmp1.len - i - 1] = num_one.number[i];
  }
  for (int i = 0; i < num_two.len; i++) {
    tmp2.number[tmp2.len - i - 1] = num_two.number[i];
  }

  int max_len = tmp1.len > tmp2.len ? tmp1.len : tmp2.len;
  tmp1 = re_init(tmp1, max_len);
  tmp2 = re_init(tmp2, max_len);
  tmp_sum = _ADD(tmp1, tmp2);
  sum = my_string_init(sum, tmp_sum.len);
  for (int i = 0; i < tmp_sum.len; i++) {
    sum.number[i] = tmp_sum.number[tmp_sum.len - i - 1];
  }
  free(tmp1.number);
  free(tmp2.number);
  free(tmp_sum.number);
  if (product_flag == 1)
    free(num_one.number);
  else if (product_flag == 2)
    free(num_two.number);
  return sum;
}

// A WRAPPER TO FUNCTION "_MULTIPLY". ONLY FOR INTERNAL USE.
MyString multiply(MyString num_one, MyString num_two) {
  // selecting multiplier and factor;
  MyString multiplier, factor, product;
  if (num_one.len > num_two.len) {
    multiplier = num_two;
    factor = num_one;
  } else {
    multiplier = num_one;
    factor = num_two;
  }
  product = _MULTIPLY(factor, multiplier);
  return product;
}

// USES OLD SCHOOL ALGORITHM TO CALCULATE PRODUCT.ONLY FOR INTERNAL USE.
MyString _MULTIPLY(MyString factor, MyString multiplier) {
  MyString product;
  product = my_string_init(product, 0);
  unsigned long long _C = __to_int(multiplier);
  while (countdown(multiplier.number, 0, multiplier.len, 0))
  {
    product = ADD(product, factor, 1);
  }
  return product;
}

// NOTHING BUT A WRAPPER TO THE ORIGINAL FUNCTION "_Product" THAT USSES
// KARATSUBA ALGORITHM. FOR PUBLIC USE.
MyString product(MyString num_one, MyString num_two) {
  return _Product(num_one, num_two);
}

// FUNCTION TO PERFORM ADDITION.IT DOES ADDITION ON REVERSED STRING NUMBER.ONLY
// ONLY FOR INTERNAL USE.
MyString _ADD(MyString num_one, MyString num_two) {

  int carry = 0;
  MyString summed_st;
  summed_st = my_string_init(summed_st, 0);

  if (num_one.len != num_two.len) {
    printf("error: in func:_ADD ** two string must be of equal size **\n");
  }
  for (int i = 0, a, b, sum; i < num_one.len; i++) {
    a = num_one.number[i];
    b = num_two.number[i];
    sum = a + b + carry - 48 * 2;

    carry = sum / 10;
    summed_st = my_append(summed_st, (sum % 10) + 48);
  }
  if (carry)
    summed_st = my_append(summed_st, (carry) + 48);
  return summed_st;
}

// THE FUNCTION TO CALCULATE PRODUCT EFFEICIENTLY.IT USES KARATSUBA ALGORITHM.
// ONLY FOR INTERNAL USE.
MyString _Product(MyString num_one, MyString num_two) {
  if (num_one.len < KARATSUBA_CUTOFF || num_two.len < KARATSUBA_CUTOFF) {
    return multiply(num_one, num_two);
  } else {
    LL NA, NB, slice_a, slice_b;
    MyString p1, p2, p3, p4;

    slice_a = (num_one.len - 1) / 2;
    slice_b = (num_two.len - 1) / 2;
    NA = num_one.len - 1 - slice_a;
    NB = num_two.len - 1 - slice_b;

    MyString _A = create_sub_string(num_one, 0, slice_a);
    MyString _B = create_sub_string(num_one, slice_a + 1, num_one.len - 1);
    MyString _C = create_sub_string(num_two, 0, slice_b);
    MyString _D = create_sub_string(num_two, slice_b + 1, num_two.len - 1);

    p1 = _Product(copy(_A), copy(_C));
    p2 = _Product(copy(_A), copy(_D));
    p3 = _Product(copy(_B), copy(_C));
    p4 = _Product(copy(_B), copy(_D));

    p1 = re_init(p1, p1.len + (NA + NB));
    p2 = re_init(p2, p2.len + NA);
    p3 = re_init(p3, p3.len + NB);
    MyString _result = ADD(ADD(ADD(p1, p2, 0), p3, 0), p4, 0);
    free(p1.number);
    free(p2.number);
    free(p3.number);
    free(p4.number);

    return _result;
  }
}

// help to multipy as school algorithm.ONLY FOR INTERNAL USE.
int countdown(char *st, int i, int size, int pos) {
  if (i == size - 1) {
    if (st[i] - 48) {
      st[i] = DECAY(st[i]);
      return 1;
    } else {
      if (pos) {
        for (int j = pos - 1; j <= i; j++) {
          st[j] = DECAY(st[j]);
        }
        return 1;
      } else
        return 0;
    }
  } else {
    if (st[i] - 48) {
      return countdown(st, i + 1, size, i + 1);
    } else {
      return countdown(st, i + 1, size, pos);
    }
  }
}

// helper for countdown function.ONLY FOR INTERNAL USE.
char DECAY(char ch) { return (((ch) % 10 + 1) % 10) + 48; }

int POW(int a, int n) { return n ? a * POW(a, n - 1) : 1; }

// CONVERTS A MyString OBJECT TO UNSIGNED 64 BIT INTEGER.
unsigned long long __to_int(MyString obj) {
  if (!(obj.len < KARATSUBA_CUTOFF)) {
    printf("\n\033[0;31m"
           "error occured in my_math.h in func: __to_int\n"
           "the given string excedded the KARATSUBA length\n"
           "remember, the function is only for certain perpose\n"
           "THE GIVEN OBJECT CAN NOT BE CONVERTED 64 BIT INT \n"
           "this error may cause some other error in the program"
           ".\n THAT'S WHY We,re closing this application.\n"
           "\033[0m\n");
  }
  unsigned long long num = 0;
  for (int i = 0, j = obj.len; i < obj.len; i++, j--) {
    num += (obj.number[i] - 48) * POW(10, j - 1);
  }
  return num;
}
#endif // MY_MATH
