OUTPUT_ARCH( "riscv" )
ENTRY( _start )

MEMORY {
  EEPROM  (rx) : ORIGIN = 0x01000000, LENGTH = 8K
  RAM    (xrw) : ORIGIN = 0x02000000, LENGTH = 16K
}

_estack = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS {
  .text : {
    . = ALIGN(4);
    KEEP(*(.vectors))
    *(.text*)
    *(.rodata*)
    . = ALIGN(4);
  } > EEPROM

  .data :  {
    . = ALIGN(4);
    _sdata = .;
    *(.data*)
    . = ALIGN(4);
    _edata = .;
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
    *(.eh_frame)
    *(.comment)
    *(.riscv.attributes)
  }
}