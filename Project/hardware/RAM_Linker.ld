
MEMORY {
  RAM (xrw) : ORIGIN = 0x02000000, LENGTH = 16K
}

_estack = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS {
  .text : {
    . = ALIGN(4);
    KEEP(*(.vectors))
    *(.text*)
    *(.rodata*)
    . = ALIGN(4);
  } > RAM

  .data : {
    . = ALIGN(4);
    *(.data*)
    . = ALIGN(4);
  } > RAM

  .bss : {
    . = ALIGN(4);
    _sbss = .;
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } > RAM
  
  /DISCARD/ : {
    *(.riscv.attributes)
    *(.comment)
    *(.note*)
    *(.eh_frame)
  }
}