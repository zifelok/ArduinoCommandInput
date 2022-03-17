#include "Command.h"
#include <AUnit.h>

test(parse_empty){
  char *str = "";

  Command c = Command::parse(str);

  assertEqual(0, c.getCommandSize());
}

test(parse_single){
  char *str = "some";

  Command c = Command::parse(str);

  assertEqual(1, c.getCommandSize());
  assertEqual("some", String(c.get(0)));
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
