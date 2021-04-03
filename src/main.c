#include "asserts.h"
#include "stdio.h"

int main(int argc, char **argv)
{
   assert_true(2==2, "Function error A", "Success A");
   assert_true(10!=11, "Function error 2", "Sucess 2");
   assert_equal_int(1, 1, "Function error 3", "Success 3");
   begin_tests();
   end_tests();
   return 0;
}
