
#include "tetro.h"

//Initialize the drawing pattern for each of the shapes with corresponding
//rotation patterns
const int Tetro::_Tetros[7][4][5][5] = {
    // Square
    {{{0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 1, 1, 0},
      {0, 0, 1, 1, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 1, 1, 0},
      {0, 0, 1, 1, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 1, 1, 0},
      {0, 0, 1, 1, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 1, 1, 0},
      {0, 0, 1, 1, 0},
      {0, 0, 0, 0, 0}}},
    // N
    {{{0, 0, 0, 0, 0},
      {0, 0, 0, 1, 0},
      {0, 0, 1, 1, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 1, 1, 0, 0},
      {0, 0, 1, 1, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 1, 1, 0, 0},
      {0, 1, 0, 0, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 1, 1, 0, 0},
      {0, 0, 1, 1, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0}}},
    // N Mirror
    {{{0, 0, 0, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 1, 0},
      {0, 0, 0, 1, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 0, 1, 1, 0},
      {0, 1, 1, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 1, 0, 0, 0},
      {0, 1, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 1, 1, 0},
      {0, 1, 1, 0, 0},
      {0, 0, 0, 0, 0}}},
    // L
    {{{0, 0, 0, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 1, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 1, 1, 1, 0},
      {0, 1, 0, 0, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 1, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 0, 0, 1, 0},
      {0, 1, 1, 1, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0}}},
    // L Mirror
    {{{0, 0, 0, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 1, 1, 0, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 1, 0, 0, 0},
      {0, 1, 1, 1, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 0, 1, 1, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 1, 1, 1, 0},
      {0, 0, 0, 1, 0},
      {0, 0, 0, 0, 0}}},
    // I
    {{{0, 0, 0, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {1, 1, 1, 1, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 1, 1, 1, 1},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0}}},
    // T
    {{{0, 0, 0, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 1, 1, 1, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 1, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 1, 1, 1, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 1, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0}}}};

Tetro::Tetro(int type) : _type(type) {
  rot = static_cast<int>(rand() % 4);
  rot_all = rot;
  _pos_x = 0;
  _pos_y = 0;
  //Initialize with random color for tetromino
  auto clr = static_cast<int>(rand() % 255);
  color[0] = clr;
  clr = static_cast<int>(rand() % 255);
  color[1] = clr;
  clr = static_cast<int>(rand() % 255);
  color[2] = clr;
}

bool Tetro::IsFree(int x, int y) {
  return _Tetros[_type][rot][x + 2][y + 2] == 0;
}

bool Tetro::IsFree(int _rot, int x, int y) {
  return _Tetros[_type][_rot][x + 2][y + 2] == 0;
}

void Tetro::UpdateRotate(int _rot) { rot = _rot; }

void Tetro::Move(int dx, int dy) {
  _pos_x += dx;
  _pos_y += dy;
}

void Tetro::GetPos(int &x, int &y) {
  x = _pos_x;
  y = _pos_y;
}

void Tetro::GetColor(int *clr) {
  clr[0] = color[0];
  clr[1] = color[1];
  clr[2] = color[2];
}

Tetro &Tetro::operator=(Tetro &&other) {
  rot = other.rot;
  _pos_x = other._pos_x;
  _pos_y = other._pos_y;
  _type = other._type;
  rot_all = other.rot_all;
  color[0] = other.color[0];
  color[1] = other.color[1];
  color[2] = other.color[2];
  return *this;
}

Tetro::Tetro(Tetro &&other) {
  rot = other.rot;
  _pos_x = other._pos_x;
  _pos_y = other._pos_y;
  _type = other._type;
  rot_all = other.rot_all;
  color[0] = other.color[0];
  color[1] = other.color[1];
  color[2] = other.color[2];

  printf("tet");
}
