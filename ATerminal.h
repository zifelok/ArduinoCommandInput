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
    void resetBuffer();

private:
    char *_buffer;
    int16_t _bufferSize;
    char *_commandEnding;
    int16_t _bufferEnd;
    int8_t _endingCount;
    
    
    void endOfCommand();
    
};

#endif