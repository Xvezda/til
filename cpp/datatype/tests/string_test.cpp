#include "xvzd_test.h"


namespace xvzd {

TEST(xvzd_string_test, string_ctor) {
  String str("hello");
  LOGGER(str);

  String sc('c');
  LOGGER(sc);

  String divider('-', 10);
  LOGGER(divider.Concat(String('+', 10)));
  LOGGER(divider.Append(String('-', 20)));
}

TEST(xvzd_string_test, string_operator) {
  String s1("abc");
  String s2(s1);

  String s3 = (s2 + "def") * 2;

  LOGGER(s3);
  EXPECT_TRUE(s3 == "abcdefabcdef");
}

TEST(xvzd_string_test, string_slice) {
  String sentence = "The quick brown fox jumps over the lazy dog";
  EXPECT_TRUE(sentence.Slice(4, -4) == "quick brown fox jumps over the lazy");
}

TEST(xvzd_string_test, string_find) {
  String sentence = "The quick brown fox jumps over the lazy dog";
  EXPECT_TRUE(sentence.Find("fox") == 16);
}

TEST(xvzd_string_test, string_split) {
  Array<String> sa = String("foo|bar|baz").Split("|");
  EXPECT_TRUE(sa.ToString() == "[foo, bar, baz]");
}

TEST(xvzd_string_test, string_subst) {
  EXPECT_TRUE(String("hello").Substr(-2, 2) == "lo");
  EXPECT_TRUE(String("hello").Substring(3, 1) == "el");
  EXPECT_TRUE(String("hello").Substring(-2, 3) == "hel");
}

TEST(xvzd_string_test, string_padding) {
  String s1("hello");
  String s2("world");

  EXPECT_TRUE(s1.Lpad(10).Rpad(5) + s2 == "          hello     world");
}

TEST(xvzd_string_test, string_length) {
  String s("");
  EXPECT_TRUE(s.Length() == 0);
}

TEST(xvzd_string_test, string_reverse) {
  String s("hello");
  EXPECT_TRUE(s.Reverse() == "olleh");
}

}  // namespace xvzd
