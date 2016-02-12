SECTIONS 
{
	. = 0x7c00;
	.boot :
	AT (0x00000000)
	{	
		start.o(.boot)
	}
	.magic :
	AT (0x000001fe)		
	{
		SHORT(0xaa55);
	}
	. = 0x1000;
	.text :
	AT (0x00000200)
	{
		_stext = .;
		*(.text*)
		_etext = .;
	}
	.data :
	AT(LOADADDR(.text)+SIZEOF(.text))
	{
		*(.data*)
	}
	.rodata :
	AT (LOADADDR(.data)+SIZEOF(.data))
	{
		*(.rodata*)	
	}

	.bss :
	{
		*(.bss*)
	}
	

	_sload_src = LOADADDR(.text);
	_eload_src = LOADADDR(.rodata)+SIZEOF(.rodata);
	_sload_dst = ADDR(.text);
	



}
