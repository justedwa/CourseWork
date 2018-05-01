	XDEF flowctrl
	XREF port_t,ferterr,lastscreen,err1,gamestate,wtrerr,wtrdisp,fertdisp,drawDL,cropstats,exitflg,drawscreen,Keyboard,SWstatus,fertDC,wtrDC,menuNum,sub1,sub2,mainmenu,display_string,wtrctrldisp,fertctrldisp,
	 
	
flowctrl:
	movb #$00,SWstatus      ;sets switch status flag to 0
	movb #$01,exitflg       ;sets exit flg to 0 this is used in keyboard subroutine
	ldaa gamestate          ;checks gamestate to see if crop is planted
	cmpa #02
	bge contflw
	ldd #err1               ;if no crop is planted throw an error
	jsr drawscreen
	lbra endflow
contflw:
	ldaa port_t         ;checks which switch is set and branches accordingly
	anda #%00000011
	cmpa #$01
	beq wtrctrl
	cmpa #$02
	lbeq fertctrl
	lbra endflow
	
	
wtrctrl:
    ldaa cropstats    ;checks the status of the crop to see if it hasnt been watered
    anda #%00000010
    beq notwatered
    ldd #wtrerr      ;if the crop is watered throw error and exit
    jsr drawscreen
    lbra endflow
notwatered:
    ldd #wtrdisp     ;draw the crop needs watered screen
    jsr drawscreen
wtrlp:
	ldd #wtrctrldisp    ;draw the water flow control screen and set delay
	movw #2500,drawDL
	std lastscreen
	jsr drawscreen
	ldaa port_t       ;checks to see if the switch is still on if not exit
    bita #%00000001
    lbeq endflow
	jsr Keyboard     ;scans the keyboard to see if flow is increased or decreased
	cmpa #10
	beq increase
	cmpa #11         ;branches if decrease or increase flow
	beq decrease
	ldaa port_t
	bra wtrlp
	
increase:
	clra         ;clears D register
	clrb         
	ldab wtrDC   ;loads current water duty cycle
	cmpb #60     ;compairs to max value if not max then increment
	bne inc
	movb #' ',wtrctrldisp+28   ;if at max value display MAX
    movb #'M',wtrctrldisp+29
    movb #'A',wtrctrldisp+30
    movb #'X',wtrctrldisp+31
    bra wtrlp    
inc:
	addb #6       ;add 6 to waterDC (10%)
	stab wtrDC    ;store new waterDC
	ldx #6        ;divide b by 6 to find percentage
	idiv
	clra          ;clear remainder
	clrb
	xgdx          ;move quotient to D
	addb #48      ;add 48 to b to get ascii
	ldaa wtrDC
	cmpa #60      ;check if max
	beq maxi
	movb #' ',wtrctrldisp+28 ;store new percentage in display
	stab wtrctrldisp+29
	movb #'0',wtrctrldisp+30
	movb #'%',wtrctrldisp+31
	lbra wtrlp
maxi:
	movb #'1',wtrctrldisp+28 ;move 100% to display
	movb #'0',wtrctrldisp+29
	movb #'0',wtrctrldisp+30	
	movb #'%',wtrctrldisp+31
	lbra wtrlp
	

decrease:
	clra      ;clear D
	clrb
	ldab wtrDC  ;check if wtrDC is at its minimum, 30
	cmpb #30
	bne dec   ;if it is not minimum decrement
    movb #'M',wtrctrldisp+29
    movb #'I',wtrctrldisp+30   ;if min display MIN on display
    movb #'N',wtrctrldisp+31
    lbra wtrlp    
dec:
	subb #6     ;subtract 6 (10%)
	stab wtrDC  ;store new value
	ldx #6      ;divide by 6 to obtain percentage
	idiv
	clra       ;clear d
	clrb
	xgdx       ;put quotient in d
	addb #48   ;add 48 to turn into ascii
	movb #' ',wtrctrldisp+28             ;store new percentage
	stab wtrctrldisp+29
	movb #'0',wtrctrldisp+30
	movb #'%',wtrctrldisp+31
	lbra wtrlp
	

fertctrl:            ;same as above but utilizing fertilize DC
    ldaa cropstats   ;min 6 max 30
    anda #%00000001
    beq notfert
    ldd #ferterr
    jsr drawscreen
    lbra endflow
notfert:
    ldd #fertdisp
    jsr drawscreen
fertlp:
	ldd #fertctrldisp
	std lastscreen
	movw #2500,drawDL
	jsr drawscreen
	ldaa port_t
    bita #%00000010
    lbeq endflow
	jsr Keyboard
	cmpa #10
	beq increase1
	cmpa #11
	beq decrease1
	ldaa port_t
	;brclr port_t,#%00000011,endflow
	bra fertlp

increase1:
	clra
	clrb
	ldab fertDC
	cmpb #30
	bne inc1
    movb #'M',fertctrldisp+29
    movb #'A',fertctrldisp+30
    movb #'X',fertctrldisp+31
    bra fertlp    
inc1:
	addb #6
	stab fertDC
	ldx #6
	idiv
	clra
	clrb
	xgdx
	addb #48
	stab fertctrldisp+29
	movb #'0',fertctrldisp+30
	movb #'%',fertctrldisp+31
	bra fertlp
	
	

decrease1:
	clra
	clrb
	ldab fertDC
	cmpb #6
	bne dec1
    movb #'M',wtrctrldisp+29
    movb #'I',wtrctrldisp+30
    movb #'N',wtrctrldisp+31
    lbra fertlp    
dec1:
	subb #6
	stab fertDC
	ldx #6
	idiv
	clra
	clrb
	xgdx
	addb #48
	stab fertctrldisp+29
	movb #'0',fertctrldisp+30
	movb #'%',fertctrldisp+31
	lbra fertlp
	

endflow:
	movb #00,exitflg   ;resets exit flag and SW status
	ldaa menuNum       ;finds previous menu before entering flow control
    beq mainMen      ;prints previous menu and returns
    cmpa #2
    blt fertMen
    ldd #sub2
    jsr drawscreen
    movb #$01,SWstatus
    rts
    
mainMen:
    ldd #mainmenu
    jsr drawscreen
    movb #$01,SWstatus
    rts
    
fertMen:
    ldd #sub1
    jsr drawscreen
    movb #$01,SWstatus
    rts