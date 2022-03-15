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
    // Detect "

    // Detect special chars in str

    // Detect spaces, and break with \0
    if (c == ' ' || c == '\t')
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
}

Command CommandParser::parse()
{
    return Command(_buffer, _commandSize);
}

Command::Command(char *buffer, int8_t commandSize)
{
    _buffer = buffer;
    _commandSize = commandSize;
}

int8_t Command::getCommandSize()
{
    return _commandSize;
}