#include <simplecpp>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
using namespace simplecpp;

//movingObject.h
#ifndef _MOVINGOBJECT_INCLUDED_
#define _MOVINGOBJECT_INCLUDED_

#include <simplecpp>
#include <vector>
#include <composite.h>
#include <sprite.h>
#include <fstream>

using namespace simplecpp;

class MovingObject : public Sprite
{
  vector<Sprite *> parts;
  double vx, vy;
  double ax, ay;
  bool paused;
  void initMO(double argvx, double argvy, double argax, double argay, bool argpaused = true)
  {
    vx = argvx;
    vy = argvy;
    ax = argax;
    ay = argay;
    paused = argpaused;
  }

public:
  MovingObject(double argvx, double argvy, double argax, double argay, bool argpaused = true)
      : Sprite()
  {
    initMO(argvx, argvy, argax, argay, argpaused);
  }
  MovingObject(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : Sprite()
  {
    double angle_rad = angle_deg * PI / 180.0;
    double argvx = speed * cos(angle_rad);
    double argvy = -speed * sin(angle_rad);
    initMO(argvx, argvy, argax, argay, argpaused);
  }
  void set_vx(double argvx) { vx = argvx; }
  void set_vy(double argvy) { vy = argvy; }
  void set_ax(double argax) { ax = argax; }
  void set_ay(double argay) { ay = argay; }
  double getXPos();
  double getYPos();
  void reset_all(double argx, double argy, double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta);

  void pause() { paused = true; }
  void unpause() { paused = false; }
  bool isPaused() { return paused; }

  void addPart(Sprite *p)
  {
    parts.push_back(p);
  }
  void nextStep(double t);
  void getAttachedTo(MovingObject *m);
};

#endif

//MovingObject.cpp

void MovingObject::nextStep(double t)
{
  if (paused)
  {
    return;
  }
  //cerr << "x=" << getXPos() << ",y=" << getYPos() << endl;
  //cerr << "vx=" << vx << ",vy=" << vy << endl;
  //cerr << "ax=" << ax << ",ay=" << ay << endl;

  for (size_t i = 0; i < parts.size(); i++)
  {
    parts[i]->move(vx * t, vy * t);
  }
  vx += ax * t;
  vy += ay * t;
} // End MovingObject::nextStep()

double MovingObject::getXPos()
{
  return (parts.size() > 0) ? parts[0]->getX() : -1;
}

double MovingObject::getYPos()
{
  return (parts.size() > 0) ? parts[0]->getY() : -1;
}

void MovingObject::reset_all(double argx, double argy, double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta)
{
  for (size_t i = 0; i < parts.size(); i++)
  {
    parts[i]->moveTo(argx, argy);
  }
  double angle_rad = angle_deg * PI / 180.0;
  double argvx = speed * cos(angle_rad);
  double argvy = -speed * sin(angle_rad);
  vx = argvx;
  vy = argvy;
  ax = argax;
  ay = argay;
  paused = argpaused;
} // End MovingObject::reset_all()

void MovingObject::getAttachedTo(MovingObject *m)
{
  double xpos = m->getXPos();
  double ypos = m->getYPos();
  for (size_t i = 0; i < parts.size(); i++)
  {
    parts[i]->moveTo(xpos, ypos);
  }
  initMO(m->vx, m->vy, m->ax, m->ay, m->paused);
}
//bomb.h
#ifndef __BOMB_H__
#define __BOMB_H__
class Bomb : public MovingObject
{
  double bomb_start_x;
  double bomb_start_y;
  double release_speed;
  double release_angle_deg;
  double bomb_ax;
  double bomb_ay;

  // Moving parts
  Circle bomb_circle;

public:
  Bomb(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta)
  {
    release_speed = speed;
    release_angle_deg = angle_deg;
    bomb_ax = argax;
    bomb_ay = argay;
    initBomb();
  }

  void initBomb();
  void resetBomb();
  void changeColor();
  void changePos();
}; //End Class bomb
#endif

//coin.h
#ifndef __COIN_H__
#define __COIN_H__

class Coin : public MovingObject
{
  double coin_start_x;
  double coin_start_y;
  double release_speed;
  double release_angle_deg;
  double coin_ax;
  double coin_ay;

  // Moving parts
  Circle coin_circle;

public:
  Coin(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta)
  {
    release_speed = speed;
    release_angle_deg = angle_deg;
    coin_ax = argax;
    coin_ay = argay;
    initCoin();
  }

