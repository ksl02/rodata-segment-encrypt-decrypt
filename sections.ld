SECTIONS {
  . = SIZEOF_HEADERS;
  . = ALIGN(0x1000);
  .text : {
  START_TEXT = .;
	*(.text *.text.*)
	START_RODATA = .;
	*(.rodata .rodata.*)
	END_RODATA = .;
	}
  . = ALIGN(0x1000);
  .data : {
    *(.custom_data*)
    *(.data .data.*)
  }
  . = ALIGN(0x1000);
  .bss : {*(.bss .bss.*)}
  .dynamic : {*(.dynamic)}
}