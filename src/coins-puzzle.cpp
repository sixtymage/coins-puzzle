#include "Board.h"
#include <stdio.h>

const int REQUIRED_NUM_MOVES = 4;
bool MakeMove(const Board& board, int numMoves);

int main()
{
  Board board;

  int numMoves = 0;

  // do the first recursive call
  if (MakeMove(board, numMoves))
  {
    printf("Success!\n");
  }

  return 0;
}

bool MakeMove(const Board& board, int numMoves)
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
        printf("Move: %d to %d\n", i, moveTo);
        newBoard.Print();
        printf("\n");

        if (numMoves + 1 == REQUIRED_NUM_MOVES)
        {
          if (newBoard.IsComplete())
          {
            printf("Found Match!\n");
            printf("The final move was: \n");
            printf("Move: %d to %d giving: \n", i, moveTo);
            newBoard.Print();
            printf("\n");
            return true;
          }
          else
          {
            printf("4th Move did not succeed; back tracking and trying another...\n");
          }
        }
        else
        {
          // not too many moves yet - try another
          bool isCorrect = MakeMove(newBoard, numMoves + 1);

          if (isCorrect)
          {
            // this was a good move; return
            printf("\n");
            printf("The previous move was: \n");
            printf("Move: %d to %d giving: \n", i, moveTo);
            newBoard.Print();
            printf("\n");
            return true;
          }
          else
          {
            // this was not a good move - try a different one (at this level)
            printf("Failed; going back to:\n");
            board.Print();
            printf("\n");
          }
        }

        moveTo = board.GetFirstEmptyBlock(moveTo + 1);

      }
    }
  }

  // if we have gone through all possibilities without returning then return false
  return false;
}
