#include "Buffer/StaticBuffer.h"
#include "Cache/OpenRelTable.h"
#include "Disk_Class/Disk.h"
#include "FrontendInterface/FrontendInterface.h"
#include <bits/stdc++.h>



void displaying_relations(){ 
// create objects for the relation catalog and attribute catalog
  RecBuffer relCatBuffer(RELCAT_BLOCK);
  RecBuffer attrCatBuffer(ATTRCAT_BLOCK);

  HeadInfo relCatHeader;
  HeadInfo attrCatHeader;

  // load the headers of both the blocks into relCatHeader and attrCatHeader.
  // (we will implement these functions later)
  relCatBuffer.getHeader(&relCatHeader);
  attrCatBuffer.getHeader(&attrCatHeader);
  int attrCatSlotIndex=0;

  for (int i=0;i<relCatHeader.numEntries;i++) {

    Attribute relCatRecord[RELCAT_NO_ATTRS]; // will store the record from the relation catalog

    relCatBuffer.getRecord(relCatRecord, i);

    printf("Relation: %s\n", relCatRecord[RELCAT_REL_NAME_INDEX].sVal);

    for (int j=0;j<relCatRecord[RELCAT_NO_ATTRIBUTES_INDEX].nVal;j++,attrCatSlotIndex++) {
        	Attribute attrCatRecord[ATTRCAT_NO_ATTRS];
        	attrCatBuffer.getRecord(attrCatRecord, attrCatSlotIndex);
      

      if (strcmp(attrCatRecord[ATTRCAT_REL_NAME_INDEX].sVal, relCatRecord[RELCAT_REL_NAME_INDEX].sVal) == 0) {
        const char *attrType = attrCatRecord[ATTRCAT_ATTR_TYPE_INDEX].nVal == NUMBER ? "NUM" : "STR";
        printf("  %s: %s\n", attrCatRecord[ATTRCAT_ATTR_NAME_INDEX].sVal, attrType);
      }
    
    if (attrCatSlotIndex == attrCatHeader.numSlots-1) {
				attrCatSlotIndex = -1; 
				attrCatBuffer = RecBuffer (attrCatHeader.rblock);
				attrCatBuffer.getHeader(&attrCatHeader);
			}
	}
    printf("\n");
  }
}
void updateAttrname(const char* relname, const char* oldattrname, const char* newattrname){
   RecBuffer attrCatBuffer(ATTRCAT_BLOCK);
   HeadInfo attrCatHeader;
   attrCatBuffer.getHeader(&attrCatHeader);
   for(int i=0;i<attrCatHeader.numEntries;i++){
      Attribute attrCatRecord[ATTRCAT_NO_ATTRS];
      attrCatBuffer.getRecord(attrCatRecord, i);
      if(strcmp(attrCatRecord[ATTRCAT_REL_NAME_INDEX].sVal,relname)==0 &&         strcmp(attrCatRecord[ATTRCAT_ATTR_NAME_INDEX].sVal,oldattrname)==0){
      strcpy(attrCatRecord[ATTRCAT_ATTR_NAME_INDEX].sVal, newattrname);
      attrCatBuffer.setRecord(attrCatRecord, i);
      break;
      }
      // reaching at the end of the block, and thus loading
		// the next block and setting the attrCatHeader & recIndex
		if (i == attrCatHeader.numSlots-1) {
			i = -1;
			attrCatBuffer = RecBuffer (attrCatHeader.rblock);
			attrCatBuffer.getHeader(&attrCatHeader);
		}

   }
   
}
int main(int argc, char *argv[]) {
  Disk disk_run;
  //printing the contents
  displaying_relations();
  //updating the attribute name
  updateAttrname("Students","Class","Batch");
  // again displaying after upadting
  displaying_relations();
    return 0;
}