  void initCoin();
  void resetCoin();

}; // End class Coin

#endif
//lasso.h
#ifndef __LASSO_H__
#define __LASSO_H__


#define WINDOW_X 800
#define WINDOW_Y 600

#define STEP_TIME 0.05

#define PLAY_X_START 100
#define PLAY_Y_START 0
#define PLAY_X_WIDTH (WINDOW_X - PLAY_X_START)
#define PLAY_Y_HEIGHT (WINDOW_Y - 100)

#define LASSO_X_OFFSET 100
#define LASSO_Y_HEIGHT 100
#define LASSO_BAND_LENGTH LASSO_X_OFFSET
#define LASSO_THICKNESS 5

#define COIN_GAP 1
#define BOMB_GAP 1

#define RELEASE_ANGLE_STEP_DEG 5
#define MIN_RELEASE_ANGLE_DEG 0
#define MAX_RELEASE_ANGLE_DEG (360 - RELEASE_ANGLE_STEP_DEG)
#define INIT_RELEASE_ANGLE_DEG 45

#define RELEASE_SPEED_STEP 20
#define MIN_RELEASE_SPEED 0
#define MAX_RELEASE_SPEED 200
#define INIT_RELEASE_SPEED 100

#define COIN_SPEED 120
#define COIN_ANGLE_DEG 90

#define BOMB_SPEED 120
#define BOMB_ANGLE_DEG 90

#define LASSO_G 30
#define COIN_G 30
#define BOMB_G 30

#define LASSO_SIZE 10
#define LASSO_RADIUS 50
#define COIN_SIZE 5
#define BOMB_SIZE 5
#define BOMB_SIZE_LEVEL_2 7
#define COIN_SIZE_LEVEL_2 4

class Lasso : public MovingObject
{
  double lasso_start_x;
  double lasso_start_y;
  double release_speed;
  double release_angle_deg;
  double lasso_ax;
  double lasso_ay;
  double LASSO_RAD;
  // Moving parts
  Circle lasso_circle;
  Circle lasso_loop;

  // Non-moving parts
  Line lasso_line;
  Line lasso_band;

  // State info
  bool lasso_looped;
  Coin *the_coin;
  Bomb *the_bomb;
  Bomb *the_bomb3;
  int num_coins;
  int num_bombs;

  bool magnetUnlocked = false;

  void initLasso();

public:
  Lasso(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta)
  {
    release_speed = speed;
    release_angle_deg = angle_deg;
    lasso_ax = argax;
    lasso_ay = argay;
    initLasso();
  }

  void draw_lasso_band();
  void yank();
  void loopit();
  void addAngle(double angle_deg);
  void addSpeed(double speed);

  void nextStep(double t);
  void check_for_coin(Coin *coin);
  void check_for_bomb(Bomb *bomb);
  int getNumCoins() { return num_coins; }
  int getNumBombs() { return num_bombs; }

  void magnet();
  void disableMagnet();
  void COINZERO();
}; // End class Lasso

#endif
//bomb.h
void Bomb::initBomb()
{
  bomb_start_x = (PLAY_X_START + WINDOW_X - 250) / 2;
  bomb_start_y = PLAY_Y_HEIGHT;
  bomb_circle.reset(bomb_start_x, bomb_start_y, BOMB_SIZE);
  bomb_circle.setColor(COLOR("red"));
  bomb_circle.setFill(true);
  addPart(&bomb_circle);
}

void Bomb::resetBomb()
{
  double bomb_speed = BOMB_SPEED;
  double bomb_angle_deg = BOMB_ANGLE_DEG;
  bomb_ax = 0;
  bomb_ay = BOMB_G;
  bool paused = true, rtheta = true;
  reset_all(bomb_start_x, bomb_start_y, bomb_speed, bomb_angle_deg, bomb_ax, bomb_ay, paused, rtheta);
}

void Bomb::changeColor()
{
  bomb_circle.setColor(COLOR("blue"));
  bomb_circle.setFill(true);
  return;
}

void Bomb::changePos()
{
  bomb_start_x = bomb_start_x + 50;
  return;
}
//coin.h

void Coin::initCoin()
{
  coin_start_x = (PLAY_X_START + WINDOW_X) / 2;
  coin_start_y = PLAY_Y_HEIGHT;
  coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);
  coin_circle.setColor(COLOR("blue"));
  coin_circle.setFill(1);
  addPart(&coin_circle);
}

