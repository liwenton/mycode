SECTIONS
{
    . = 0x23008000;
    
    .text : 
    {
        start.o (.text);
        shell.o (.text);
        cmd.o  (.text);
        * (.text);
    }

    .data :
    {
        * (.data);
    }

    __bss_start = .;
    .bss :
    {
        * (.bss);
    }
    __bss_end = .;
    __end = .;
}




