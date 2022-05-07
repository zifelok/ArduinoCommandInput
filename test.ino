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

int8_t resultCount = 0;
char result[3][8];
bool bufferError = false;

void clearResult()
{
    resultCount = 0;
    bufferError = false;
}

void bufferErrorCallback()
{
    bufferError = true;
}

void onCommandCallback(Command *command)
{
    resultCount = command->getCount();
    Serial.print(F("Count\t"));
    Serial.println(resultCount);
    for (int8_t i = 0; i < resultCount; i++)
    {
        Serial.print(i);
        Serial.print('\t');
        char *c = command->get(i);
        Serial.println(c);
        int8_t j = 0;
        do
        {
            result[i][j] = c[j];
            j++;
        } while (c[j] != '\0');
    }
}

void putString(CommandInput *ci, char *c)
{
    for (int8_t i = 0; c[i] != '\0'; i++)
    {
        ci->put(c[i]);
    }
}


test(CommandInput_out_of_buffer_and_than_ok)
{
    CommandInput ci = CommandInput(buffer, 10);
    ci.setOnOutOfBufferError(bufferErrorCallback);
    ci.setOnCommand(onCommandCallback);
    clearResult();
    putString(&ci, "1234567890\r\n");

    assertEqual(0, resultCount);
    assertTrue(bufferError);
    
    clearResult();
    putString(&ci, "fi\r\n");

    assertFalse(bufferError);
    assertEqual(1, resultCount);
    assertEqual("fi", String(result[0]));
}

test(CommandInput_single)
{
    CommandInput ci = CommandInput(buffer, 64);
    ci.setOnOutOfBufferError(bufferErrorCallback);
    ci.setOnCommand(onCommandCallback);
    clearResult();
    putString(&ci, "first second third\r\n");

    assertFalse(bufferError);
    assertEqual(3, resultCount);
    assertEqual("first", String(result[0]));
    assertEqual("second", String(result[1]));
    assertEqual("third", String(result[2]));
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