void Coin::resetCoin()
{
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG;
  coin_ax = 0;
  coin_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(coin_start_x, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
}

//lasso.cpp

void Lasso::draw_lasso_band()
{
  double len = (release_speed / MAX_RELEASE_SPEED) * LASSO_BAND_LENGTH;
  double arad = release_angle_deg * PI / 180.0;
  double xlen = len * cos(arad);
  double ylen = len * sin(arad);
  lasso_band.reset(lasso_start_x, lasso_start_y, (lasso_start_x - xlen), (lasso_start_y + ylen));
  lasso_band.setThickness(LASSO_THICKNESS);
} // End Lasso::draw_lasso_band()

void Lasso::initLasso()
{
  lasso_start_x = (PLAY_X_START + LASSO_X_OFFSET);
  lasso_start_y = (PLAY_Y_HEIGHT - LASSO_Y_HEIGHT);
  lasso_circle.reset(lasso_start_x, lasso_start_y, LASSO_SIZE);
  lasso_circle.setColor(COLOR("red"));
  lasso_circle.setFill(true);
  lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE / 2);
  lasso_loop.setColor(COLOR("green"));
  lasso_loop.setFill(true);
  addPart(&lasso_circle);
  addPart(&lasso_loop);
  lasso_looped = false;
  the_coin = NULL;
  the_bomb = NULL;
  the_bomb3 = NULL;
  num_coins = 0;
  num_bombs = 0;
  LASSO_RAD = LASSO_RADIUS;
  lasso_line.reset(lasso_start_x, lasso_start_y, lasso_start_x, lasso_start_y);
  lasso_line.setColor(COLOR("yellow"));

  lasso_band.setColor(COLOR("blue"));
  draw_lasso_band();

} // End Lasso::initLasso()
void Lasso::COINZERO() //Ensures that the number of coins get zeroed at beginning of each level. Do not apply on lives-- else gmae will be too hard
{
  num_coins = 0;
  num_bombs = 0;
  return;
}
void Lasso::yank()
{
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
  lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE / 2);
  lasso_loop.setFill(true);
  lasso_looped = false;

  if (the_coin != NULL)
  {
    num_coins++;
    the_coin->resetCoin();
    the_coin = NULL;
  }
  if (the_bomb != NULL)
  {
    num_coins--;
    the_bomb->resetBomb();
    the_bomb = NULL;
  }
  if (the_bomb3 != NULL) //BOMB FOR LEVEL-3 doesn't matter if defined at other levels or not, this part of code will remain dead for 2 levels
  {
    num_coins--;
    the_bomb3->resetBomb();
    the_bomb3 = NULL;
  }
  else
    num_coins += 0;

} // End Lasso::yank()

void Lasso::loopit()
{
  if (lasso_looped)
  {
    return;
  } // Already looped
  lasso_loop.reset(getXPos(), getYPos(), LASSO_RAD);
  lasso_loop.setFill(false);
  lasso_looped = true;
} // End Lasso::loopit()

void Lasso::addAngle(double angle_deg)
{
  release_angle_deg += angle_deg;
  if (release_angle_deg < MIN_RELEASE_ANGLE_DEG)
  {
    release_angle_deg = MIN_RELEASE_ANGLE_DEG;
  }
  if (release_angle_deg > MAX_RELEASE_ANGLE_DEG)
  {
    release_angle_deg = MAX_RELEASE_ANGLE_DEG;
  }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
} // End Lasso::addAngle()

void Lasso::addSpeed(double speed)
{
  release_speed += speed;
  if (release_speed < MIN_RELEASE_SPEED)
  {
    release_speed = MIN_RELEASE_SPEED;
  }
  if (release_speed > MAX_RELEASE_SPEED)
  {
    release_speed = MAX_RELEASE_SPEED;
  }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
} // End Lasso::addSpeed()

void Lasso::nextStep(double stepTime)
{
  draw_lasso_band();
  MovingObject::nextStep(stepTime);
  if (getYPos() > PLAY_Y_HEIGHT)
  {
    yank();
  }
  lasso_line.reset(lasso_start_x, lasso_start_y, getXPos(), getYPos());
} // End Lasso::nextStep()

void Lasso::check_for_coin(Coin *coinPtr)
{
  double lasso_x = getXPos();
  double lasso_y = getYPos();
  double coin_x = coinPtr->getXPos();
  double coin_y = coinPtr->getYPos();
  double xdiff = (lasso_x - coin_x);
  double ydiff = (lasso_y - coin_y);
  double distance = sqrt((xdiff * xdiff) + (ydiff * ydiff));
  if (distance <= LASSO_RAD)
  {
    the_coin = coinPtr;
    the_coin->getAttachedTo(this);
  }
}
void Lasso::check_for_bomb(Bomb *bombPtr)
{
  double lasso_x = getXPos();
  double lasso_y = getYPos();
  double bomb_x = bombPtr->getXPos();
  double bomb_y = bombPtr->getYPos();
  double xdiff = (lasso_x - bomb_x);
  double ydiff = (lasso_y - bomb_y);
  double distance = sqrt((xdiff * xdiff) + (ydiff * ydiff));
  if (distance <= LASSO_RAD)
  {
    the_bomb = bombPtr;
    the_bomb->getAttachedTo(this);
  }
}

//Function to make the lasso magnetized
void Lasso::magnet()
{
  LASSO_RAD = 2 * LASSO_RADIUS;
  return;
}

//De-magnetizing Lasso
void Lasso::disableMagnet()
{
  LASSO_RAD = LASSO_RADIUS;
  return;
}
// End Lasso::check_for_coin()

