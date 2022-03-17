#include "Command.h"
//#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINT(x) Serial.print(x)
#define DEBUG_PRINTLN(x) Serial.println(x)
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTLN(x)
#endif

Command Command::parse(char *str)
{
    return Command::build(str, str, 0xFFFF);
}

Command Command::parse(char *str, char *buffer, uint16_t bufferSize)
{
    return Command::build(str, buffer, bufferSize);
}

Command::Command(char *buffer, uint8_t commandSize)
{
    _buffer = buffer;
    _commandSize = commandSize;
}

uint8_t Command::getCommandSize()
{
    return _commandSize;
}

char *Command::get(uint8_t i)
{
    if (i >= _commandSize)
        return NULL;
    char *c = _buffer;
    while (i > 0)
    {
        while (*c != '\0')
            c++;
        while (*c == '\0')
            c++;
        --i;
    }
    return c;
}

Command Command::build(char *str, char *buffer, uint16_t bufferSize)
{
    uint8_t commandSize = 0;
    uint16_t inBuffer = 0;
    uint16_t i = 0;
    char last;
    char current;
    while (str[i] != '\0')
    {
        current = str[i];
        DEBUG_PRINT("i:\t");
        DEBUG_PRINT(i);
        DEBUG_PRINT("\tinBuffer:\t");
        DEBUG_PRINT(inBuffer);
        DEBUG_PRINT("\tcurrent:\t");
        DEBUG_PRINTLN(current);

        ++i;
        last = inBuffer == 0 ? '\0' : buffer[inBuffer - 1];

        if (current == ' ' || current == '\t')
        {
            if (last != '\0')
                buffer[inBuffer++] = '\0';

            continue;            
        }

        if (last == '\0')
            ++commandSize;

        buffer[inBuffer++] = current;
    }

    buffer[inBuffer++] = '\0';
    return Command(buffer, commandSize);
}