	XDEF statsmen
	XREF drawscreen,scoredisp,harvests,pests,fertwtr,drawDL

statsmen:         ;loads the ammount of harvests and then multiplies by 32
	ldab harvests   ;this gives the total # of plants harvested
	ldaa #32
	mul
    clra
	jsr hextoascii    ;converts hex value of plants harvested to ascii
	staa scoredisp+9  ;stores the ascii result into the score display
	stab scoredisp+10
	xgdx
	stab scoredisp+11
	clra
	ldab pests        ;does the same with the # of pests 
	jsr hextoascii
	stab scoredisp+22
	xgdx
	stab scoredisp+23
	clra
	ldab fertwtr     ;does the same with the # of times watered/fertilized
	jsr hextoascii
	staa scoredisp+29
	stab scoredisp+30
	xgdx
	stab scoredisp+31
	ldd #scoredisp
	movw #30000,drawDL   ;displays the screen with a 3 second delay
	jsr drawscreen
	rts
	
hextoascii:
	ldx #10          ;divides value by 10 to get first digit
	idiv
	xgdx
	pshb            ;stores result on the stack
	xgdx
	ldx #10         ;divides again to get second digit
	idiv            ; the remainder is the final digit
	xgdx            ;sticks third digit in x
	pshb
	pula           ;second digit in a
	pulb           ;first digit in b
	adda #48       ;adds #48 to convert all digits to ascii
	addb #48
	xgdx
	addb #48
	xgdx
	rts
	
	
	