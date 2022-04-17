#ifndef CommandInput_h
#define CommandInput_h

#include "Arduino.h"
#include "Command.h"

class CommandInput
{
private:
    char *_buffer;
    uint16_t _bufferSize;
    char *_separator;
    uint8_t _separatorSize;
    uint8_t _separatorEqualityCount;
    uint16_t _count;
    void reset();
    bool isOutOfBuffer();
    void endOfCommand();
    void (*_onOutOfBufferError)();
    void (*_onCommand)(Command *command);

public:
    CommandInput(char *buffer, uint16_t bufferSize, char *commandSeparator = "\r\n");
    void put(char c);
    void setOnOutOfBufferError(void (*callback)());
    void setOnCommand(void (*callback)(Command *command));
};

#endif