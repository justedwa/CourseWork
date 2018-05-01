    xdef    pushb
    xref    gamestate,lastscreen,port_t,mainmenu,port_p,start,harvesting,sub1,sub2,menuNum,disp,drawscreen,tth,display_string,tth2,Keyboard


pushb: 
    
    pshd
    ldaa gamestate
    cmpa #5
    beq fin 
    ldd #disp ;gamestate1-4
    jsr drawscreen
    brset port_t,#%00000001,lastsscreen
    brset port_t,#%00000010,lastsscreen
    ldaa menuNum
    beq mainMenu
    cmpa #2
    blt fertMenu
    ldd #sub2
    jsr drawscreen
    puld
    rts
mainMenu:
    ldd #mainmenu
    jsr drawscreen
    puld
    rts
fertMenu:
    ldd #sub1
    jsr drawscreen
    puld
    rts
lastsscreen:
    ldd lastscreen
    jsr drawscreen
    puld
    rts
    
fin:    ;gamestate5
    ldd #tth
    jsr drawscreen
    ldd #tth2
    jsr drawscreen
wait:
    brset port_p,#%00100000,wait
    jsr harvesting
    ldd #mainmenu
    jsr drawscreen
    puld
    leas -4,sp
    jmp start

    
