#include "ATerminal.h"

CommandParser::CommandParser(char *buffer, int16_t bufferSize, char *commandEnding)
{
    _buffer = buffer;
    _bufferSize = bufferSize;
    _commandEnding = commandEnding;
}

void CommandParser::parse(char *command)
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
    // Detect end of command \0 or \r\n
    endOfCommand();

    // endOfCommand();

    // Detect "

    // Detect special chars in str

    // Detect spaces
}

bool CommandParser::putToBuffer(char c)
{
    // Detect "

    // Detect special chars in str

    // Detect spaces
}

void CommandParser::endOfCommand()
{
    if (_callback != NULL)
    {
        Command command = Command(_buffer, _commandSize);
        _callback(command);
    }
    reset();
}

void CommandParser::setCallback(void (*callback)(Command))
{
    _callback = callback;
}

Command::Command(char *buffer, int8_t commandSize)
{
    _buffer = buffer;
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