#include <stdio.h>
#include <math.h>
#include <asserts.h>
#include <string.h>
#include <stdint.h>
/*
void on_add_assert(void *ctx)
{
   char msg[512];
   struct a *m=(struct a *)ctx;
   printf("\nAdding function %s ...", strcpy(msg, m->c));
}

void cb_func_on_error(void *ctx)
{
   printf("\nExiting on error test\n\t%s\n", (const char *)ctx);
}
*/

int main(int argc, char **argv)
{
   const double delta=0*1E-15;
   show_message_text();

   //assert_false(0, "Erro bool", "Sucesso bool");

   C_ASSERT_FALSE(0);

   C_ASSERT_TRUE(1, CTEST_SETTER(
      CTEST_TITLE("This is a title with value %d", 5),
      CTEST_INFO("This is an INFO title"),
      CTEST_WARN("This is a WARN message"),
      CTEST_ON_ERROR("This is a message when error occurs"),
      CTEST_ON_SUCCESS("This is a message when SUCCESS occurs")
   ));
/*
   C_ASSERT_TRUE(1, CTEST_SETTER(
      CTEST_TITLE("This is a title with value %d", 5),
      CTEST_INFO("This is an INFO title"),
"obj",
      //CTEST_WARN("This is a WARN message"),
//      CTEST_ON_ERROR("This is a message when error occurs"),
      NULL,
      CTEST_ON_SUCCESS("This is a message when SUCCESS occurs"),
NULL
   ));
*/

   C_ASSERT_EQUAL_INT(-1, -1);

   C_ASSERT_NOT_EQUAL_INT(11,12);

   C_ASSERT_EQUAL_LONG_INT(3, 3);
   C_ASSERT_NOT_EQUAL_LONG_INT(1, 0xf1);

   C_ASSERT_EQUAL_DOUBLE(2., 2.3-0.3, delta);

   C_ASSERT_NOT_EQUAL_DOUBLE(5.6, 2.3-0.3, delta);

   end_tests();

   return 0;
}
