#include "ATerminal.h"
#include <AUnit.h>

char *commandBuffer = new char[64]{'1', '2', '\0', 'a', '\0', 'g', '1', '\0', 'r'};
Command testCommand = Command(commandBuffer, 3);

test(command_keeps_size)
{
  assertEqual(3, testCommand.getSize());
}

test(command_iterator_works)
{
  testCommand.reset();
  for (int8_t i = 0; i < 7; ++i)
  {
    assertEqual(F("12"), testCommand.current());
    assertEqual(true, testCommand.moveNext());
    assertEqual(F("a"), testCommand.current());
    assertEqual(true, testCommand.moveNext());
    assertEqual(F("g1"), testCommand.current());
    assertEqual(false, testCommand.moveNext());
    testCommand.reset();
  }
}

void setup()
{
  Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop()
{
  aunit::TestRunner::run();
}
