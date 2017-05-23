#pragma once
#include <API.h>
#include <vector>

namespace sensors {
struct quad_t {
  Encoder enc;
  unsigned char ports[2];
  long zero;
  bool inverted;
  void reset(void);
  long value(void);
  float request;
  void init(void);
  quad_t(unsigned char port1, unsigned char port2, bool _inverted);
};
class gyro_t {
  int calibration;

public:
  Gyro gyro;
  unsigned char port;
  long zero;
  void reset(void);
  long value(void);
  float request;
  void init(void);
  gyro_t(unsigned char _port, unsigned int _calibration);
};
struct pot_t {
  unsigned char port;
  long zero;
  bool inverted;
  void reset(void);
  long value(void);
  float request;
  void init(void);
  pot_t(unsigned char _port, bool _inverted);
};
struct button_t {
  unsigned char port;
  bool inverted;
  bool value(void);
  void init(void);
  button_t(unsigned char _port, bool _inverted);
};
void init(void);
void reset(void);

extern quad_t left;
extern quad_t right;
extern gyro_t gyro;
extern pot_t pot;
extern button_t button;
}
