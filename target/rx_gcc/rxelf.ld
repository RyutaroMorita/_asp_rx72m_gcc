MEMORY
{
    FLASH (rx) : ORIGIN = 0x08003000, LENGTH = 512K-0x3000
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 64K
}

PROVIDE(_hardware_init_hook = 0);
PROVIDE(_software_init_hook = 0);
PROVIDE(_software_term_hook = 0);
STARTUP(start.o)

SECTIONS
{
	.text :
	{
		__text = .;
		*(.vector)
		*(.text)
		*(.text.*)
	} > FLASH
	_etext = .;
	PROVIDE(etext = .);

	.rodata :
	{
		*(.rodata)
		*(.rodata.*)
	} > FLASH

	__idata_start = .;
	.data : AT (__idata_start)
	{
		__data_start = .;
		*(vtable)
		*(.data)
		*(.data.*)
	} > SRAM
	__idata_end = __idata_start + SIZEOF(.data);
	_edata = .;
	PROVIDE(edata = .);

	. = ALIGN(4);

	.bss :
	{
		__bss_start  = .;
		*(.bss)
		*(COMMON)
		. = ALIGN(4);
	} > SRAM
	. = ALIGN(4);
	_end = .;
	__bss_end = .;
	PROVIDE(end = .);
}
