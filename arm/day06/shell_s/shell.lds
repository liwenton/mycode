SECTIONS
{
    . = 0x23000000;
 
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
