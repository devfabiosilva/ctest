#include <stdio.h>
#include <math.h>
#include <asserts.h>
#include <string.h>
#include <stdint.h>
/*
struct a {
   uint32_t b;
   const char *c;
};

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

void *varg_msg=NULL;

void cb_func_on_error(void *ctx)
{
   printf("\nExiting on error test (%p)\n", ctx);
}


int main(int argc, char **argv)
{
   void *vargs;
   char *msg;
   int err;

   on_abort(cb_func_on_error);
   err=load_test_vargs_for_test(&vargs, CTEST_SETTER(NULL, "Wrong Object"));
   printf("\nERR=%d\n", err);
   assert_equal_int(14, err, "Error. Value are not equal", "Error success");
   assert_null(vargs, NULL, NULL, "Expected: \"vargs == NULL\"", "vargs=NULL (Success)");
   err=load_test_vargs_for_test(&vargs, CTEST_SETTER(
      CTEST_TITLE("This is a title with value %d", err+5)
   ));
   assert_equal_int(0, err, "Error. Expected success", "Error success");
   assert_not_null(vargs, NULL, NULL, "Expected not NULL, but NULL found", "vargs address allocated");
   msg=ctest_setter_has_title(vargs);
   assert_not_null(msg, NULL, NULL, "Error. msg pointer should be NOT NULL", "msg pointer success");
   printf("Message passed %s\n", msg);

   msg=ctest_setter_has_info(vargs);

   assert_null(msg, NULL, NULL, "Error. Info should be not set and return NULL", "INFO NULL pointer expected success");

   err=free_vargs_for_test(vargs);
   assert_equal_int(0, err, "Error found in free_vargs", "Error free_vargs success");

   err=load_test_vargs_for_test(&vargs, CTEST_SETTER(
      CTEST_TITLE("This is a title with value %d", err+5),
      CTEST_INFO("This is an INFO title"),
      CTEST_WARN("This is a WARN message"),
      CTEST_ON_ERROR("This is a message when error occurs"),
      CTEST_ON_SUCCESS("This is a message when error occurs")
   ));

   assert_equal_int(0, err, "Second step error. Expected success", "Sencond step error success");

   msg=ctest_setter_has_info(vargs);
   assert_not_null(msg, NULL, NULL, "Second step INFO error. Message should be NOT NULL", "Second step INFO success");

   printf("\nINFO text message %s\n", msg);

   msg=ctest_setter_has_warn(vargs);
   assert_not_null(msg, NULL, NULL, "Second step WARN error. Message should be NOT NULL", "Second step WARN success");

   printf("\nWARN text message %s\n", msg);

   msg=ctest_setter_has_onerror(vargs);
   assert_not_null(msg, NULL, NULL, "Second step ON ERROR error. Message should be NOT NULL", "Second step ON ERROR success");

   printf("\nON ERROR text message %s\n", msg);

   msg=ctest_setter_has_onsuccess(vargs);
   assert_not_null(msg, NULL, NULL, "Second step ON SUCCESS error. Message should be NOT NULL", "Second step ON SUCCESS success");

   printf("\nON SUCCESS text message %s\n", msg);

   err=free_vargs_for_test(vargs);
   assert_equal_int(0, err, "Second step error found in free_vargs", "Second step error free_vargs success");

   show_message_text();

   end_tests();


//CTEST_SETTER(NULL, "Wrong Object");
/*
   varg_msg=CTEST_TITLE("shghg");
   assert_not_null(varg_msg, NULL, NULL, "Error. Expected not null", "varg_msg != NULL -> Success");

   assert_null(CTEST_SETTER(varg_msg, NULL, "NULL"), NULL, NULL, "Error. Expected = NULL", "CTEST_SETTER: Success");
   assert_true(CTEST_SETTER(NULL, VA_END_SIGNATURE)==(void *)VA_END_SIGNATURE, "Error. Expected = NULL", "CTEST_SETTER: Success");
*/
   return 0;
/*
   double delta=1E-15;
   const char *str1="This is an simple string A";
   const char *str2="This is an simple string B";

   assert_true(2==2, "Function error A", "Success A");
   assert_false(10!=10, "Function error 2", "Sucess 2");
   rm_on_add_test();
   on_add_test(on_add_assert);
   assert_equal_int(1, 1, "Function error 3", "Success 3");
   assert_not_equal_int(1, 2, "Function 4", "Success 4");
   assert_equal_double(2, 2.3-0.3, delta, "Error sub", "Success sub");
   rm_on_add_test();
   assert_not_equal_double(2, 2.3-0.29999999999999, delta, "Error sub", "Success sub");
   assert_true(strlen(str1)==strlen(str2), "Error. String length does not match.", "Comparing \"str1\" with \"str2\"");
   rm_on_add_test();
   assert_not_equal_byte((void *)str1, (void *)str2, strlen(str1), NULL, NULL, "Error. String does not match", "String NOT comparation success");
   assert_equal_string("bitcoin", "bitcoin", "Error comparing two strings", "Comparison word success");
   on_add_test(on_add_assert);
   assert_equal_string_ignore_case("Bitcoin", "bitcoin", "Error comparing two strings 2", "Comparison word success 2");
   assert_not_equal_string("bitcoin", "Bitcoin", "Error comparing two strings B", "Comparison word success 3");
on_add_test(on_add_assert);
   assert_not_equal_string_ignore_case("Bitcoin", "Chocolate", "Error comparing two strings 3", "Comparison word success 4");
   assert_null(NULL, NULL, NULL, "Error assertion. Should be null", "Pointer is NULL. SUCCESS");
   assert_not_null((void *)"This is an pointer containing a string", NULL, NULL, "Pointer should be NOT null. Aborting", "Non null pointer success");
   assert_not_equal_byte(
      (void *)str1,
      (void *)str2,
      strlen(str1),
      cb_func_on_error,
      (void *)"Testing on error",
      "Error. String does not match",
      "String comparation success"
   );
//   begin_tests();
   end_tests();
   return 0;
*/
}
