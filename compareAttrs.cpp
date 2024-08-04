int compareAttrs(union Attribute attr1, union Attribute attr2, int attrType) {

    double diff;
     if (attrType == STRING){
      diff = strcmp(attr1.sval, attr2.sval);
     }
     else{
       diff = attr1.nval - attr2.nval;
         }
    
    if (diff > 0)  return 1;
    if (diff < 0)  return -1;
    if (diff = 0)  return 0;
  
}
