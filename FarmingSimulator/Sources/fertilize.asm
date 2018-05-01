    XDEF fertilize
    XREF gamestate,loc,Sprinklersound,Fertilizesound,fertwtr,port_s,cropstats,fertDC,menuNum,wtrDC,drawDL,rtiCtrl,port_t,tON,fertscreen,wtrscreen,display_string,Keyboard,err1,sub1,drawscreen
		
fertilize:
    movb #01,menuNum    ;sets the current menu to fertilizer
    ldab gamestate      ;checks to see if crop is planted
    cmpb #$02
    blt error           ;if it is not planted throw and error screen
    ldd #sub1           ;otherwise display fertilizer/water screen
    jsr display_string
fl1:
    jsr Keyboard   ;scans for user selection
    cmpa #10
    beq fert      ;if a is pressed fertilize
    cmpa #11
    beq wtr       ;if b is pressed water
    rts



fert:
	ldaa fertDC          ;loads the duty cycle for fertilizer
	staa tON             ;stores value in tON
	ldx #Fertilizesound   ;loads the fertilizer sound addr
	stx loc
	bset rtiCtrl,#%11000001  ;sets flags needed to turn on dc motor sound and leds
	movw #20000,drawDL     ;set screen delay to 2 secs
	ldd #fertscreen        ;loads and displays fert screen
    jsr drawscreen
    bclr port_t,#%00001000  ;turns off motor and clears flags used
    bclr rtiCtrl,#%11000001
    bset cropstats,#%00000001 ;set the crop status to show crop was fertilized
    movb #$00,port_s   ;turns of LEDs
    inc fertwtr        ;increments fert/wtr counter
    rts

wtr:
    ldaa wtrDC          ;same as above but using variables for watering
    staa tON
	ldx #Sprinklersound
	stx loc
   	bset rtiCtrl,#%01000001
   	movw #20000,drawDL
    ldd #wtrscreen
   	jsr drawscreen
    bclr rtiCtrl,#%11000001
   	bclr port_t,#%00001000
   	bset cropstats,#%00000010
   	movb #$00,port_s
   	inc fertwtr
    rts
    
error:
    ldd #err1     ;loads and displays error screen
    jsr drawscreen
    rts