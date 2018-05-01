    XDEF growth
    XREF seconds,wtrctrldisp,fertctrldisp,disp,gamestate,cropstats,fertDC,wtrDC
    
growth:
           ldd cropstats       ;checks the status of the crops
           brclr cropstats,#%00000001,endgrow   ;branches to the end of the crop is watered and fertilized
           brclr cropstats,#%00000010,endgrow
           brclr cropstats,#%00000011,endgrow
           ldd seconds     ;checks how many seconds have passed
           cpd #10
           ble endgrow     ;if less than 10 end
           ldaa cropstats
           cmpa #7        ;after 7 second growin
           lbeq growing
           cmpa #15       ;after 15 secs matured 
           lbeq matured
           cmpa #31       ;after 31 ready to harvest
           lbeq harvest
endgrow:
           RTS
           


growing:
           movb #00,seconds             ;resets second counter
           bclr cropstats,#%00000011 ;clears the fert/wtr status
           bset cropstats,#%00001000 ;sets flag showing crop is growing
           movb #'*',disp      ;replaces display with growing symbol
           movb #'*',disp+1
           movb #'*',disp+2
           movb #'*',disp+3
           movb #'*',disp+4
           movb #'*',disp+5
           movb #'*',disp+6
           movb #' ',disp+7
           movb #' ',disp+8
           movb #'*',disp+9
           movb #'*',disp+10
           movb #'*',disp+11
           movb #'*',disp+12
           movb #'*',disp+13
           movb #'*',disp+14
           movb #'*',disp+15
           movb #'*',disp+16
           movb #'*',disp+17
           movb #'*',disp+18
           movb #'*',disp+19
           movb #'*',disp+20
           movb #'*',disp+21
           movb #'*',disp+22
           movb #' ',disp+23
           movb #' ',disp+24
           movb #'*',disp+25
           movb #'*',disp+26
           movb #'*',disp+27
           movb #'*',disp+28
           movb #'*',disp+29
           movb #'*',disp+30
           movb #'*',disp+31
           movb #0,disp+32
           movb #3,gamestate         ;sets new growing gamestate
           movb #'1',fertctrldisp+29   ;resets fert/wtr ctrl display to default
           movb #'0',fertctrldisp+30
           movb #'%',fertctrldisp+31
           movb #' ',wtrctrldisp+28
           movb #'5',wtrctrldisp+29
           movb #'0',wtrctrldisp+30
           movb #'%',wtrctrldisp+31
           movb #30,wtrDC          ;resets duty cycle for DC motor
           movb #6,fertDC
           rts
matured:
           movb #00,seconds         ;same as above but sets matured flag
           bclr cropstats,#%00000011
           bset cropstats,#%00010000
           movb #'@',disp
           movb #'@',disp+1
           movb #'@',disp+2
           movb #'@',disp+3
           movb #'@',disp+4
           movb #'@',disp+5
           movb #'@',disp+6
           movb #' ',disp+7
           movb #' ',disp+8
           movb #'@',disp+9
           movb #'@',disp+10
           movb #'@',disp+11
           movb #'@',disp+12
           movb #'@',disp+13
           movb #'@',disp+14
           movb #'@',disp+15
           movb #'@',disp+16
           movb #'@',disp+17
           movb #'@',disp+18
           movb #'@',disp+19
           movb #'@',disp+20
           movb #'@',disp+21
           movb #'@',disp+22
           movb #' ',disp+23
           movb #' ',disp+24
           movb #'@',disp+25
           movb #'@',disp+26
           movb #'@',disp+27
           movb #'@',disp+28
           movb #'@',disp+29
           movb #'@',disp+30
           movb #'@',disp+31
           movb #0,disp+32
           movb #4,gamestate
           movb #30,wtrDC
           movb #6,fertDC
           movb #'1',fertctrldisp+29
           movb #'0',fertctrldisp+30
           movb #'%',fertctrldisp+31
           movb #' ',wtrctrldisp+28
           movb #'5',wtrctrldisp+29
           movb #'0',wtrctrldisp+30
           movb #'%',wtrctrldisp+31
           rts
harvest:   
           movb #30,wtrDC    ;resets duty cycle for DC motor
           movb #6,fertDC
           movb #'1',fertctrldisp+29
           movb #'0',fertctrldisp+30    ;resets fert/wtr ctrl display to default
           movb #'%',fertctrldisp+31
           movb #' ',wtrctrldisp+28
           movb #'5',wtrctrldisp+29
           movb #'0',wtrctrldisp+30
           movb #'%',wtrctrldisp+31
           movb #0,cropstats      ;resets crop status and sets final gamestate
           movb #5,gamestate
           rts