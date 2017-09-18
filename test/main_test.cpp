#include "../include/Game.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Hello
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(Game_win_Test)
{
  Game g(RED);
  unsigned int s[] ={0,1,0,1,0,1,0};
  g.play(s);
  BOOST_CHECK_EQUAL(g.who_win(),RED);

  Game g2(GREEN);
  unsigned int s2[] ={0,1,0,1,0,1,0};
  g2.play(s2);
  BOOST_CHECK_EQUAL(g2.who_win(),GREEN);
}


BOOST_AUTO_TEST_CASE(Game_turn_Test)
{
  /////////////////////////////////////////////////////////////////////////////
  //                                red start                                //
  /////////////////////////////////////////////////////////////////////////////
  Game g(RED);
  BOOST_CHECK_EQUAL(g.turn(), RED);

  Move m0(1,g.turn(),g);
  BOOST_CHECK(m0.is_valid());
  g.apply(m0);
  BOOST_CHECK_EQUAL(g.turn(), GREEN);

  Move m1(1,g.turn(),g);
  BOOST_CHECK(m1.is_valid());
  g.apply(m1);
  BOOST_CHECK_EQUAL(g.turn(), RED);

  /////////////////////////////////////////////////////////////////////////////
  //                               green start                               //
  /////////////////////////////////////////////////////////////////////////////
  Game g1(GREEN);
  BOOST_CHECK_EQUAL(g.turn(),GREEN);


  Move m2(1,g.turn(),g);
  BOOST_CHECK(m2.is_valid());
  g.apply(m2);
  BOOST_CHECK_EQUAL(g.turn(), RED);


  Move m3(1,g.turn(),g);
  BOOST_CHECK(m3.is_valid());
  g.apply(m3);
  BOOST_CHECK_EQUAL(g.turn(), GREEN);

}

BOOST_AUTO_TEST_CASE(Game_init_Test)
{
  Game g_r1;
  Game g_r2;

  BOOST_CHECK_EQUAL(g_r1, g_r2);
  Game g_r3(RED);
  Game g_g4(GREEN);

  BOOST_CHECK(false==(g_r3 == g_g4));

  Game g0;
  Game g1 = Game();
  Game* g2 = new Game();
  //  Game g3 = g1;
  BOOST_CHECK_EQUAL(g0.turn(), 0);
  BOOST_CHECK_EQUAL(g0.is_valid(), OK);
  BOOST_CHECK_EQUAL(g0.is_over(), false);
  BOOST_CHECK_EQUAL(g1.is_valid(), OK);
  BOOST_CHECK_EQUAL(g2->is_valid(), OK);


  delete g2;
}

