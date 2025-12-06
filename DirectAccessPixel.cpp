#include<bios.h> //Needed for the REGS structure

void main()
{
  unsigned char far* vgaspace = (unsigned char far*) 0xA0000000;
  
  union REGS regs;
  regs.h.ah = 0;
  regs.h.al = 0x13;
  int86(0x10, &regs, &regs);
  
  vgaspace[0x200] = 0x44;
}
