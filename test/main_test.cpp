#include "../include/Game.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Hello
#include <boost/test/unit_test.hpp>
#include <vector>

typedef std::vector<unsigned int> Vui;

BOOST_AUTO_TEST_CASE(Game_win_Test)
{
  // red win columns
  Game g(RED);
  Vui s = {0,1,0,1,0,1,0};
  g.play(s);
  BOOST_CHECK_EQUAL(g.who_win(),RED);

  // green win columns
  Game g2(GREEN);
  Vui s2 = {0,1,0,1,0,1,0};
  g2.play(s2);
  BOOST_CHECK_EQUAL(g2.who_win(),GREEN);

  // red row win
  Game g3(RED);

  Vui s3 = {0,0,1,1,2,2,3} ;
  g3.play(s3);
  BOOST_CHECK_EQUAL(g3.who_win(),RED);

  // green row win
  Game g4(GREEN);

  Vui s4 = {0,0,1,1,2,2,3};
  g4.play(s4);
  BOOST_CHECK_EQUAL(g4.who_win(),GREEN);

  // red diag1 win
  Game g5(RED);
  Vui s5 = {0,1,
                      1,2,
                      3,2,
                      2,3,
                      3,4,
                      3};
  g5.play(s5);
  BOOST_CHECK_EQUAL(g5.who_win(),RED);

  /// green diag1 win
  Game g6(GREEN);
  Vui s6 = {0,1,
                      1,2,
                      3,2,
                      2,3,
                      3,4,
                      3};
  g6.play(s6);

  BOOST_CHECK_EQUAL(g6.who_win(),GREEN);



  Game g7(GREEN);
  for (unsigned int i = 0; i < 6; i++) {
    for (unsigned int j = 0; j < 7; j++) {
      g7.play(j);
    }
  }

  BOOST_CHECK_EQUAL(g7.is_over(),true);

}


BOOST_AUTO_TEST_CASE(Game_turn_Test)
{
  /////////////////////////////////////////////////////////////////////////////
  //                                red start                                //
  /////////////////////////////////////////////////////////////////////////////
  Game g(RED);
  BOOST_CHECK_EQUAL(g.get_turn(), RED);

  Move m0(1,g.get_turn(),g);
  BOOST_CHECK_EQUAL(m0.is_valid(), OK);
  g.apply(m0);
  BOOST_CHECK_EQUAL(g.get_turn(), GREEN);

  Move m1(1,g.get_turn(),g);
  BOOST_CHECK_EQUAL(m1.is_valid(), OK);
  g.apply(m1);
  BOOST_CHECK_EQUAL(g.get_turn(), RED);

  /////////////////////////////////////////////////////////////////////////////
  //                               green start                               //
  /////////////////////////////////////////////////////////////////////////////
  Game g1(GREEN);	
  BOOST_CHECK_EQUAL(g1.get_turn(),GREEN);


  Move m2(1,g1.get_turn(),g1);
  BOOST_CHECK_EQUAL(m2.is_valid(), OK);
  g1.apply(m2);
  BOOST_CHECK_EQUAL(g1.get_turn(), RED);


  Move m3(1,g1.get_turn(),g1);
  BOOST_CHECK_EQUAL(m3.is_valid(), OK);
  g1.apply(m3);
  BOOST_CHECK_EQUAL(g1.get_turn(), GREEN);

}

BOOST_AUTO_TEST_CASE(Game_valid_Test)
{
  Game g(RED);
  g.set_turn(GREEN);
  BOOST_CHECK_EQUAL( g.is_valid(), TURN_PARITY);

  Game g1;
  BOOST_CHECK_EQUAL( g1.is_valid(), OK);
  g1.set(1,1,BS_RED);
  g1.set_turn(GREEN);
  BOOST_CHECK_EQUAL( g1.is_valid(),  GRAVITY );

/*  Game g2(RED);
  g2.set_turn(RED);
  BOOST_CHECK_EQUAL( g2.is_valid(), TURN_PARITY);
Change to OK?*/

  Game g3(RED);
  Vui  p3 = {0,0,0,0,0,0};
  g3.play(p3);
  int c = 0;
  BOOST_CHECK_EQUAL(g3.play(c),FULL_COLUMN);


  Game g5(RED);
  Vui  p5 = {0,0,0,0,0,0};
  g5.play(p5);
  Move m(0, g5.get_turn(),g5);
  BOOST_CHECK_EQUAL(g5.apply(m),FULL_COLUMN);

  Game g4(RED);
  g4.play(1);
  g4.set_turn(RED);
  BOOST_CHECK_EQUAL( g4.is_valid(), TURN_PARITY);


}

BOOST_AUTO_TEST_CASE(Game_post_prev_Test)
{
  Game g1;
  Game g2;
  BOOST_CHECK_EQUAL(g1.postr(g2), false);
  g1.play(1);
  BOOST_CHECK_EQUAL(g1.post(g2), false);
  BOOST_CHECK_EQUAL(g1.post(g2), true);





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
  BOOST_CHECK_EQUAL(g0.get_turn(), RED);
  BOOST_CHECK_EQUAL(g0.is_valid(), OK);
  BOOST_CHECK_EQUAL(g0.is_over(), false);
  BOOST_CHECK_EQUAL(g1.is_valid(), OK);
  BOOST_CHECK_EQUAL(g2->is_valid(), OK);

  delete g2;

}



