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

  for(int i=0;i<=1;i++){
  RelCatEntry relCatBuf;
   RelCacheTable::getRelCatEntry(i,&relCatBuf);
   printf("Relation:%s\n",relcatBuf.relname);
  }
  for(int j=0;j<relCatBuf.numAttrs-1;j++){
  AttrCatEntry attrcatBuf;
  AttrCacheTable::getAttrCatEntry(i,j,attrcatBuf);
  printf("  %s: %s\n", attrcatBuf.attrName, attrcatBuf.attrType);
  }
  return 0;
}
