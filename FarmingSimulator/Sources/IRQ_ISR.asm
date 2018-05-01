   XDEF IRQ_ISR
   XREF rtiCtrl,sub1,sub2,display_string,drawDL,drawscreen,pesterr,temp,read_pot,pestdisp,port_p,menuNum,mainmenu
  
IRQ_ISR:
        ldaa rtiCtrl
        staa temp
        movb #%00100010,rtiCtrl
        cli
        ldd #pesterr
        movw #3000,drawDL
        jsr drawscreen
read:
        jsr read_pot
        tfr a,b
        clra
        ldx #25
        idiv
        xgdx
        cpd #10
        beq max
        addb #48
        stab pestdisp+16
        movb #'0',pestdisp+17
        movb #'%',pestdisp+18
        ldd #pestdisp
        jsr display_string
        brclr port_p,#%00100000,endpest
        bra read
max:
        movb #'M',pestdisp+16
        movb #'A',pestdisp+17
        movb #'X',pestdisp+18
        ldd #pestdisp
        jsr display_string
        bra read
        
endpest:
    ldaa menuNum
    beq mainMen1
    cmpa #2
    blt fertMen2
    ldd #sub2
    jsr drawscreen
    ldaa temp
    staa rtiCtrl
    rti
    
mainMen1:
    ldd #mainmenu
    jsr drawscreen
    ldaa temp
    staa rtiCtrl
    rti
    
fertMen2:
    ldd #sub1
    jsr drawscreen
    ldaa temp
    staa rtiCtrl
    rti
     