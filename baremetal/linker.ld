ENTRY(_start)

MEMORY
{
  IRAM (rx)  : ORIGIN = 0x4037C000, LENGTH = 0x00080000
  DRAM (rw)  : ORIGIN = 0x3FC80000, LENGTH = 0x00050000
}

SECTIONS
{
  .text : {
    *(.init)
    *(.text .text.*)
    *(.rodata .rodata.*)
  } > IRAM

  .data : { *(.data .data.*) } > DRAM AT > IRAM

  .bss (NOLOAD) : {
    *(.bss .bss.*)
    *(COMMON)
  } > DRAM

  . = ORIGIN(DRAM) + LENGTH(DRAM);
  _stack_top = .;
}
