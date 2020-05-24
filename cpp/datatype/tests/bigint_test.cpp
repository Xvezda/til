#include "xvzd_test.h"


namespace xvzd {

TEST(xvzd_bigint_test, bigint_ctor) {
  BigInt bi;
}

TEST(xvzd_bigint_test, bigint_default) {
  BigInt bi;
  EXPECT_TRUE(bi == "0");
}

TEST(xvzd_bigint_test, bigint_compare) {
  BigInt bia = "123";
  BigInt bib = "123";
  EXPECT_TRUE(bia.Compare(bib) == 0);

  bib = "124";
  EXPECT_TRUE(bia.Compare(bib) < 0);

  bib = "122";
  EXPECT_TRUE(bia.Compare(bib) > 0);
}

TEST(xvzd_bigint_test, bigint_add_no_carriage) {
  BigInt bia = "123";
  BigInt bib = "456";
  BigInt bic = bia + bib;

  LOGGER(bic);
  EXPECT_TRUE(bic == "579");
}

TEST(xvzd_bigint_test, bigint_add_carriage) {
  BigInt bia = "123";
  BigInt bib = "789";
  BigInt bic = bia + bib;

  LOGGER(bic);
  EXPECT_TRUE(bic == "912");
}

TEST(xvzd_bigint_test, bigint_add_diff_len) {
  BigInt bia = "123";
  BigInt bib = "987654";
  BigInt bic = bia + bib;

  LOGGER(bic);
  EXPECT_TRUE(bic == "987777");
}

TEST(xvzd_bigint_test, bigint_add_diff_len_with_carriage) {
  BigInt bia = "123";
  BigInt bib = "456789";
  BigInt bic = bia + bib;

  LOGGER(bic);
  EXPECT_TRUE(bic == "456912");

  bia = "999";
  bib = "99";
  bic = bia + bib;
  LOGGER(bic);
  EXPECT_TRUE(bic == "1098");
}


}  // namespace xvzd
