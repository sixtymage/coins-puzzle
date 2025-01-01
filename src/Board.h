#include <string>

class Board
{

public:
  enum Value { Value_Red, Value_White, Value_Empty };

public:
  Board();
  Board(const Board& copyFrom);

  int GetFirstEmptyBlock(int startFrom = 0) const;

  Value GetValue(int index) const { return m_values[index]; }
  void SetValue(int index, Value value) { m_values[index] = value; }

  bool IsGlass(int index) const { return m_values[index] == Value_Red || m_values[index] == Value_White; }

  bool IsEmpty(int index) const { return m_values[index] == Value_Empty; }

  void Move(int moveFrom, int moveTo);

  bool IsComplete() const;

  void Print(const std::string& message) const;
  void Print(int moveFrom, int moveTo) const;

private:
  Value m_values[16];
};
