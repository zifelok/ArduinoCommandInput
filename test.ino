#include "Command.h"
#include "CommandInput.h"
#include <AUnit.h>

char *buffer = new char[64];
int32_t bufferSize = 64;

test(parse_empty)
{
  Command c = Command("", buffer, bufferSize);

  assertEqual(CommandStatus::successful, c.getStatus());
  assertEqual(0, c.getCount());
}

test(parse_single)
{
  Command c = Command("some", buffer, bufferSize);

  assertEqual(CommandStatus::successful, c.getStatus());
  assertEqual(1, c.getCount());
  assertEqual("some", String(c.get(0)));
}

test(parse_few)
{
  Command c = Command("some command with arguments", buffer, bufferSize);

  assertEqual(CommandStatus::successful, c.getStatus());
  assertEqual(4, c.getCount());
  assertEqual("some", String(c.get(0)));
  assertEqual("command", String(c.get(1)));
  assertEqual("with", String(c.get(2)));
  assertEqual("arguments", String(c.get(3)));
}

test(parse_few_with_extra_space)
{
  Command c = Command("   some command\t with    arguments   ", buffer, bufferSize);

  assertEqual(CommandStatus::successful, c.getStatus());
  assertEqual(4, c.getCount());
  assertEqual("some", String(c.get(0)));
  assertEqual("command", String(c.get(1)));
  assertEqual("with", String(c.get(2)));
  assertEqual("arguments", String(c.get(3)));
}

test(parse_empty_scopes)
{
  Command c = Command("\"\"", buffer, bufferSize);

  assertEqual(CommandStatus::successful, c.getStatus());
  assertEqual(0, c.getCount());
}

test(parse_scopes_keeps_format)
{
  Command c = Command("before \" in \t \" after", buffer, bufferSize);

  assertEqual(CommandStatus::successful, c.getStatus());
  assertEqual(3, c.getCount());
  assertEqual("before", String(c.get(0)));
  assertEqual(" in \t ", String(c.get(1)));
  assertEqual("after", String(c.get(2)));
}

test(parse_scopes_reads_special_chars)
{
  Command c = Command("before \"la2 \\\\ \\t la2\" \"\\\"\\r\\n\" after'", buffer, bufferSize);

  assertEqual(CommandStatus::successful, c.getStatus());
  assertEqual(4, c.getCount());
  assertEqual("before", String(c.get(0)));
  assertEqual("la2 \\ \t la2", String(c.get(1)));
  assertEqual("\"\r\n", String(c.get(2)));
  assertEqual("after'", String(c.get(3)));
}

test(parse_unknown_char_after_slash)
{
  Command c = Command("\"0123\\56\"", buffer, bufferSize);

  assertEqual(0, c.getCount());
  assertEqual(CommandStatus::errorAtPosition, c.getStatus());
  assertEqual((uint16_t)5, c.getErrorPosition());
}

test(parse_out_of_buffer)
{
  Command c = Command("012356", buffer, 3);

  assertEqual(0, c.getCount());
  assertEqual(CommandStatus::outOfBufferError, c.getStatus());
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
