  XDEF harvesting
  XREF gamestate,loc,Harvestsound,Counter2,harvests,wtrctrldisp,fertctrldisp,disp,seconds,timer,rtiCtrl,drawscreen,drawDL,harv

harvesting:
     ldx #Harvestsound   ;load and set flags for harvest sound
     stx loc
     ldd #harv        ;load screen that says Harvesting
     jsr drawscreen
     ldy #32          ;load length of field array 
     ldx #disp        ;load the field array address
     bset rtiCtrl,#%01010000  ;set harvesting ctrl flag and sound ctrl flag
hv1:
     ldaa #32          ;loads blank space
     staa 1,X+         ;stores blank space over current space in crop display
     ldd #disp
     movw #2500,drawDL  ;redraw screen and set delay
     jsr drawscreen
     dey           ;decrement y
     bne hv1       ;check to see if entire field has been harvested
     bclr rtiCtrl,#%00010000      ;resets variable and ctrl flags to new game state
     movb #$00,gamestate
     movw #$00,timer
     movw #$00,seconds
     movb #$00,rtiCtrl
     movw #$00,Counter2
     movb #'1',fertctrldisp+29   ;resets fert/wtr ctrl display to default
     movb #'0',fertctrldisp+30
     movb #'%',fertctrldisp+31
     movb #' ',wtrctrldisp+28
     movb #'5',wtrctrldisp+29
     movb #'0',wtrctrldisp+30
     movb #'%',wtrctrldisp+31
     inc harvests    ;increments the number of times harvested
     rts
     
    