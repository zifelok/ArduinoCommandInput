#include "ATerminal.h"

CommandParser::CommandParser(char *buffer, int16_t bufferSize, char *commandEnding)
{
    _buffer = buffer;
    _bufferSize = bufferSize;
    _commandEnding = commandEnding;
}

void CommandParser::write(char *command)
{
    Serial.println(command);
    int16_t i = 0;
    char *c = command;
    while (*c != '\0')
    {
        write(*c);
        c++;
    }
}

void CommandParser::reset()
{
    _bufferEnd = 0;
    _endingCount = 0;
    _commandSize = 0;
}

void CommandParser::write(char c)
{
    Serial.println(c);
    endOfCommand();
    // Detect end of command \0 or \r\n
    // endOfCommand();

    // Detect "

    // Detect special chars in str

    // Detect spaces

    /*
    char *nextEndingChar = _commandEnding + _endingCount;
    if (nextEndingChar == '\0')
    {
        endOfCommand();
        return;
    }

    if (c == nextEndingChar)
    {
        _endingCount++;
        return;
    }

    char *lastChar = '\0';
    if (_bufferEnd > 0)
        *lastChar = _buffer + _bufferEnd;
    char *nextChar = _buffer + _bufferEnd + 1;
    if (c == ' ' || c == '\t')
    {
        if (lastChar != '\0')
        {
            nextChar = '\0';
            _bufferEnd++;
        }
    }else if(c == '\"'){

    }
    _endingCount = 0;
    */
}

void CommandParser::endOfCommand()
{
    if (_callback == NULL)
        Serial.println("NULL");
    else
        _callback(5);
    reset();
}

void CommandParser::setCallback(void (*callback)(int))
{
    _callback = callback;
}

Command::Command(char *buffer, int16_t bufferSize, int8_t commandSize)
{
    _buffer = buffer;
    _bufferSize = bufferSize;
    _commandSize = commandSize;
    reset();
}

void Command::reset()
{
    _commandIndex = 0;
    _argPointer = _buffer;
}

bool Command::hasNext()
{
    return _commandIndex < _commandSize - 1;
}
bool Command::moveNext()
{
    if (!hasNext())
        return false;
    char *c = _argPointer;
    while (*c != '\0')
    {
        c++;
    }
    _argPointer = c + 1;
    _commandIndex++;
    return true;
}
char *Command::current()
{
    return _argPointer;
}
int8_t Command::getSize()
{
    return _commandSize;
}