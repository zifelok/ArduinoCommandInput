#include "CommandInput.h"

CommandInput::CommandInput(char *buffer, uint16_t bufferSize, char *commandSeparator)
{
    _buffer = buffer;
    _bufferSize = bufferSize;
    _separator = commandSeparator;
    _separatorSize = 0;
    while (_separator[_separatorSize] != '\0')
        _separatorSize++;
    reset();
}

void CommandInput::reset()
{
    _count = 0;
    _separatorEqualityCount = 0;
}

void CommandInput::put(char c)
{
    if (_separator[_separatorEqualityCount] == c)
        _separatorEqualityCount++;
    else
        _separatorEqualityCount = 0;

    if (_separatorEqualityCount == _separatorSize)
    {
        endOfCommand();
        return;
    }

    if (isOutOfBuffer())
        return;

    _buffer[_count++] = c;
}

bool CommandInput::isOutOfBuffer()
{
    // -1 for '\0' char
    return _count >= _bufferSize - 1;
}

void CommandInput::endOfCommand()
{
    if (isOutOfBuffer())
    {
        if (_onOutOfBufferError != NULL)
            _onOutOfBufferError();
    }
    else
    {
        if (_onCommand != NULL)
        {
            // +1 cause last ending is not counted
            _buffer[_count - _separatorEqualityCount + 1] = '\0';
            Command c(_buffer);
            _onCommand(&c);
        }
    }
    reset();
}

void CommandInput::setOnOutOfBufferError(void (*callback)())
{
    _onOutOfBufferError = callback;
}

void CommandInput::setOnCommand(void (*callback)(Command *command))
{
    _onCommand = callback;
}