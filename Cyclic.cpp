#include <Cyclic.h>

byte CyclicBuffer::IncrementPtr(byte p,byte n){
  byte r;
  r=p+n;
  r&=CBUFFER_MASK;
  return(r);
}
byte CyclicBuffer::IncrementPtr(byte p){
  return(IncrementPtr(p,1));
}
void CyclicBuffer::SetAvail(){
  if(ReadAvailable()){
    Avail=WrPtr-RdPtr;
    Avail&=CBUFFER_MASK;
  } else {
    Avail=0;
  }
}
byte CyclicBuffer::BufferSize(){
  return(CBUFFER_SIZE);
}
bool CyclicBuffer::ReadAvailable(){
  return(WrPtr!=RdPtr);
}
byte CyclicBuffer::GetAvailableLen(){
  return(Avail);
}
bool CyclicBuffer::WriteFull(){
  return(RdPtr==IncrementPtr(WrPtr));
}
bool CyclicBuffer::WriteByte(byte b){
  if(WriteFull()){
    return(false);
  } else {
    MyBuffer[WrPtr]=b;
    WrPtr=IncrementPtr(WrPtr);
    SetAvail();
    return(true);
  } 
}
byte CyclicBuffer::ReadByte(){
  byte b=0;
  if(ReadAvailable()){
    b=MyBuffer[RdPtr];
    RdPtr=IncrementPtr(RdPtr);
    SetAvail();
  } else {
    b=MyBuffer[IncrementPtr(RdPtr,-1)];
  }
  return(b);
}
void CyclicBuffer::Flush(){
  WrPtr=RdPtr;
  Avail=0;//SetAvail()
}
void CyclicBuffer::Flush(byte p){
  byte i;
  if(p>0){
    RdPtr=((p<Avail)?IncrementPtr(RdPtr,p):WrPtr);
    SetAvail();
  }
}
byte CyclicBuffer::ViewByte(){
  return(MyBuffer[RdPtr]);
}
byte CyclicBuffer::ViewByte(byte p){
    return(MyBuffer[IncrementPtr(RdPtr,p)]);
}
CyclicBuffer::CyclicBuffer():RdPtr(0),WrPtr(0),Avail(0){}
