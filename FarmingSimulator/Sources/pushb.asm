    xdef    pushb
    xref    gamestate,lastscreen,port_t,mainmenu,port_p,start,harvesting,sub1,sub2,menuNum,disp,drawscreen,tth,display_string,tth2,Keyboard


pushb: 
    
    pshd  ;saves register
    ldaa gamestate   ;checks gamestate to see if its time to harvest
    cmpa #5
    beq fin    ;branches if harvest time
    ldd #disp ;gamestate1-4
    jsr drawscreen   ;otherwise display the current field status
    brset port_t,#%00000001,lastsscreen  ;if the switches are set 
    brset port_t,#%00000010,lastsscreen ;go to special routine to redraw screen
    ldaa menuNum
    beq mainMenu    ;otherwise check menu number
    cmpa #2
    blt fertMenu     ;draw screen based on what menu number the program
    ldd #sub2        ;was on last then return
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
lastsscreen:        ;load the address of the last screen display and return
    ldd lastscreen
    jsr drawscreen
    puld
    rts
    
fin:    ;gamestate5
    ldd #tth         ;load time to harvest screen and draw
    jsr drawscreen
    ldd #tth2        ;load harvest instruction screen and draw
    jsr drawscreen
wait:
    brset port_p,#%00100000,wait  ;wait for user to press pushbutton to continue
    jsr harvesting    ;jump to harvesting routine
    ldd #mainmenu     ;redraw main menu
    jsr drawscreen
    puld             ;restore D
    leas -4,sp       ;load stack pointer to return from nested subroutines
    jmp start        ;jmp back to start (scanning keyboard on main menu)

    
