#include "Command.h"
#include <AUnit.h>

test(parse_empty)
{
  char *str = "";

  Command c = Command::parse(str);

  assertEqual(0, c.getCommandSize());
}

test(parse_single)
{
  char *str = "some";

  Command c = Command::parse(str);

  assertEqual(1, c.getCommandSize());
  assertEqual("some", String(c.get(0)));
}

test(parse_few)
{
  char *str = "some command with arguments";

  Command c = Command::parse(str);

  assertEqual(4, c.getCommandSize());
  assertEqual("some", String(c.get(0)));
  assertEqual("command", String(c.get(1)));
  assertEqual("with", String(c.get(2)));
  assertEqual("arguments", String(c.get(3)));
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
