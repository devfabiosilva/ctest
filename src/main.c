#include <stdio.h>
#include <math.h>
#include <asserts.h>
#include <string.h>

void cb_func_on_error(void *ctx)
{
   printf("\nExiting on error test\n\t%s\n", (const char *)ctx);
}

int main(int argc, char **argv)
{
   double sq=sqrt(2.0);
   const char *str1="This is an simple string A";
   const char *str2="This is an simple string B";
   assert_true(2==2, "Function error A", "Success A");
   assert_false(10!=10, "Function error 2", "Sucess 2");
   assert_equal_int(1, 1, "Function error 3", "Success 3");
   assert_not_equal_int(1, 2, "Function 4", "Success 4");
   assert_equal_double(sqrt(2), sq, "Error sqrt", "Success sqrt 3");
   assert_true(strlen(str1)==strlen(str2), "Error. String length does not match.", "Comparing \"str1\" with \"str2\"");
   assert_not_equal_byte((void *)str1, (void *)str2, strlen(str1), NULL, NULL, "Error. String does not match", "String NOT comparation success");
   assert_equal_string("bitcoin", "bitcoin", "Error comparing two strings", "Comparison word success");
   assert_equal_string_ignore_case("Bitcoin", "bitcoin", "Error comparing two strings 2", "Comparison word success 2");
   assert_not_equal_string("bitcoin", "Bitcoin", "Error comparing two strings B", "Comparison word success 3");
   assert_not_equal_string_ignore_case("Bitcoin", "Chocolate", "Error comparing two strings 3", "Comparison word success 4");
   assert_null(NULL, NULL, NULL, "Error assertion. Should be null", "Pointer is NULL. SUCCESS");
   assert_not_null((void *)"This is an pointer containing a string", NULL, NULL, "Pointer should be NOT null. Aborting", "Non null pointer success");
   assert_equal_byte(
      (void *)str1,
      (void *)str2,
      strlen(str1),
      cb_func_on_error,
      (void *)"Testing on error",
      "Error. String does not match",
      "String comparation success"
   );
   begin_tests();
   end_tests();
   return 0;
}
