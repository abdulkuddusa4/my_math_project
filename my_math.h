#ifndef MY_MATH
#define MY_MATH

#include"my_string.h"
MyString _ADD(MyString num_one,MyString num_two);
MyString _MULTIPLY(MyString factor,MyString multiplier);
int countdown(char *st,int i,int size,int pos);
char DECAY(char ch);

//add function
MyString add(MyString num_one, MyString num_two){
    //reversing char digits
    MyString tmp1,tmp2,sum,tmp_sum;
    tmp1=my_string_init(tmp1,num_one.len);
    tmp2=my_string_init(tmp2,num_two.len);
    for(int i=0;i<num_one.len;i++){
        tmp1.number[tmp1.len-i-1]=num_one.number[i];
    }
    for(int i=0;i<num_two.len;i++){
        tmp2.number[tmp2.len-i-1]=num_two.number[i];
    }

    int max_len=tmp1.len>tmp2.len?tmp1.len:tmp2.len;
    tmp1 = re_init(tmp1,max_len);
    tmp2 = re_init(tmp2,max_len);
    tmp_sum = _ADD(tmp1,tmp2);
    sum = my_string_init(sum,tmp_sum.len);
    for(int i=0;i<tmp_sum.len;i++){
        sum.number[i]=tmp_sum.number[tmp_sum.len-i-1];
    }
    return sum;
}

// function for adding reversed numbers of equal length
MyString _ADD(MyString num_one,MyString num_two){

    int carry=0;
    MyString summed_st;
    summed_st=my_string_init(summed_st,0);

    if(num_one.len!=num_two.len){
        printf("error: in func:_ADD ** two string must be of equal size **\n");
        exit(1);
    }
    for(int i=0,a,b,sum;i<num_one.len;i++){
        a=num_one.number[i];
        b=num_two.number[i];
        sum=a+b+carry-48*2;

        carry=sum/10;
        summed_st = my_append(summed_st,(sum%10)+48);
    }
    if(carry)summed_st=my_append(summed_st,(carry)+48);
    return summed_st;
}

//multipication
MyString multiply(MyString num_one, MyString num_two){
    // selecting multiplier and factor;
    MyString multiplier,factor,product;
    if(num_one.len>num_two.len){
        multiplier = num_two;
        factor = num_one;
    }else{
        multiplier = num_one;
        factor = num_two;
    }
    product = _MULTIPLY(factor,multiplier);
    return product;
}

MyString _MULTIPLY(MyString factor,MyString multiplier){
    MyString product;
    product = my_string_init(product,0);
    while(countdown(multiplier.number,0,multiplier.len,0)){
        product = add(product,factor);
    }
    return product;
}

int countdown(char *st,int i,int size,int pos){
  if(i==size-1){
    if(st[i]-48){
      st[i]=DECAY(st[i]);
      return 1;
    }
    else{
      if(pos){
        for(int j=pos-1;j<=i;j++){
          st[j]=DECAY(st[j]);
        }
        return 1;
      }
      else return 0;
    }
  }
  else{
    if(st[i]-48){
      return countdown(st,i+1,size,i+1);
    }
    else{
      return countdown(st,i+1,size,pos);
    }
  }
}
char DECAY(char ch){
    return (((ch)%10+1)%10)+48;
}

#endif // MY_MATH


