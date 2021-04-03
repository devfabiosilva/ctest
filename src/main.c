#include <stdio.h>
#include <math.h>
#include <asserts.h>

int main(int argc, char **argv)
{
   double sq=sqrt(2.0);
   assert_true(2==2, "Function error A", "Success A");
   assert_true(10!=11, "Function error 2", "Sucess 2");
   assert_equal_int(1, 1, "Function error 3", "Success 3");
   assert_equal_double(1.0, 1.0, "Error sqrt", "Success sqrt 3"); 
   begin_tests();
   end_tests();
   return 0;
}
