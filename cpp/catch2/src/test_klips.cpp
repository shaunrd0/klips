#define CATCH_CONFIG_MAIN

#include <iostream>

#include "catch2/catch_all.hpp"

#include "klips.hpp"
#include "type_name.hpp"

#define TT() std::cout << "T = " << type_name<TestType>() << std::endl;
#define TD(x)                                                                  \
  std::cout << type_name<decltype(x)>() << " " << #x << " = " << x << std::endl;
#define T(x) std::cout << "T = " << type_name<x>() << std::endl;

TEST_CASE("factorials are computed", "[factorial]") {
  REQUIRE(factorial(1) == 1);
  REQUIRE(factorial(2) == 2);
  REQUIRE(factorial(3) == 6);
  REQUIRE(factorial(10) == 3628800);
}

TEST_CASE("Generators") {
  auto i = GENERATE(1, 3, 5);
  TD(i);
}

TEST_CASE("Generators 2") {
  auto i = GENERATE(1, 2);
  SECTION("one") {
    auto j = GENERATE(-3, -2);
    REQUIRE(j < i);
    std::cout << "i = " << i << "; j = " << j << std::endl;
  }
  SECTION("two") {
    auto k = GENERATE(4, 5, 6);
    REQUIRE(i != k);
    std::cout << "i = " << i << "; k = " << k << std::endl;
  }
}

TEST_CASE("Complex mix of sections and generates") {
  auto i = GENERATE(1, 2);
  SECTION("A") {
    std::cout << "i = " << i << "; A passed" << std::endl;
    SUCCEED("A");
  }
  std::cout << "left A\n";
  auto j = GENERATE(3, 4);
  std::cout << "i = " << i << "; j = " << j << std::endl;
  SECTION("B") {
    std::cout << "i = " << i << "; j = " << j << "; B passed;" << std::endl;
    SUCCEED("B");
  }
  auto k = GENERATE(5, 6);
  std::cout << "i = " << i << "; k = " << k << std::endl;
  SUCCEED();
}

TEST_CASE("Test generaators 3", "[test]") { GENERATE(values({1, 2})); }

TEMPLATE_TEST_CASE("Testing template tests", "[test][template]", int8_t,
                   int16_t, int32_t, int64_t) {
  TT();
}

template <typename T> struct Foo {
  size_t size() { return 0; }
};

template <typename T> struct Test {
  T test() {
    T x;
    return x;
  }
};

TEMPLATE_PRODUCT_TEST_CASE("A Template product test case",
                           "[template][product]", (std::vector, Test),
                           (int, float)) {
  TT();
}

TEMPLATE_PRODUCT_TEST_CASE("Product with differing arities",
                           "[template][product]", std::tuple,
                           (int, (int, double), (int, double, float))) {
  TT();
}

using types = std::tuple<int8_t, int16_t, int32_t, int64_t>;

TEMPLATE_LIST_TEST_CASE("Testing template list tests", "[test][template][list]",
                        types) {
  TT();
}

TEMPLATE_TEST_CASE_SIG(
    "TemplateTestSig: arrays can be created from NTTP arguments",
    "[vector][template][nttp]", ((typename T, int V), T, V), (int, 5),
    (float, 4), (std::string, 15), ((std::tuple<int, float>), 6)) {
  T(T);
  std::cout << "V = " << V;
  std::array<T, V> v;
  REQUIRE(v.size() > 1);
}

template <typename T, size_t S> struct Bar {
  size_t size() { return S; }
};

TEMPLATE_PRODUCT_TEST_CASE_SIG(
    "A Template product test case with array signature",
    "[template][product][nttp]", ((typename T, size_t S), T, S),
    (std::array, Bar), ((int, 9), (float, 42))) {
  TT();
  TestType x;
  REQUIRE(x.size() > 0);
}

template <typename T> struct test_config_get {
  template <bool must_find> void run() {
    //    Config c{};
    //    std::string key{"the_key"};
    //    std::string value{"the_value"};
    //    c.set(key, value);
    if constexpr (must_find) {
      std::cout << "Test 1 ran";
    } else {
      std::cout << "Test 2 ran";
    }
  }
};
template <> template <bool must_find> void test_config_get<std::string>::run() {
  if constexpr (must_find) {
    std::cout << "Test 1 ran for strings";
  } else {
    std::cout << "Test 2 ran for strings";
  }
}

TEMPLATE_PRODUCT_TEST_CASE("Test", "[test]", test_config_get,
                           (int, std::string)) {
  TT();
  // TestType t;
  test_config_get<int> s;
  s.template run<true>();
  //  TestType t;
  //  t.run<true>();
}
