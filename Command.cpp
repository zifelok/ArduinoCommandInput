#include "Command.h"
//#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINT(x) Serial.print(x)
#define DEBUG_PRINTLN(x) Serial.println(x)
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTLN(x)
#endif

Command::Command(char *str)
{
    build(str, str, 0xFFFF);
}

Command::Command(char *str, char *buffer, uint16_t bufferSize)
{
    build(str, buffer, bufferSize);
}

uint8_t Command::getCount()
{
    return _count;
}

char *Command::get(uint8_t i)
{
    if (i >= _count)
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

void Command::build(char *str, char *buffer, uint16_t bufferSize)
{
    _buffer = buffer;
    _bufferSize = bufferSize;
    _count = 0;
    _inBuffer = 0;

    uint16_t i = 0;
    char last;
    char current;
    bool quotes = false;
    while (str[i] != '\0')
    {
        current = str[i];
        ++i;
        /*
        DEBUG_PRINT("i:\t");
        DEBUG_PRINT(i);
        DEBUG_PRINT("\tinBuffer:\t");
        DEBUG_PRINT(_inBuffer);
        DEBUG_PRINT("\tcurrent:\t");
        DEBUG_PRINTLN(current);
        */

        if (current == '"')
        {
            quotes = !quotes;
            continue;
        }

        if (!quotes && (current == ' ' || current == '\t'))
        {
            if (getLast() != '\0')
                put('\0');

            continue;
        }

        if (quotes && current == '\\')
        {
            current = str[i];
            ++i;
            switch (current)
            {
            case '\"':
                put('\"');
                break;
            case '\\':
                put('\\');
                break;
            case 'n':
                put('\n');
                break;
            case 'r':
                put('\r');
                break;
            case 't':
                put('\t');
                break;

            default:
                break;
            }

            continue;
        }

        put(current);
    }

    put('\0');
}

bool Command::put(char c)
{
    if (c == '\0' && getLast() == '\0')
        return true;
    if (_inBuffer >= _bufferSize)
        return false;
    _buffer[_inBuffer++] = c;
    if (c == '\0')
        ++_count;
    return true;
}

char Command::getLast()
{
    return _inBuffer == 0 ? '\0' : _buffer[_inBuffer - 1];
}