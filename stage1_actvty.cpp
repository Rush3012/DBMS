#include "Buffer/StaticBuffer.h"
#include "Cache/OpenRelTable.h"
#include "Disk_Class/Disk.h"
#include "FrontendInterface/FrontendInterface.h"
#include <iostream>

int main(int argc, char *argv[]) {
  Disk disk_run;


  unsigned char buffer[BLOCK_SIZE];
  
  Disk::readBlock(buffer, 0);
 for(int i=0;i<BLOCK_SIZE;i++){
    std::cout<< (int)buffer[i];
    }  

  return 0;
}