//Function that allows new users to access key mapping whenever equired in the game
void help()
{

  Text h11(WINDOW_X / 2, 170, "KEY-MAPPING");
  Text h12(WINDOW_X / 2, 200, "]: Increase the angle");
  Text h13(WINDOW_X / 2, 220, "[: Decrease the angle");
  Text h14(WINDOW_X / 2, 240, "=: Increase speed");
  Text h15(WINDOW_X / 2, 260, "-: Decrease speed");
  Text h16(WINDOW_X / 2, 280, "l: Loop the lasso");
  Text h17(WINDOW_X / 2, 300, "y: Yank the lasso");
  Text h18(WINDOW_X / 2, 320, "q: Exit the game");
  Text h19(WINDOW_X / 2, 340, "h: Open this page in the middle of the game");
  Text h110(WINDOW_X / 2, 370, "PRESS C AND CLICK ANYWHERE TO CONTINUE");
  getClick();
  return;
}

//Repetitive part of the code
void repeatf(char c, Lasso &lasso, Coin &coin, Bomb &bomb)
{
  switch (c)
  {
  case 't':
    lasso.unpause();
    break;
  case 'y':
    lasso.yank();
    break;
  case 'l':
    lasso.loopit();
    lasso.check_for_coin(&coin);
    lasso.check_for_bomb(&bomb);
    wait(STEP_TIME * 5);
    break;
  case '[':
    if (lasso.isPaused())
    {
      lasso.addAngle(-RELEASE_ANGLE_STEP_DEG);
    }
    break;
  case ']':
    if (lasso.isPaused())
    {
      lasso.addAngle(+RELEASE_ANGLE_STEP_DEG);
    }
    break;
  case '-':
    if (lasso.isPaused())
    {
      lasso.addSpeed(-RELEASE_SPEED_STEP);
    }
    break;
  case '=':
    if (lasso.isPaused())
    {
      lasso.addSpeed(+RELEASE_SPEED_STEP);
    }
    break;
  case 'h':
  {
    help();
  }
  break;
  case 'q':
    exit(0);
  default:
    break;
  }
  return;
}

//Repetitive part shortened with function
void unpauseResetNextStep(Lasso &lasso, Coin &coin, Bomb &bomb, float &currTime, float &stepTime, double &last_coin_jump_end, double &last_bomb_jump_end)
{

  lasso.nextStep(stepTime);

  coin.nextStep(stepTime);

  bomb.nextStep(stepTime);

  if (coin.isPaused())
  {
    if ((currTime - last_coin_jump_end) >= COIN_GAP)
    {
      coin.unpause();
    }
  }
  if (bomb.isPaused())
  {
    if ((currTime - last_bomb_jump_end) >= BOMB_GAP)
    {
      bomb.unpause();
    }
  }
  if (coin.getYPos() > PLAY_Y_HEIGHT)
  {
    coin.resetCoin();
    last_coin_jump_end = currTime;
  }
  if (bomb.getYPos() > PLAY_Y_HEIGHT)
  {
    bomb.resetBomb();
    last_bomb_jump_end = currTime;
  }
  return;
}

//Countdown at beginning of a new level
void STARTERTIME()
{
  for (int i = 3; i >= 0; i--)
  {
    Text StartTime(WINDOW_X / 2 + 40, WINDOW_Y / 2, i);
    wait(1);
  }
  return;
}

//Life lost warning as well as updation on screen
void Warning(int lives, float &t)
{
  if (lives > 0)
  {
    Text WARNING(WINDOW_X / 2, WINDOW_Y / 2 - 20, "Time's Up! You Lost a Life! Using new life in ");
    STARTERTIME();
    WARNING.hide();
    t = 30;
    return;
  }
}

//Message notifying player that he has proceeded to the next level
void nextLevelmsg()
{
  Text Wc(WINDOW_X / 2 - 5, WINDOW_Y / 2, "Next Level Beginning in");
  for (int i = 1; i <= 4; i++)
  {
    Text Wc2(WINDOW_X / 2 + 80, WINDOW_Y / 2, 4 - i);
    wait(1);
    Wc2.hide();
  }
  Wc.hide();
  Text START(WINDOW_X / 2, WINDOW_Y / 2, "START!");
  wait(0.7);
  return;
}

//Call when the magnet is supposed to be unlocked
void magnetUnlocked(Lasso &lasso)
{
  Text magnet(WINDOW_X / 2, WINDOW_Y / 2, "Power-Up!");
  Text magnet2(WINDOW_X / 2, WINDOW_Y / 2 + 20, "You Unlocked a magnet. Now catch coins for 15 seconds for longer distances.");
  lasso.magnet();
  wait(1.5);
  magnet.hide();
  magnet2.hide();
  return;
}

