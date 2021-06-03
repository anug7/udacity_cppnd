#ifndef _TETRO_H_
#define _TETRO_H_

#include <math.h>

class Tetro {
public:
  Tetro(int type);
  Tetro(Tetro &&other);

  bool IsFree(int x, int y);
  bool IsFree(int rot, int x, int y);
  void UpdateRotate(int diff);
  void Move(int dx, int dy);
  void GetPos(int &x, int &y);
  void GetColor(int *clr); 
  int rot_all;
  
  Tetro& operator=(Tetro &&);

private:
  static const int _Tetros[7][4][5][5]; // 7 shapes with 4 rotations with grid size of 5x5
  int _type;
  int rot;
  int _pos_x;
  int _pos_y;
  int color[3];
};


#endif
