#include "../include/main.h"

namespace drive {
side_t left;
side_t right;
double inch = 28.64788975654116043839907740705258516620273623328216077458012735;

void side_t::set(int power) {
  side_t::topM.set(power);
  side_t::midM.set(power);
  side_t::lowM.set(power);
}

void init(void) {
  left.topM    = motors::init(2, 1, .5, .8);
  left.midM    = motors::init(3, -1, .5, .8);
  left.lowM    = motors::init(4, 1, .5, .8);
  right.topM   = motors::init(7, -1, .5, .8);
  right.midM   = motors::init(8, 1, .5, .8);
  right.lowM   = motors::init(9, -1, .5, .8);
  left.sensor  = &sensors::left;
  right.sensor = &sensors::right;
}

void set(int lpower, int rpower) {
  left.set(lpower);
  right.set(rpower);
}

void tank(void) {
  int deadband = 20;
  int lj       = joystickGetAnalog(1, 3);
  int rj       = joystickGetAnalog(1, 2);
  if (abs(lj) < deadband && abs(rj) < deadband) {
    pid::enable();
    return;
  }
  lj              = (abs(lj) < deadband) ? 0 : lj;
  rj              = (abs(rj) < deadband) ? 0 : rj;
  pid::enabled[0] = (lj == 0);
  pid::enabled[1] = (rj == 0);
  if (lj != 0)
    left.set(lj);
  if (rj != 0)
    right.set(rj);
  pid::request((lj == 0) ? left.sensor->request : left.sensor->value(),
               (rj == 0) ? right.sensor->request : right.sensor->value());
}

namespace accel {
long x     = 0;
long y     = 0;
long prevX = 0;
long prevY = 0;
void drive(void) {
  prevX          = x;
  prevY          = y;
  x              = 0 - joystickGetAnalog(1, ACCEL_X);
  y              = 0 - joystickGetAnalog(1, ACCEL_Y);
  int threshold  = 20;
  int multiplier = 1.1;

  if (abs(x) < threshold)
    x = 0;
  if (abs(y) < threshold)
    y = 0;

  x *= multiplier;
  y *= (multiplier * 1.25);

  set(x - y, x + y);
}
}

void inches(long inches) {
  pid::enable();
  left.sensor->request += inches * inch;
  right.sensor->request += inches * inch;
  pid::wait(pid::default_precision, inches * inches * 8);
  pid::disable();
}
}
