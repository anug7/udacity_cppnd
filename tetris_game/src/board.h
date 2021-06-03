#ifndef _BOARD_HPP_
#define _BOARD_HPP_

#include <memory>
#include <cassert>
#include <stdlib.h>

#include "tetro.h"

class Array2D{
public:
    Array2D(int row, int col)
           :_row(row), _col(col)
    {
        size = _row * _col;
        _arr = (int*)malloc(sizeof(int) * size);
        for(int i = 0; i < size; i++)
        {
            _arr[i] = 0;
        }
    }

    ~Array2D()
    {
        if (_arr != nullptr)
            free(_arr);;
    }

    int& at(int row, int col)
    {
        assert(row < _row && row >= 0);
        assert(col < _col && col >= 0);
        return _arr[row * _col +  col];
    }
private:
    int *_arr;
    int _row;
    int _col;
    size_t size;
};


class Board
{
public:
    Board(int h, int w);
    ~Board();
    bool IsFree(int row, int col);
    void UpdateBoard(Tetro *tetro);
    int CheckUnite(int py);
private:

    std::unique_ptr<Array2D> board_array;
    int _h;
    int _w;
    int cur_x;
    int cur_y;
};
#endif
