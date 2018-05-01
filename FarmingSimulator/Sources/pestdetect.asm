	XDEF pestdetect
	XREF lastscreen,tON,loc,Alarm,rtiCtrl,display_string,read_pot,pestdisp,pstdtct,port_s,pests,drawDL,pesterr,drawscreen,pestctrl,port_t,port_p
	
pestdetect:
		ldd loc      ;loads the previous sound being played
		pshd	       ;pushes that value onto the stack for use after subroutine
		ldaa rtiCtrl ;loads ctrl flags and pushes to be restored after subroutine
		psha
		ldx #Alarm    ;loads alarm sound 
		stx loc
		movb #00,rtiCtrl   ;resets rtiCtrl
		bset rtiCtrl,#%01100000   ;sets sound and pest flags
		ldd drawDL    ;loads and saves drawDL for when returning from subroutine
		pshd
		movb #00,pstdtct ;resets pstdtct
		ldd lastscreen   ;pushes previous screen on stack for later
		pshd
		inc pests
		ldaa #$FF       ;turns all LEDs on
		staa port_s
		ldd #pesterr
		movw #30000,drawDL   ;displays pest screen for 3 seconds
		jsr drawscreen
		movb #00,tON         ;sets duty cycle for DC motor to 0
		bset rtiCtrl,#%00000001  ;sets dc motor flag for RTI      
read:
		ldx loc      ;loads the address of current location in sound array
		ldaa 0,X  ;loads the value at the address
		cmpa #0   ;checks if it is the terminator
		beq AlarmRst  ;if it is the terminator branch to reset array
        jsr read_pot   ;reads potentiometer
        clra       ;clears a
        ldx #25    ;divides by 25 to break into 10
        idiv
        xgdx       ;loads quotient into d
        cpd #10    ;compairs quotient to 10 (100%)
        pshb       ;pushes the quotient onto the stack
        beq max    ;checks to see if duty cycle is max
        addb #48   ;adds 48 to convert to ascii
        stab pestdisp+16      ;stores percentage (duty cycle) into pest display
        movb #'0',pestdisp+17
        movb #'%',pestdisp+18
        ldd #pestdisp      ;displays pest display screen
        jsr display_string
        ldaa port_s        ;flashes LEDs
        eora #$FF
        staa port_s
        pulb               ;pulls new duty cycle of of stack
        ldaa #6            ;multiplies by 6 to get proper value for tON
        mul
        stab tON           ;sets new tON
        brclr port_p,#%00100000,endpest  ;checks pushbutton if pressed exit
        bra read
max:
        movb #'M',pestdisp+16   ;if duty cycle is max display MAX
        movb #'A',pestdisp+17
        movb #'X',pestdisp+18
        ldd #pestdisp
        jsr display_string
        bra read
AlarmRst:
		ldx #Alarm           ;loads the address of alarm and store in loc
		stx loc              ;this resets the sound 
		bset rtiCtrl,#%01000000  ;set the sound flag again
		bra read      
endpest:
	brclr port_p,#%00100000,endpest   ;debounce pushbutton
	bclr port_s,#$FF        ;clear LEDs
	puld                    ;pull last screen off of stack
	jsr display_string      ;display last menu
	puld
	std drawDL              ;pull delay off of stack and restore
	pula
	staa rtiCtrl            ;pull control flag status and restore
	puld
	std loc                 ;pull last sound location and restore
	bclr port_t,#%00001000  ;turn off DC motor
	rts	                    ;return