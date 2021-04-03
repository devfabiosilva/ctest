#include <stdio.h>
#include <math.h>
#include <asserts.h>
#include <string.h>

int main(int argc, char **argv)
{
   double sq=sqrt(2.0);
   const char *str1="This is an simple string A";
   const char *str2="This is an simple string B";
   assert_true(2==2, "Function error A", "Success A");
   assert_false(10!=10, "Function error 2", "Sucess 2");
   assert_equal_int(1, 1, "Function error 3", "Success 3");
   assert_equal_double(sqrt(2), sq, "Error sqrt", "Success sqrt 3");
   assert_true(strlen(str1)==strlen(str2), "Error. String length does not match.", "Comparing \"str1\" with \"str2\"");
   assert_equal_byte((void *)str1, (void *)str2, strlen(str1), NULL, NULL, "Error. String does not match", "String comparation success");
   begin_tests();
   end_tests();
   return 0;
}
