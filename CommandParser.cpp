#include "CommandParser.h"

CommandParser::CommandParser(char *buffer, int16_t bufferSize, char *commandEnding)
{
    _buffer = buffer;
    _bufferSize = bufferSize;
    _commandEnding = commandEnding;
    reset();
}

bool CommandParser::append(char c)
{
    _inputCount++;
    if (_errorPosition >= 0)
        return false;
    if (!put(c))
    {
        _errorPosition = _inputCount - 1;
        return false;
    }
    return true;
}

bool CommandParser::put(char c)
{
    // skip \0
    if (c == '\0')
        return true;
    // Detect "
    if (c == '"')
    {
        _quotes = !_quotes;
        return true;
    }

    // Detect special chars in str

    // Detect spaces, and break with \0
    if ((c == ' ' || c == '\t') && !_quotes)
    {
        if (_inBuffer == 0 || _buffer[_inBuffer - 1] == '\0')
            return true;
        c = '\0';
        _commandSize++;
    }

    _buffer[_inBuffer] = c;
    _inBuffer++;
    return true;
}

bool CommandParser::write(char c)
{
    return append(c);
}

bool CommandParser::append(char *command)
{
    char *c = command;
    while (*c != '\0')
    {
        if (!append(*c))
            return false;
        c++;
    }
}

void CommandParser::reset()
{
    _inBuffer = 0;
    _endingCount = 0;
    _commandSize = 0;
    _errorPosition = -1;
    _inputCount = 0;
    _quotes = false;
}

void CommandParser::endCommand()
{
    if (_buffer[_inBuffer - 1] != '\0')
        put(' ');
    if (_quotes)
    {
        _errorPosition = _inputCount;
    }
}

Command CommandParser::parse()
{
    endCommand();
    if (_errorPosition < 0)
        return Command(_buffer, _commandSize);
    else
        return Command(NULL, 0, _errorPosition);
}

Command::Command(char *buffer, int8_t commandSize, int16_t errorPosition)
{
    _buffer = buffer;
    _commandSize = commandSize;
    _errorPosition = errorPosition;
}

int8_t Command::getCommandSize()
{
    return _commandSize;
}

char *Command::get(int8_t i)
{
    if (i < 0 || i >= _commandSize)
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