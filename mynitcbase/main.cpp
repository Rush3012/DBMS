#include "Buffer/StaticBuffer.h"
#include "Cache/OpenRelTable.h"
#include "Disk_Class/Disk.h"
#include "FrontendInterface/FrontendInterface.h"
#include <bits/stdc++.h>
#include <cstdlib>

int main(int argc, char *argv[]) {
  Disk disk_run;
  StaticBuffer buffer;
  OpenRelTable cache;

  /*
  for i = 0 and i = 1 (i.e RELCAT_RELID and ATTRCAT_RELID)
 
      get the relation catalog entry using RelCacheTable::getRelCatEntry()
      printf("Relation: %s\n", relname);

      for j = 0 to numAttrs of the relation - 1
          get the attribute catalog entry for (rel-id i, attribute offset j)
           in attrCatEntry using AttrCacheTable::getAttrCatEntry()

          printf("  %s: %s\n", attrName, attrType);
  */

  /*for(int i=0;i<=3;i++){
  RelCatEntry relCatBuf;
   RelCacheTable::getRelCatEntry(i,&relCatBuf);
   printf("Relation:%s\n",relCatBuf.relName);
  
  for(int j=0;j<relCatBuf.numAttrs;j++){
  AttrCatEntry attrcatBuf;
  AttrCacheTable::getAttrCatEntry(i,j,&attrcatBuf);
  const char *attrType = attrcatBuf.attrType == NUMBER? "NUM":"STR";
  printf("  %s: %s\n", attrcatBuf.attrName,attrType);
   }
  }    
  return 0;
  */
  

  return FrontendInterface::handleFrontend(argc, argv);

}