//Call when game ends. Stores name, level completed and lives left in separate lines. File can be accessed manually from the folder.
void leaderboard(int lives, int level)
{
  char nameStr[100];

  sprintf(nameStr, "Enter your name: %s", " ");
  Text nameInput(WINDOW_X / 2, WINDOW_Y / 2 + 60, nameStr);
  Text instruct(WINDOW_X / 2, WINDOW_Y / 2 + 30, "Press ] to exit");
  nameInput.setMessage(nameStr);
  char c;
  for (int i = 16; c != '\n'; i++)
  {

    XEvent e;
    nextEvent(e);
    if (keyPressEvent(e))
    {
      c = charFromEvent(e);

      if (c == ']')
        break;
      nameStr[i] = c;
      nameStr[i + 1] = '\0';
      nameInput.setMessage(nameStr);
    }
  }
  ofstream outfile("Leaderboard.txt");
  outfile << "NAME:" << nameStr + 16 << ' ' << "LIVES LEFT:" << lives << ' ' << "COMPLETED THE LEVEL:" << level << endl;
  exit(0);
  return;
}

//MAIN CODE

main_program
{
  //OPENING INTERFACE: A LOADING SCREEN
  initCanvas("Lasso", WINDOW_X, WINDOW_Y);
  Text top(WINDOW_X / 2, 75, "CoinMaster");
  Text Welcome(WINDOW_X / 2, WINDOW_Y / 2, "LOADING....");
  Circle c1(WINDOW_X / 2, WINDOW_Y / 2, 60);
  Turtle t1;
  t1.show();
  t1.penUp();
  t1.forward(60);
  t1.right(90);
  Text Bottom(WINDOW_X / 2, WINDOW_Y - 100, "Copyright \xa9 2020");
  Text Bottom2(WINDOW_X / 2, WINDOW_Y - 70, "CoinMaster Version V_1.28");

  repeat(1)
  {
    Text Mid(WINDOW_X / 2, WINDOW_Y / 2 + 100, "Developed by Pulkit Paliwal<20D100021>");
    repeat(90)
    {
      t1.forward(4.2);
      t1.right(4);
    }
  }
  c1.hide();
  t1.hide();
  Welcome.hide();

  //HOME SCREEN: Free-Play, HELP, QUIT

  Rectangle R1(WINDOW_X / 2, WINDOW_Y / 2 - 50, 100, 40);
  Text FreePlay(WINDOW_X / 2, WINDOW_Y / 2 - 50, "Free-Play");
  Rectangle R2(WINDOW_X / 2, WINDOW_Y / 2, 100, 40);
  Text Help(WINDOW_X / 2, WINDOW_Y / 2, "Help");
  Rectangle R3(WINDOW_X / 2, WINDOW_Y / 2 + 50, 100, 40);
  Text Exit(WINDOW_X / 2, WINDOW_Y / 2 + 50, "Quit");

  //The coins and bombs with their quotes.
  Circle coincoin(WINDOW_X / 2 - 40, WINDOW_Y / 2 - 120, 30);
  coincoin.setColor(COLOR("blue"));
  coincoin.setFill(true);
  Text coint(WINDOW_X / 2 - 90, WINDOW_Y / 2 - 120, "Catch Me if you can");

  Circle bombbomb(WINDOW_X / 2 + 40, WINDOW_Y / 2 - 120, 30);
  bombbomb.setColor(COLOR("red"));
  bombbomb.setFill(true);
  Text bombt(WINDOW_X / 2 + 90, WINDOW_Y / 2 - 120, "Avoid Me if you can");

  getClick();

  int cor, XC, YC;
  cor = getClick();
  XC = cor / 65536;
  YC = cor % 65536;
  //Loop to keep the home screen up until user chooses an option
  while (true)
  {

    if (XC < WINDOW_X / 2 + 50 && XC > WINDOW_X / 2 - 50)
    {

      //USER CHOSES TO BEGIN THE GAME
      if (YC < WINDOW_Y / 2 - 30 && YC > WINDOW_Y / 2 - 70)
        break;

      //USER WANTS TO VIEW THE INSTRUCTIONS
      else if (YC < WINDOW_Y / 2 + 20 && WINDOW_Y / 2 - 20)
      {

        coincoin.hide();
        bombbomb.hide();
        coint.hide();
        bombt.hide();
        R1.hide();
        R2.hide();
        R3.hide();
        FreePlay.hide();
        Help.hide();
        Exit.hide();
        while (true)
        {
          Text Help2(WINDOW_X / 2, 50, "INSTRUCTIONS");
          //INSTRUCTIONS GO HERE ONCE THE GAME IS MODIFIED WITH LEVELS, MAGNETS? AND BOMBS.
          Text h1(WINDOW_X / 2, 120, "HOW TO PLAY: A standard lasso is given to you with the help of which, you need to catch the coin moving on the screen.");
          Text h2(WINDOW_X / 2, 140, "Each time you are able to catch a coin, the coins in the bank increase.");
          Text h3(WINDOW_X / 2, 160, "Each time you catch a bomb, the coins in the bank decrease.");
          Text h4(WINDOW_X / 2, 180, "There are 3 levels in the game. A timer will run at the top of your screen, to complete each level you must meet the target.");
          Text h5(WINDOW_X / 2, 200, "The target involves catching the coins required mentioned at the top, before the timer hits zero.");
          Text h6(WINDOW_X / 2, 220, "In case the timer hits zero, you will lose a life. Remeber that lives do not get refreshed at the beginning of each level!");
          Text h7(WINDOW_X / 2, 240, "You will however retain coins if you lose a life. If you lose all your lives, you lose the game!");
          Text h8(WINDOW_X / 2, 260, "At the beginning of each level, you may receive a power-up or get some info about the next level.");
          Text h9(WINDOW_X / 2, 290, "KEY-MAPPING:");
          Rectangle seeMapping(WINDOW_X / 2 + 100, 290, 20, 20);
          Text Mapping(WINDOW_X / 2 + 100, 290, "View");
          //INSTRUCTIONS END HERE
          Rectangle ExitI(WINDOW_X - 150, WINDOW_Y - 70, 100, 40);
          Rectangle Begin(150, WINDOW_Y - 70, 100, 40);
          Text back1(WINDOW_X - 150, WINDOW_Y - 70, "Quit");
          Text begin1(150, WINDOW_Y - 70, "Start Game");
          int CORI = getClick(), xI, yI;
          xI = CORI / 65536;
          yI = CORI % 65536;
          if (xI < WINDOW_X / 2 + 110 && xI > WINDOW_X / 2 + 90 && yI < 300 && yI > 280)
          {
            h1.hide();
            h2.hide();
            h3.hide();
            h4.hide();
            h5.hide();
            h6.hide();
            h7.hide();
            h8.hide();
            h9.hide();
            seeMapping.hide();
            Mapping.hide();
            help();
          }
          h1.show();
          h2.show();
          h3.show();
          h4.show();
          h5.show();
          h6.show();
          h7.show();
          h8.show();
          h9.show();
          seeMapping.show();
          Mapping.show();
          //Display all previous instructions by using hn.show();

          if (xI > WINDOW_X - 200 && xI < WINDOW_X - 100 && yI < WINDOW_Y - 50 && yI > WINDOW_Y - 90)
            exit(0); //LEAVE GAME AFTER READING INSTRUCTIONS
          else if (xI > 100 && xI < 200 && yI < WINDOW_Y - 50 && yI > WINDOW_Y - 90)
            break; //START GAME AFTER READING INSTRUCTIONS<IF USER OPENS THE MAPPING, HE WILL NEED TO PRESS START TWICE!>
        }
        break;
      }

      //USER WANTS TO QUIT
      else if (YC < WINDOW_Y / 2 + 70 && YC > WINDOW_Y / 2 + 30)
      {
        exit(0);
        break;
      } //QUIT THE GAME
    }
  }
  Bottom.hide();
  Bottom2.hide();
  coincoin.hide();
  bombbomb.hide();
  coint.hide();
  bombt.hide();
  R1.hide();
  R2.hide();
  R3.hide();
  FreePlay.hide();
  Help.hide();
  Exit.hide();

  //If the User chooses to start the game:

  int stepCount = 0;
  float stepTime = STEP_TIME;
  float runTime = -1; // sec; -ve means infinite
  float currTime = 0;

  // Draw lasso at start position
  double release_speed = INIT_RELEASE_SPEED;         // m/s
  double release_angle_deg = INIT_RELEASE_ANGLE_DEG; // degrees
  double lasso_ax = 0;
  double lasso_ay = LASSO_G;
  bool paused = true;
  bool rtheta = true;
  Lasso lasso(release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);

  Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
  b1.setColor(COLOR("blue"));
  Line b2(PLAY_X_START, 0, PLAY_X_START, WINDOW_Y);
  b2.setColor(COLOR("blue"));

  string msg("Cmd: _");
  Text charPressed(PLAY_X_START + 50, PLAY_Y_HEIGHT + 20, msg);
  char coinScoreStr[256];
  sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins() + lasso.getNumBombs());
  Text coinScore(PLAY_X_START + 50, PLAY_Y_HEIGHT + 50, coinScoreStr);

  paused = true;
  rtheta = true;
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG;
  double coin_ax = 0;
  double coin_ay = COIN_G;
  Coin coin(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta); //CREATE A COIN
  Bomb bomb(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta); //CREATE A BOMB(This is a level-1 bomb and the parameters are same as coin)
  // After every COIN_GAP sec, make the coin jump

  double last_coin_jump_end = 0;
  double last_bomb_jump_end = 0;

  int level = 0;
  int lives = 3;
  //LEVEL-1 begins
  //TIME LIMIT: 120s

  //Display level 1 and coins required
  Text Level(WINDOW_X / 2, 50, "LEVEL-I");
  char scoreStr[256];
  sprintf(scoreStr, "Coins Required: %d", 15);
  Text scoreTar(WINDOW_X / 2, 130, scoreStr);

  //timer

  float t = 30;
  int T1 = 120;
  char timeStr[256];
  sprintf(timeStr, "Time: %d", T1);
  Text timer(WINDOW_X / 2, 100, timeStr);

  //Lives
  char livesStr[256];
  sprintf(livesStr, "Lives: %d", lives);
  Text lifeCount(WINDOW_X - 80, 100, livesStr);

  //Startup messages
  Text Start(WINDOW_X / 2, WINDOW_Y / 2, "Starting in ");
  STARTERTIME();
  Start.hide();

  for (;;)
  {
    /*Created a timer which basically exploits the time used to run one for loop. t is an arbitrary float value initialized at 30. each iteration leads
    to a decrement of 0.015 in t, reflecting on T1, T2 and T3 in proceeding levels with time
    gaps of 1 second */

    T1 = 10 * t - 180;
    sprintf(timeStr, "Time: %d", T1);
    timer.setMessage(timeStr);

    sprintf(livesStr, "Lives: %d", lives);
    lifeCount.setMessage(livesStr);

    if ((runTime > 0) && (currTime > runTime))
    {
      break;
    }

    XEvent e;
    bool pendingEv = checkEvent(e);
    if (pendingEv)
    {
      char c = charFromEvent(e);
      msg[msg.length() - 1] = c;
      charPressed.setMessage(msg);

      repeatf(c, lasso, coin, bomb); //calling the switch-case part(compressed in form of function to ensure that minimal duplication of code occurs
    }

    unpauseResetNextStep(lasso, coin, bomb, currTime, stepTime, last_coin_jump_end, last_bomb_jump_end);

    sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins() + lasso.getNumBombs());
    coinScore.setMessage(coinScoreStr);

    if (lasso.getNumCoins() + lasso.getNumBombs() == 15) //proceed to level 2 once coin requirement is fullfilled
    {                                                    //LEVEL-2 BEGINS
      //TIME LIMIT: 90s

      level = 1;

      sprintf(timeStr, "Time: %d", T1);
      timer.setMessage(timeStr);
      sprintf(livesStr, "Lives: %d", lives);
      lifeCount.setMessage(livesStr);

      // Modifications in level-2: changed time, increased target, introduction of magnet.

      lasso.COINZERO();
      Text Level(WINDOW_X / 2, 50, "LEVEL-II");
      int T2 = 90;
      //timer
      sprintf(timeStr, "Time: %d", T2);
      timer.setMessage(timeStr);

      sprintf(livesStr, "Lives: %d", lives);
      lifeCount.setMessage(livesStr);

      sprintf(scoreStr, "Coins Required: %d", 12);
      scoreTar.setMessage(scoreStr);

      t = 30;
      if (T1 > 40) //unlock the magnet
      {
        magnetUnlocked(lasso);
      }

      //Using nextLevel Func
      nextLevelmsg();

      for (;;)
      {
        T2 = 10 * t - 210;

        sprintf(timeStr, "Time: %d", T2);
        timer.setMessage(timeStr);

        sprintf(livesStr, "Lives: %d", lives);
        lifeCount.setMessage(livesStr);

        if (T2 == 75)
        {
          lasso.disableMagnet();
        }

        if ((runTime > 0) && (currTime > runTime))
        {
          break;
        }

        XEvent e;
        bool pendingEv = checkEvent(e);
        if (pendingEv)
        {
          char c = charFromEvent(e);
          msg[msg.length() - 1] = c;
          charPressed.setMessage(msg);
          repeatf(c, lasso, coin, bomb);
        }

        unpauseResetNextStep(lasso, coin, bomb, currTime, stepTime, last_coin_jump_end, last_bomb_jump_end);

        sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins() + lasso.getNumBombs());
        coinScore.setMessage(coinScoreStr);

        if (lasso.getNumCoins() + lasso.getNumBombs() == 12)
        {
          level = 2; //THIS DOES NOT INDICATE THE CURRENT LEVEL! IT INDICATES THE LEVEL COMPLETED.
          bomb.changeColor();
          lasso.COINZERO(); // ensure 0 coins after new level begins!

          Text Level(WINDOW_X / 2, 50, "LEVEL-III");
          if (T2 > 20)
          {
            magnetUnlocked(lasso);
          }

          //timer

          int T3 = 60;
          t = 30;
          sprintf(timeStr, "Time: %d", T3);
          timer.setMessage(timeStr);

          sprintf(livesStr, "Lives: %d", lives);
          lifeCount.setMessage(livesStr);

          sprintf(scoreStr, "Required Coins: %d", 12);
          scoreTar.setMessage(scoreStr);
          //Create a 3rd Level Bomb
          Bomb bomb3(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
          bomb3.changePos();
          bomb3.changeColor();
          double last_bomb3_jump_end = 0;

          //Using nextLevel Func
          Text level3instruct(WINDOW_X / 2, WINDOW_Y / 2 + 30, "Awesome! you made it to level-3. But be warned!");
          Text level3instruct2(WINDOW_X / 2, WINDOW_Y / 2 + 50, "2 bombs having color same as the coin and may change the postion suddenly :)");
          nextLevelmsg();
          level3instruct.hide();
          level3instruct2.hide();
          for (;;)
          {
            T3 = 10 * t - 240;
            if (T3 == 45)
            {
              lasso.disableMagnet();
            }

            sprintf(timeStr, "Time: %d", T3);
            timer.setMessage(timeStr);

            sprintf(livesStr, "Lives: %d", lives);
            lifeCount.setMessage(livesStr);

            if ((runTime > 0) && (currTime > runTime))
            {
              break;
            }

            XEvent e;
            bool pendingEv = checkEvent(e);
            if (pendingEv)
            {
              char c = charFromEvent(e);
              msg[msg.length() - 1] = c;
              charPressed.setMessage(msg);

              switch (c)
              {
              case 't':
                lasso.unpause();
                break;
              case 'y':
                lasso.yank();
                break;
              case 'l':
                lasso.loopit();
                lasso.check_for_coin(&coin);
                lasso.check_for_bomb(&bomb);
                lasso.check_for_bomb(&bomb3);

                wait(STEP_TIME * 5);
                break;
              case '[':
                if (lasso.isPaused())
                {
                  lasso.addAngle(-RELEASE_ANGLE_STEP_DEG);
                }
                break;
              case ']':
                if (lasso.isPaused())
                {
                  lasso.addAngle(+RELEASE_ANGLE_STEP_DEG);
                }
                break;
              case '-':
                if (lasso.isPaused())
                {
                  lasso.addSpeed(-RELEASE_SPEED_STEP);
                }
                break;
              case '=':
                if (lasso.isPaused())
                {
                  lasso.addSpeed(+RELEASE_SPEED_STEP);
                }
                break;

              case 'h':
              {
                help();
                c = '_';
              }
              break;

              case 'q':
                exit(0);
              default:
                break;
              }
            }

            bomb3.nextStep(stepTime);

            unpauseResetNextStep(lasso, coin, bomb, currTime, stepTime, last_coin_jump_end, last_bomb_jump_end);

            if (bomb3.isPaused())
            {
              if ((currTime - last_bomb3_jump_end) >= BOMB_GAP)
              {
                bomb3.unpause();
              }
            }

            if (bomb3.getYPos() > PLAY_Y_HEIGHT)
            {
              bomb3.resetBomb();
              last_bomb3_jump_end = currTime;
            }

            sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins() + lasso.getNumBombs());
            coinScore.setMessage(coinScoreStr);

            if (lasso.getNumCoins() + lasso.getNumBombs() == 12)
            { //Level-3 complete means game has been won!
              level = 3;
              Text v(400, 300, "YOU WON!");
              wait(3);
              leaderboard(lives, level);
              exit(0);
              break;
            }

            else if (T3 == 0)
            {
              lives--;
              //Decrease the lives, reflect on screen and give a warning.
              Warning(lives, t);
              //Ensure if the lives go to 0, then the user gets notified. Also he MUST Be given an option to save his progress.
              if (lives == 0)
              {
                Text gameover(WINDOW_X / 2, WINDOW_Y / 2, "GAME OVER!");
                wait(2);
                leaderboard(lives, level);
                exit(0);
              }
            }

            stepCount++;
            currTime += stepTime;
            wait(stepTime);
            t -= 0.015;
          } // End for(;;)

          wait(3);
        }
        else if (T2 == 0)
        {
          lives--;

          Warning(lives, t);
          if (lives == 0)
          {
            Text gameover(WINDOW_X / 2, WINDOW_Y / 2, "GAME OVER!");
            wait(2);
            leaderboard(lives, level);
            exit(0);
          }
        }

        stepCount++;
        currTime += stepTime;
        wait(stepTime);
        t -= 0.015;
      } // End for(;;)

      wait(3);
    }

    else if (T1 == 0)
    {
      lives--;

      if (lives == 0)
      {
        Text gameover(WINDOW_X / 2, WINDOW_Y / 2, "GAME OVER!");
        wait(2);
        leaderboard(lives, level);
        exit(0);
      }
      Warning(lives, t);
    }
    stepCount++;
    currTime += stepTime;
    wait(stepTime);
    t -= 0.015; //Decrease t

  } // End for(;;)
}

// End main_program
