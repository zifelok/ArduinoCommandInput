#ifndef ATerminal_h
#define ATerminal_h

#include "Arduino.h"
/*
class ATerminal
{
public:
    ATerminal(Stream *serial, char *buffer, int16_t bufferSize, char *term = "\r\n");
    void iterate();

private:
    Stream *_serial;
    char *_buffer;
    int16_t _bufferSize;
    char *_term;
    int16_t _pointer;

    void resetBuffer();
    void putInBuffer(char c);
};
*/
class CommandParser
{
public:
    CommandParser(char *buffer, int16_t bufferSize, char *commandEnding = "\r\n");
    void write(char c);
    void write(char *command);
    void reset();
    void setCallback(void (*callback)(int));

private:
    void (*_callback)(int);
    char *_buffer;
    int16_t _bufferSize;
    char *_commandEnding;
    int16_t _bufferEnd;
    int8_t _endingCount;
    int8_t _commandSize;
    
    
    void endOfCommand();
    
};

class Command
{
public:
    Command(char *buffer, int16_t bufferSize, int8_t commandSize);
    void reset();
    bool hasNext();
    bool moveNext();
    char * current();
    int8_t getSize();
private:
    char *_buffer;
    int16_t _bufferSize;
    int8_t _commandSize;
    int8_t _commandIndex;
    char *_argPointer;
};

#endif