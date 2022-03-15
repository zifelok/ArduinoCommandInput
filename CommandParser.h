#ifndef CommandParser_h
#define CommandParser_h

#include "Arduino.h"

class Command
{
public:
    Command(char *buffer, int8_t commandSize);
    int8_t getCommandSize();

private:
    char *_buffer;
    int8_t _commandSize;
};

class CommandParser
{
public:
    CommandParser(char *buffer, int16_t bufferSize, char *commandEnding = "\r\n");
    // append single char
    bool append(char c);
    // append string
    bool append(char *command);
    // write single char and detect commandEnding
    bool write(char c);
    // reset buffer
    void reset();
    Command parse();

private:
    char *_buffer;
    int16_t _bufferSize;
    char *_commandEnding;
    int16_t _inBuffer;
    int8_t _endingCount;
    int8_t _commandSize;
    int16_t _errorPosition;
    int16_t _inputCount;
    bool put(char c);
    void endCommand();
};

#endif