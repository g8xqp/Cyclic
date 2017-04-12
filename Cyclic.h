#ifndef Cyclic_h
#define Cyclic_h
#include "Arduino.h"

#ifndef CYCLIC_BUFFER
#define CYCLIC_BUFFER 2
#endif

#if ( CYCLIC_BUFFER == 1 )
#define CBUFFER_SIZE 8
#define CBUFFER_MASK 0x07
#else
#if ( CYCLIC_BUFFER == 2 )
#define CBUFFER_SIZE 16
#define CBUFFER_MASK 0x0F
#else
#define CBUFFER_SIZE 32
#define CBUFFER_MASK 0x1F
#endif
#endif

class CyclicBuffer{
  private:
    byte MyBuffer[CBUFFER_SIZE];
    byte WrPtr;
    byte RdPtr;
    byte Avail;
    byte IncrementPtr(byte p,byte n);
    byte IncrementPtr(byte p);
    void SetAvail();
  public:
    byte BufferSize();     // size of buffer
    bool ReadAvailable();  // return true if data in buffer
    byte GetAvailableLen();// return number of bytes in buffer
    bool WriteFull();      // return true if buffer full
    bool WriteByte(byte b);// write byte into buffer
    void WriteByteForce(byte b);// force byte into buffer
    byte ReadByte();       // read byte from buffer
    void Flush();          // flush buffer
    void Flush(byte p);    // flush p bytes from buffer
    byte ViewByte();       // view next byte without popping from buffer
    byte ViewByte(byte p); // view byte p without popping from buffer
    CyclicBuffer();
    ~CyclicBuffer(){}
};

#endif
