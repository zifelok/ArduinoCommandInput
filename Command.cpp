#include "Command.h"

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
    while (str[i] != '\0')
    {
        last = inBuffer == 0 ? '\0' : buffer[inBuffer];
        
        if (last == '\0')
            ++commandSize;

        buffer[inBuffer++] = last = str[i];
        ++i;
    }

    buffer[inBuffer++] = '\0';
    return Command(buffer, commandSize);
}