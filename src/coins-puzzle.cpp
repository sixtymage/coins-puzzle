#include <stdio.h>
#include <string>
#include <stdexcept>
#include "Board.h"

const int DEFAULT_NUM_ALLOWED_MOVES = 4;
static bool MakeMove(const Board& board, int numMoves, int numAllowedMoves);
static int GetNumAllowedMoves(int argc, char** argv);

int main(int argc, char** argv)
{
  int numAllowedMoves = GetNumAllowedMoves(argc, argv);

  Board board;
  if (MakeMove(board, 0, numAllowedMoves))
  {
    board.Print("Initial board        :");
    printf("Success!\n");
  }
  else
  {
    printf("Failed to find a solution for %i allowed moves.", numAllowedMoves);
  }

  return 0;
}

static bool MakeMove(const Board& board, int numMoves, int numAllowedMoves)
{
  // we go through every pair of coins...
  for (int i = 0; i < 15; i++)
  {
    // if this is not an empty space AND next space is not empty we can move these
    if (!board.IsEmpty(i) && !board.IsEmpty(i + 1))
    {
      // we make every move we can possibly make with these coins
      int moveTo = board.GetFirstEmptyBlock(0);
      while (moveTo != -1)
      {
        // make a new board with this move
        Board newBoard(board);
        newBoard.Move(i, moveTo);

        if (numMoves + 1 == numAllowedMoves)
        {
          if (newBoard.IsComplete())
          {
            newBoard.Print(i, moveTo);
            return true;
          }
        }
        else
        {
          // not too many moves yet - try another
          bool isCorrect = MakeMove(newBoard, numMoves + 1, numAllowedMoves);

          if (isCorrect)
          {
            // this was a good move; return
            newBoard.Print(i, moveTo);
            return true;
          }
        }

        moveTo = board.GetFirstEmptyBlock(moveTo + 1);
      }
    }
  }

  // if we have gone through all possibilities without returning then return false
  return false;
}

static int GetNumAllowedMoves(int argc, char** argv)
{
  if (argc < 2)
  {
    return DEFAULT_NUM_ALLOWED_MOVES;
  }

  int arg = 0;
  try
  {
    arg = std::stoi(argv[1]);
  }
  catch (const std::invalid_argument&)
  {
    int arg = 0;
  }
  catch (const std::out_of_range&)
  {
    int arg = 0;
  }

  if (arg <= 0)
  {
    return DEFAULT_NUM_ALLOWED_MOVES;
  }

  return arg;
}
