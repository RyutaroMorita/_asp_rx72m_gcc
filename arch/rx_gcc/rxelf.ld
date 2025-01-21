MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512K
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 64K
}

PROVIDE(hardware_init_hook = 0);
PROVIDE(software_init_hook = 0);
PROVIDE(software_term_hook = 0);
/*STARTUP(start.o)*/

SECTIONS
{

	.text :
	{
		__text = .;
		*(.vector)
		*(.text)
		*(.text.*)
		*(P)
	} > FLASH
	_etext = .;
	PROVIDE(etext = .);

	.rodata :
	{
		*(.rodata)
		*(.rodata.*)
		*(C_1)
		*(C_2)
		*(C)
		*(C$VECT)
	} > FLASH

	__exidx_start = .;
	__exidx_end = .;

	__idata_start = .;
	.data : 
	{
		__data_start = .;
		*(.data)
		*(.data.*)
		*(D)
		*(D_1)
		*(D_2)
	} > SRAM AT> FLASH
	__idata_end = __idata_start + SIZEOF(.data);
	__idata_size = SIZEOF(.data);
	_edata = .;
	PROVIDE(edata = .);

	. = ALIGN(4);

	.bss : 
	{
		__bss_start  = .;
		*(.bss)
		*(COMMON)
		*(B)
		*(B_1)
		*(B_2)
		*(SI)
	} > SRAM
	. = ALIGN(4);
	_end = .;
	__bss_end = .;
	PROVIDE(end = .);

    .fvectors 0xFFFFFF80 : {
		*(FVECT)
    }
}
