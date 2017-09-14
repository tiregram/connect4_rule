#include <iostream>

#define BOOST_TEST_MODULE MyTest
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( my_test )
{
  BOOST_CHECK( 1 == 1 );
  BOOST_CHECK( 1 == 0 );
}

int main(int argc, char *argv[])
{
  std::cout << "hello" << "\n";
  return 0;
}
