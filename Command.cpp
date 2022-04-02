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
    if (_status == CommandStatus::successful)
        return _count;
    return 0;
}

char *Command::get(uint8_t i)
{
    if (i >= getCount())
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
    _status = CommandStatus::successful;
    _errorPosition = 0;

    uint16_t i = 0;
    char last;
    char current;
    bool quotes = false;
    while (str[i] != '\0')
    {
        if (_status != CommandStatus::successful)
            return;

        _errorPosition = i;
        current = str[i];
        ++i;

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
                _status = CommandStatus::errorAtPosition;
                break;
            }

            continue;
        }

        put(current);
    }
    if (quotes)
        _status = CommandStatus::errorAtPosition;

    put('\0');
}

void Command::put(char c)
{
    if (c == '\0' && getLast() == '\0')
        return;

    if (_inBuffer >= _bufferSize)
    {
        _status = CommandStatus::outOfBufferError;
        return;
    }

    _buffer[_inBuffer++] = c;
    if (c == '\0')
        ++_count;
}

char Command::getLast()
{
    return _inBuffer == 0 ? '\0' : _buffer[_inBuffer - 1];
}

CommandStatus Command::getStatus()
{
    return _status;
}

uint16_t Command::getErrorPosition()
{
    if (_status == CommandStatus::errorAtPosition)
        return _errorPosition;
    return 0xFFFF;
}