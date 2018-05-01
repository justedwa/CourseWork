    XDEF newcrop
    XREF gamestate,Plowsound,Seedsound,loc,Counter2,cropstats,menuNum,rtiCtrl,STPcnt,PlantLED,PlowLED,drawDL,port_s,display_string,Keyboard,err2,err3,sub2,drawscreen,disp,__SEG_END_SSTACK
		
newcrop:
    movb #02,menuNum   ;sets current menu
    ldab gamestate
    cmpb #2          ;checks to see if crop is already planted
    lbge error1      ;if crop is already planted display error
klp:
    ldd #sub2       ;displays the planting screen
    jsr display_string
    jsr Keyboard    ;checks keyboard input and selects proper action
    cmpa #10
    lbeq plow
    cmpa #11
    beq plant
    bne klp
    
    
plant:
	 ldaa gamestate ;set gamestate,delay,sound file,LED pattern,Reset stepper counter,and set ctrl flags
	 cmpa #$01
	 lbne error2
	 movw #500,drawDL
	 movb #$02,gamestate
   ldaa #32
   ldx #Seedsound
   stx loc
   ldy #PlantLED
   ldx #disp
   movb #00,STPcnt
   bset rtiCtrl,#%01001000
   bset cropstats,#%00000100    ;set crop status as planted
   psha
     
pl2:
     ldab 1,Y+     ;loads next led pattern and displays
     stab port_s    
     ldaa #46
     staa 1,X+
     ldd #disp     ;stores . in current space then redraws screen
     jsr drawscreen
     movw #500,drawDL
     pula          ;pulls counter increments and stores
     deca
     psha
     beq endplant1   ;checks to see if entire field is planted
     cmpa #9
     beq space   ;if on space 9 or 25 branch to print spaces
     cmpa #25
     beq space
     bra pl2
endplant1:
     pula
     bclr rtiCtrl,#%01001000   ;resets flags and LEDs
     bclr port_s,$FF
     movw #$00,Counter2   ;resets counter
     rts  
space:
     ldab 1,Y+    ;keeps displaying LED pattern
     stab port_s
     ldaa #32     ;prints space then display screen again
     staa 1,X+
     ldd #disp
     movw #500,drawDL
     jsr drawscreen
     pula         ;decrements counter
     deca
     psha
     ldab 1,Y+    ;repeats
     stab port_s
     ldaa #32
     staa 1,X+
     ldd #disp
     movw #500,drawDL
     jsr drawscreen
     pula
     deca
     psha
   	 movw #500,drawDL
     bra pl2   ;return to printing .'s  
    
plow:
     movw #500,drawDL    ;sets delay, sounds file, display, LED pattern, and control flags
     ldaa #32
     ldx #Plowsound
     stx loc
     ldx #disp
     ldy #PlowLED
     bset rtiCtrl,#%01000100
     psha
pl1: 
     ldab 1,Y+     ;loads next LED pattern and displays
     stab port_s    
     ldaa #35      ;loads the # symbol
     staa 1,X+     ;stores a # in the next space in the field display
     ldd #disp     ;redraws field screen
     jsr drawscreen
     movw #500,drawDL
     pula    ;pulls counter off the stack
     deca    ;decrements 
     psha    ;pushes counter back on the stack
     beq endplow2 ;if the counter has reached 0 end plowing
     cmpa #9     ;if on space 9 print spaces 
     beq space2
     cmpa #25    ;if on space 25 print spaces
     beq space2
     bra pl1
     
endplow2:
     pula     
     bclr rtiCtrl,#%01000100
     bclr port_s,$FF
     movb #$01,gamestate
     movw #$00,Counter2
     lbra klp
space2:
     ldab 1,Y+   ;keeps displaying LED pattern
     stab port_s
     ldaa #32
     staa 1,X+    ;loads and stores space then redraws screen
     ldd #disp
     movw #500,drawDL
     jsr drawscreen
     pula
     deca
     psha
     ldab 1,Y+    ;repeat for the next space
     stab port_s
     ldaa #32
     staa 1,X+
     ldd #disp
     movw #500,drawDL
     jsr drawscreen
     pula
     deca
     psha
     movw #500,drawDL
     bra pl1         ;return to printing screen
error1:
    ldd #err2        ;load and printer error then return
    jsr drawscreen
    rts
error2:          ;load and print error and return (not plowed)
	ldd #err3
	jsr drawscreen
	jmp klp
	