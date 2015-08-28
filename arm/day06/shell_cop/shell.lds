SECTIONS
{
    . = 0x23008000;
 
    .text :
    {
      * (.text)
    }
  
    .data :
    {
      * (.data);
    }
  
    .bss :
    {
      * (.bss);
    }
   
  __end= . ;
}
