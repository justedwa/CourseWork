    XDEF drawscreen
    XREF display_string,drawDL,rtiCtrl,lastscreen,pstdtct,pestdetect
 
drawscreen:
    pshy   ;pushes registers
    pshx
    std lastscreen   ;address of screen being printed is stored in lastscreen
    jsr display_string ;displays string and sets draw delay flag for RTI
    bset rtiCtrl,#%00000010
RTILP:
	brset pstdtct,#%00000001,PST   ;if pest detect flag is set jump to subroutine
    ldx drawDL    ;loads drawDL
    bne RTILP     ;if it hasnt reached 0 loop
    bclr rtiCtrl,#%00000010   ;clear rti delay flag
    movw #10000,drawDL      ;reset the delay to 1s
    pulx     ;restore registers and return
    puly
    rts

PST:
	jsr pestdetect
	bra RTILP