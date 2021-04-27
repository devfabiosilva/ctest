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
void cb_func_on_success(void *ctx)
{
   printf("\nSuccess ctx %p\n", ctx);

   if (ctx)
      printf("\nCTX VALUE %s\n", (char *)ctx);
}
void cb_func_on_error(void *ctx)
{
   printf("\nError ctx %p\n", ctx);

   if (ctx)
      printf("\nCTX VALUE %s\n", (char *)ctx);
}
int main(int argc, char **argv)
{
   const double delta=1E-15;
   char vec1[] = {1, 2, 3, 4}, vec2[] = {1, 2, 3, 4}, vec3[] = {2, 1, 3, 4};
   const char *name1="Nikola Tesla", *name2="Nikola Tesla", *name3="nikola tesla";

   C_ASSERT_FALSE(1, CTEST_SETTER(CTEST_INFO("This is an INFO title"), CTEST_ON_ERROR_CB(cb_func_on_error, "jgg"), CTEST_ON_SUCCESS_CB(cb_func_on_success, "hhj")))

   C_ASSERT_FALSE(0)

   C_ASSERT_TRUE(1, CTEST_SETTER(
      CTEST_TITLE("This is a title with value %d", 5),
      CTEST_INFO("This is an INFO title"),
      CTEST_WARN("This is a WARN message"),
      CTEST_ON_ERROR("This is a message when error occurs"),
      CTEST_ON_SUCCESS("This is a message when SUCCESS occurs")
   ))

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

   C_ASSERT_EQUAL_INT(-1, -1)

   C_ASSERT_NOT_EQUAL_INT(11,12)

   C_ASSERT_EQUAL_LONG_INT(3, 3)
   C_ASSERT_NOT_EQUAL_LONG_INT(1, 0xf1)

   C_ASSERT_EQUAL_DOUBLE(2., 2.3-0.3, delta)

   C_ASSERT_NOT_EQUAL_DOUBLE(5.6, 2.3-0.3, delta)

   C_ASSERT_EQUAL_BYTE(vec1, vec2, sizeof(vec1))

   C_ASSERT_NOT_EQUAL_BYTE(vec1, vec3, sizeof(vec1), CTEST_SETTER(CTEST_INFO("Testando esse vetor"), CTEST_WARN("ALERTA: Ele deve ser diferente!!!")))

   C_ASSERT_NULL(NULL)

   C_ASSERT_NOT_NULL(vec3)

   C_ASSERT_EQUAL_STRING(name1, name2)

   C_ASSERT_EQUAL_STRING_IGNORE_CASE(name3, name2)

   C_ASSERT_NOT_EQUAL_STRING(name1, name3)

   C_ASSERT_NOT_EQUAL_STRING_IGNORE_CASE(name3, "Albert Einstein")

   end_tests();

   show_message_text();

   return 0;
}
