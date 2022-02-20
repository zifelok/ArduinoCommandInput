#ifndef ATerminal_h
#define ATerminal_h

#include "Arduino.h"

class Command
{
public:
    Command(char *buffer, int8_t commandSize);
    void reset();
    bool hasNext();
    bool moveNext();
    char *current();
    int8_t getSize();

private:
    char *_buffer;
    int8_t _commandSize;
    int8_t _commandIndex;
    char *_argPointer;
};

class CommandParser
{
public:
    CommandParser(char *buffer, int16_t bufferSize, char *commandEnding = "\r\n");
    void write(char c);
    void parse(char *command);
    void reset();
    void setCallback(void (*callback)(Command));

private:
    void (*_callback)(Command);
    char *_buffer;
    int16_t _bufferSize;
    char *_commandEnding;
    int16_t _bufferEnd;
    int8_t _endingCount;
    int8_t _commandSize;

    void endOfCommand();
    bool putToBuffer(char c);
};

#endif