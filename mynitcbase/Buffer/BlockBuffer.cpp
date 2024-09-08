#include "BlockBuffer.h"

#include <cstdlib>
#include <cstring>
// the declarations for these functions can be found in "BlockBuffer.h"

BlockBuffer::BlockBuffer(int blockNum) {
  // initialise this.blockNum with the argument
  this->blockNum=blockNum;
}

// calls the parent class constructor
RecBuffer::RecBuffer(int blockNum) : BlockBuffer::BlockBuffer(blockNum) {}

// load the block header into the argument pointer


int BlockBuffer::getHeader(struct HeadInfo *head) {
  unsigned char *bufferPtr;
  int ret = loadBlockAndGetBufferPtr(&bufferPtr);
  if (ret != SUCCESS) {
    return ret;   // return any errors that might have occured in the process
  }
  // read the block at this.blockNum into the buffer
  unsigned char buffer[BLOCK_SIZE];
  Disk::readBlock(buffer,this->blockNum);
  // populate the numEntries, numAttrs and numSlots fields in *head
  memcpy(&head->numSlots, buffer + 24, 4);
  memcpy(&head->numEntries, buffer + 16, 4);
  memcpy(&head->numAttrs, buffer + 20, 4);
  memcpy(&head->rblock, buffer+ 12, 4);
  memcpy(&head->lblock, buffer + 8, 4);
  memcpy(&head->pblock, buffer + 4, 4);
  
  return SUCCESS;
}

// load the record at slotNum into the argument pointer


int RecBuffer::getRecord(union Attribute *rec, int slotNum) {
   unsigned char *bufferPtr;
    int ret = loadBlockAndGetBufferPtr(&bufferPtr);
    if (ret != SUCCESS)
    {
        return ret;
    }
  
  
  struct HeadInfo head;

  // get the header using this.getHeader() function
  BlockBuffer::getHeader(&head);
  int attrCount = head.numAttrs;
  int slotCount = head.numSlots;

  // read the block at this.blockNum into a buffer
   unsigned char buffer[BLOCK_SIZE];
  Disk::readBlock(buffer,this->blockNum);
  /* record at slotNum will be at offset HEADER_SIZE + slotMapSize + (recordSize * slotNum)
     - each record will have size attrCount * ATTR_SIZE
     - slotMap will be of size slotCount
  */
  int recordSize = attrCount * ATTR_SIZE;
  unsigned char *slotPointer = buffer + ( 32 + slotCount + (recordSize * slotNum));

  // load the record into the rec data structure
  memcpy(rec, slotPointer, recordSize);

  return SUCCESS;
}


int RecBuffer::setRecord(union Attribute *rec, int slotNum) {
    unsigned char *bufferPtr;
   
    /* get the header of the block using the getHeader() function */
    struct HeadInfo head;
    BlockBuffer::getHeader(&head);
    // get number of attributes in the block.
    int attrCount = head.numAttrs;
    // get the number of slots in the block.
    int slotCount = head.numSlots;
     unsigned char buffer[BLOCK_SIZE];
     Disk::readBlock(buffer,this->blockNum);
     int recordSize = attrCount * ATTR_SIZE;
     unsigned char *slotPointer = buffer + ( 32 + slotCount + (recordSize * slotNum));
  // load the record into the rec data structure
      memcpy(slotPointer,rec, recordSize);
      Disk::writeBlock(buffer,this->blockNum);
     return SUCCESS;
}



int BlockBuffer::loadBlockAndGetBufferPtr(unsigned char **buffPtr) {
  // check whether the block is already present in the buffer using StaticBuffer.getBufferNum()
  int bufferNum = StaticBuffer::getBufferNum(this->blockNum);

  if (bufferNum == E_BLOCKNOTINBUFFER) {
    bufferNum = StaticBuffer::getFreeBuffer(this->blockNum);

    if (bufferNum == E_OUTOFBOUND) {
      return E_OUTOFBOUND;
    }

    Disk::readBlock(StaticBuffer::blocks[bufferNum], this->blockNum);
  }

  // store the pointer to this buffer (blocks[bufferNum]) in *buffPtr
  *buffPtr = StaticBuffer::blocks[bufferNum];

  return SUCCESS;
}
/* used to get the slotmap from a record block
NOTE: this function expects the caller to allocate memory for `*slotMap`
*/
int RecBuffer::getSlotMap(unsigned char *slotMap) {
  unsigned char *bufferPtr;

  // get the starting address of the buffer containing the block using loadBlockAndGetBufferPtr().
  int ret = loadBlockAndGetBufferPtr(&bufferPtr);
  if (ret != SUCCESS) {
    return ret;
  }

  struct HeadInfo head;
  // get the header of the block using getHeader() function
  BlockBuffer::getHeader(&head);
  int slotCount = head.numSlots;/* number of slots in block from header */;

  // get a pointer to the beginning of the slotmap in memory by offsetting HEADER_SIZE
  unsigned char *slotMapInBuffer = bufferPtr + HEADER_SIZE;

  // copy the values from `slotMapInBuffer` to `slotMap` (size is `slotCount`)
  memcpy(slotMap,slotMapInBuffer,slotCount);

  return SUCCESS;
}

int compareAttrs(union Attribute attr1, union Attribute attr2, int attrType) {

    double diff;
    if (attrType == STRING)
    {
        diff = strcmp(attr1.sVal, attr2.sVal);
    }
    else
    {
    diff = attr1.nVal - attr2.nVal;
    }
    
    if (diff > 0)  
    {
    return 1;
    }
    else if (diff < 0) 
    {
    return -1;
    }
    else 
    { 
    return 0;
    }
    return 0;
    
}
