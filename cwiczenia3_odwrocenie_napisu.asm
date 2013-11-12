.cseg
.org 0

main:
	ldi r16, high(ramend)
	out SPH, r16
	ldi r16, low(ramend)
	out SPL, r16
	ldi r17, 15
	ldi r18, 18
	ldi XH, 5
	ldi ZL, 10

	call Odwroc_napis

	jmp main

Odwroc_napis:
	;zachowanie orginalnych wartosci rejestru
	push r16
	push r17
	push r18
	.def dlugosc = R16
	.def tmp = R17
	clr dlugosc

	Initialize_RAM:
		;zachowanie orginalnych wartosci rejestru c.d
		push ZH
		push ZL
		push XH
		push XL
		ldi ZH, high(Flash_Table_Initializer << 1)
		ldi ZL, low(Flash_Table_Initializer << 1)
		ldi XH, high(MyTable)
		ldi XL, low(MyTable)
	Initialize_RAM_Loop: ;sciaganie napisu z flasha
		lpm tmp, Z+   
		cpi tmp, 0
		breq reverse_string
		st X+, tmp
		inc dlugosc  
		jmp Initialize_RAM_Loop

	reverse_string:
		.def tmp2 = r18		
		clr tmp											
		mov tmp2, dlugosc
		na_stos:
			ld tmp, -X		
			push tmp	
			dec tmp2
			cpi tmp2, 0
			brne na_stos		
			add XL, dlugosc
		wstaw:
			pop tmp
			ST -X, tmp
			dec dlugosc
			cpi dlugosc, 0
			brne wstaw

	pop XL
	pop XH
	pop ZL
	pop ZH
	pop r18
	pop r17
	pop r16

	ret


.equ TABLE_SIZE = 255

.dseg
MyTable:
   .byte TABLE_SIZE   ; Declare storage space to hold the
                      ; coefficient table


Flash_Table_Initializer:
; This table contains the initial value that should always be
; used for the coefficient table on start-up.  The RAM copy
; of the table will be initialized based on this table.
my_string: .db "H e",0
