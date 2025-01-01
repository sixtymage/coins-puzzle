#include "Board.h"
#include <stdio.h>

Board::Board()
{
  // board starts:
  //
  //  E E E E R R R R W W W W E E E E
  //
  //

  for (int i = 0; i < 4; i++)
  {
    m_values[i] = Value_Empty;
  }

  for (int i = 4; i < 8; i++)
  {
    m_values[i] = Value_Red;
  }

  for (int i = 8; i < 12; i++)
  {
    m_values[i] = Value_White;
  }


  for (int i = 12; i < 16; i++)
  {
    m_values[i] = Value_Empty;
  }
}

Board::Board(const Board& copyFrom)
{
  for (int i = 0; i < 16; i++)
  {
    m_values[i] = copyFrom.m_values[i];
  }
}


int Board::GetFirstEmptyBlock(int startFrom) const
{
  int firstBlock = -1;

  for (int i = startFrom; i < 15 && firstBlock == -1; i++)
  {
    if (IsEmpty(i) && IsEmpty(i + 1))
    {
      firstBlock = i;
    }
  }

  return firstBlock;
}

void Board::Move(int moveFrom, int moveTo)
{
  // 
  m_values[moveTo] = m_values[moveFrom];
  m_values[moveFrom] = Value_Empty;

  m_values[moveTo + 1] = m_values[moveFrom + 1];
  m_values[moveFrom + 1] = Value_Empty;
}

bool Board::IsComplete() const
{
  // complete if:
  //  all are alternating
  //  there are no gaps
  int start = -1;

  for (int i = 0; i < 16 && start == -1; i++)
  {
    if (!IsEmpty(i))
    {
      start = i;
    }
  }

  if (start == -1)
  {
    return false;
  }

  Value currVal = GetValue(start);
  bool isOk = true;

  for (int i = start + 1; i < start + 8 && isOk; i++)
  {
    Value nextVal = GetValue(i);

    isOk = false;
    if (currVal == Value_Red)
    {
      isOk = nextVal == Value_White;
    }
    else if (currVal == Value_White)
    {
      isOk = nextVal == Value_Red;
    }

    currVal = nextVal;
  }

  if (!isOk)
  {
    return false;
  }

  // finally should check remainder are empty

  for (int i = start + 8; i < 16; i++)
  {
    if (!IsEmpty(i))
    {
      return false;
    }
  }

  return true;
}


void Board::Print() const
{
  printf("[ ");
  for (int i = 0; i < 16; i++)
  {
    switch (GetValue(i))
    {
    case Value_Empty: printf("E "); break;
    case Value_Red: printf("R "); break;
    case Value_White: printf("W "); break;
    }
  }
  printf("]\n");
}
