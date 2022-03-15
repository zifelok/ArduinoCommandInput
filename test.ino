#include "CommandParser.h"
#include <AUnit.h>

test(parse_returns_empty)
{
  CommandParser cp(new char[1], 1);

  Command c = cp.parse();

  assertEqual(0, c.getCommandSize());
}

test(parse_append_puts_in_buffer)
{
  char *expected = "something";
  char *buffer = new char[16]{};
  CommandParser cp(buffer, 16);

  cp.append("some");
  cp.append("thing");
  Command c = cp.parse();

  assertEqual(1, c.getCommandSize());
  assertEqual(String(expected), String(buffer));
}

/*
test(Array_OK)
{
  int8_t n = 16;
  char *expected = new char[16]{'1', '2', '\0', 'a', '\0', 'g', '1', '\0', 'r'};
  char *buffer = new char[16]{'1', '2', '\0', 'a', '\0', 'g', '1', '\0', 'r'};
  for (int8_t i = 0; i < n; ++i)
    assertEqual(expected[i], buffer[i]);
}
*/

void setup()
{
  Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop()
{
  aunit::TestRunner::run();
}
