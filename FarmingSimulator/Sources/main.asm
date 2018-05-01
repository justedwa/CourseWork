;**************************************************************
;* This stationery serves as the framework for a              *
;* user application. For a more comprehensive program that    *
;* demonstrates the more advanced functionality of this       *
;* processor, please see the demonstration applications       *
;* located in the examples subdirectory of the                *
;* Freescale CodeWarrior for the HC12 Program directory       *
;**************************************************************
; Include derivative-specific definitions
            INCLUDE 'derivative.inc'

; export symbols
            XDEF Entry,pestctrl,Harvestsound,Plowsound,Seedsound,Alarm,Fertilizesound,Sprinklersound,loc,timer2,Counter2,temp,pstdtct,scoredisp,fertwtr,pests,harvests,IRQ_ISR,lastscreen,pesterr,pestdisp,ferterr,wtrerr,wtrdisp,fertdisp,menuNum,cropstats,exitflg,wtrctrldisp,fertctrldisp,SWstatus,start,port_p,sub1,sub2,mainmenu,harv,harvesting,tth,tth2,timer,seconds,STPcnt,PlantLED,wtrDC,fertDC,drawDL,rtiCtrl,port_t,RTI_ISR,CRGFLG,tON,fertscreen, wtrscreen, _Startup,port_s, err3,PlowLED, gamestate,Keyboard,err1,err2,sub2,sub1,disp,port_t
            ; we use export 'Entry' as symbol. This allows us to
            ; reference 'Entry' either in the linker .prm file
            ; or from C/C++ later on

            XREF __SEG_END_SSTACK,statsmen,speaker,growth,flowctrl,pestdetect,harvesting,pushb,display_string,pot_value,read_pot,init_LCD,SendsChr,PlayTone,fertilize,newcrop,drawscreen      ; symbol defined by the linker for the end of the stack
            
            ; LCD References
	         

            ; Potentiometer References
          



; variable/data section
my_variable: SECTION
PestDC  ds.b 1
disp:	ds.b 33
menuNum: ds.b 1
gamestate: ds.b 1
timer ds.w 1
seconds ds.w 1
Counter ds.b 1
tON ds.b 1
rtiCtrl ds.b 1
drawDL ds.w 1
fertDC ds.b 1
wtrDC ds.b 1
STPcnt ds.b 1
SWstatus ds.b 1
wtrctrldisp ds.b 33
fertctrldisp ds.b 33
pestdisp ds.b 33
exitflg ds.b 1
cropstats ds.b 1
temp ds.b 1
keyflg ds.b 1
gametime ds.w 1
lastscreen ds.w 1
scoredisp ds.b 33
harvests ds.b 1
pests ds.b 1
fertwtr ds.b 1
pestctrl ds.b 1
pstdtct ds.b 1
Counter2 ds.w 1
loc ds.w 1
timer2 ds.w 1
my_constants: SECTION 
harv dc.b       "   Harvesting                   ",0
welcome dc.b    "    Welcome         Farmtek     ",0
mainmenu  dc.b  "(A)F/W(B)NewCrop(F)Stats        ",0
sub2 dc.b       "(A)Plow         (B)Plant        ",0
sub1 dc.b       "(A)Fertilize    (B)Water        ",0
err1 dc.b       "Plant Crop      to Continue     ",0
err2 dc.b       "Crop Already    Planted         ",0
err3 dc.b 		"Field not       Plowed          ",0
fertscreen dc.b "Fertilizing                     ",0
wtrscreen dc.b  "Watering                        ",0
tth       dc.b  "Time to         Harvest         ",0
tth2      dc.b  "Press Button    To Harvest      ",0
ferterr dc.b    "Crop Fertile                    ",0
wtrerr dc.b     "Crop Watered                    ",0
fertdisp dc.b   "Crop Infertile                  ",0
wtrdisp dc.b    "Crop Not Watered                ",0
pesterr dc.b    "Pest Detected!  Spraying Field  ",0
ledpat dc.b $24,$81,$18,$FF,$00
PlantLED dc.b $80,$40,$20,$10,$08,$04,$02,$01,$80,$40,$20,$10,$08,$04,$02,$01,$80,$40,$20,$10,$08,$04,$02,$01,$80,$40,$20,$10,$08,$04,$02,$01
PlowLED dc.b $7F,$BF,$DF,$EF,$F7,$FB,$FD,$FE,$7F,$BF,$DF,$EF,$F7,$FB,$FD,$FE,$7F,$BF,$DF,$EF,$F7,$FB,$FD,$FE,$7F,$BF,$DF,$EF,$F7,$FB,$FD,$FE
fertLED dc.b $A5,$00
wtrLED dc.b  $AA,$55
port_s equ $248
s_DDR equ  $24A
port_u equ $268
u_DDR equ $24A
PSR_u equ $24D
PUDE equ $24C
port_t equ $240
t_DDR equ $242
Kseq dc.b $70,$B0,$D0,$E0,$FF
table dc.b $eb,$77,$7b,$7d,$b7,$bb,$bd,$d7,$db,$dd,$e7,$ed,$7e,$be,$de,$ee
port_p equ $258
p_DDR equ $25A
seq dc.b %00001010,%00010010,%00010100,%00001100
A3:		equ	37
B3:		equ	33
C3:		equ	63
d3:		equ	56
E3:		equ	50
F3:		equ	47
G3:		equ	42
C4:		equ	31
D4:		equ	28
E4:		equ	25
F4:		equ	24
G4:		equ	21
A4:		equ	19
A5:		equ	9
B5:		equ	8
B4:		equ	17
C5:		equ	16
D5:		equ	14
E5:		equ	12
F5:		equ	11
G5:		equ	10
A3F:	equ	40
B3F:	equ	35
D3F:	equ	59
E3F:	equ	53
G3F:	equ	44
A4F:	equ	20
B4F:	equ	17
D4F:	equ	30
E4F:	equ	26
G4F:	equ	22
A5F:	equ	10
B5F:	equ	9
D5F:	equ	15
E5F:	equ	13
G5F:	equ	11
B6:	equ	4
Arr	dc.b 	E5,E5,255,E5,E5,255,255,E5,E5,255,255,C5,C5,E5,E5,255,255
	dc.b	G5,G5,255,255,255,255,255,255,G4,G4,255,255,255,255,255,255
	dc.b	C5,C5,255,255,255,255,G4,G4,255,255,255,255,E4,E4,E4,E4
	dc.b	255,A4,A4,A4,A4,255,B4,B4,B4,255,B4F,B4F,A4,A4,00 

Alarm	dc.b	E5,E5,E5,E5,255,255,E5,E5,E5,E5,255,255
		dc.b	E5,E5,E5,E5,255,255,E5,E5,E5,E5,255,255
		dc.b	E5,E5,E5,E5,255,255,E5,E5,E5,E5,255,255
		dc.b	E5,E5,E5,E5,255,255,E5,E5,E5,E5,255,255,00

Plowsound: 
	dc.b B4,A4,G4,B4,A4,G4,B4,A4,G4,B4,A4,G4,B4,A4,G4,B4,A4,G4,B4,A4,G4,B4,A4,G4
	dc.b B4,A4,G4,B4,A4,G4,B4,A4,G4,B4,A4,G4,B4,A4,G4,B4,A4,G4,B4,A4,G4,B4,A4,G4
	dc.b B4,A4,G4,B4,A4,G4,B4,A4,G4,B4,A4,G4,B4,A4,G4,B4,A4,G4,B4,A4,G4,B4,A4,G4,00
			

Seedsound:		dc.b B6,255,255,B6,255,255,B6,255,255,B6,255,255,B6,255,255,B6,255,255,B6,255,255,B6,255,255
				dc.b B6,255,255,B6,255,255,B6,255,255,B6,255,255,B6,255,255,B6,255,255,B6,255,255,B6,255,255 
				dc.b B6,255,255,B6,255,255,B6,255,255,B6,255,255,B6,255,255,B6,255,255,B6,255,255,B6,255,255,00

Harvestsound:	dc.b G4,G4,G4,G4,G4,G4,G4,G4,G4,G4,G4,G4,D4,D4,D4,D4,E4,E4,E4,E4,C4,C4,C4,C4,C4,C4,C4,C4
				dc.b D4,D4,D4,D4,D4,D4,D4,D4,B4,B4,B4,B4,B4,B4,B4,B4,A4,A4,A4,A4,A4,A4,A4,A4,G4,G4,G4,G4,G4,G4,G4,G4,G4,G4,G4,G4,D4,D4,D4,D4,00
					 

Fertilizesound: 	dc.b C4,D4,E4,F4,G4,A4,B4,255,B4,A4,F4,E4,D4,C4 
					dc.b C4,D4,E4,F4,G4,A4,B4,255,B4,A4,F4,E4,D4,C4
					dc.b C4,D4,E4,F4,G4,A4,B4,255,B4,A4,F4,E4,D4,C4
					dc.b C4,D4,E4,F4,G4,A4,B4,255,B4,A4,F4,E4,D4,C4,00

Sprinklersound: 	dc.b G3,255,G3,255,G3,255,255,G3,G3,G3,G3,255,255,G3,255,G3 
					dc.b G3,255,G3,255,G3,255,255,G3,G3,G3,G3,255,255,G3,255,G3
					dc.b G3,255,G3,255,G3,255,255,G3,G3,G3,G3,255,255,G3,255,G3
					dc.b G3,255,G3,255,G3,255,255,G3,G3,G3,G3,255,255,G3,255,G3,00

; code section

MyCode:     SECTION
Entry:
_Startup:
;this section initilizes all variables as well as initilize the arrays that hold
;the displays. 
		   movw #0000,Counter2
		   movb #00,pstdtct 
		   movb #$00,pestctrl
		   movb #'H',scoredisp
           movb #'a',scoredisp+1
           movb #'r',scoredisp+2
           movb #'v',scoredisp+3
           movb #'e',scoredisp+4
           movb #'s',scoredisp+5
           movb #'t',scoredisp+6
           movb #'s',scoredisp+7
           movb #':',scoredisp+8
           movb #' ',scoredisp+9
           movb #' ',scoredisp+10
           movb #' ',scoredisp+11
           movb #' ',scoredisp+12
           movb #' ',scoredisp+13
           movb #' ',scoredisp+14
           movb #' ',scoredisp+15
           movb #'P',scoredisp+16
           movb #'e',scoredisp+17
           movb #'s',scoredisp+18
           movb #'t',scoredisp+19
           movb #'s',scoredisp+20
           movb #':',scoredisp+21
           movb #' ',scoredisp+22
           movb #' ',scoredisp+23
           movb #' ',scoredisp+24
           movb #'W',scoredisp+25
           movb #'/',scoredisp+26
           movb #'F',scoredisp+27
           movb #':',scoredisp+28
           movb #' ',scoredisp+29
           movb #' ',scoredisp+30
           movb #' ',scoredisp+31
           movb #0,pestdisp+32 
           movb #00,keyflg
           movb #' ',pestdisp
           movb #'S',pestdisp+1
           movb #'p',pestdisp+2
           movb #'r',pestdisp+3
           movb #'a',pestdisp+4
           movb #'y',pestdisp+5
           movb #'i',pestdisp+6
           movb #'n',pestdisp+7
           movb #'g',pestdisp+8
           movb #' ',pestdisp+9
           movb #'P',pestdisp+10
           movb #'e',pestdisp+11
           movb #'s',pestdisp+12
           movb #'t',pestdisp+13
           movb #' ',pestdisp+14
           movb #' ',pestdisp+15
           movb #' ',pestdisp+16
           movb #' ',pestdisp+17
           movb #' ',pestdisp+18
           movb #' ',pestdisp+19
           movb #' ',pestdisp+20
           movb #'P',pestdisp+21
           movb #'B',pestdisp+22
           movb #' ',pestdisp+23
           movb #'t',pestdisp+24
           movb #'o',pestdisp+25
           movb #' ',pestdisp+26
           movb #'e',pestdisp+27
           movb #'x',pestdisp+28
           movb #'i',pestdisp+29
           movb #'t',pestdisp+30
           movb #'!',pestdisp+31
           movb #0,pestdisp+32
		   movb #'(',fertctrldisp
           movb #'A',fertctrldisp+1
           movb #')',fertctrldisp+2
           movb #'I',fertctrldisp+3
           movb #'n',fertctrldisp+4
           movb #'c',fertctrldisp+5
           movb #'F',fertctrldisp+6
           movb #'e',fertctrldisp+7
           movb #'r',fertctrldisp+8
           movb #'t',fertctrldisp+9
           movb #'i',fertctrldisp+10
           movb #'l',fertctrldisp+11
           movb #'i',fertctrldisp+12
           movb #'z',fertctrldisp+13
           movb #'e',fertctrldisp+14
           movb #'r',fertctrldisp+15
           movb #'(',fertctrldisp+16
           movb #'B',fertctrldisp+17
           movb #')',fertctrldisp+18
           movb #'D',fertctrldisp+19
           movb #'e',fertctrldisp+20
           movb #'c',fertctrldisp+21
           movb #' ',fertctrldisp+22
           movb #' ',fertctrldisp+23
           movb #' ',fertctrldisp+24
           movb #' ',fertctrldisp+25
           movb #' ',fertctrldisp+26
           movb #' ',fertctrldisp+27
           movb #' ',fertctrldisp+28
           movb #'1',fertctrldisp+29
           movb #'0',fertctrldisp+30
           movb #'%',fertctrldisp+31
           movb #0,fertctrldisp+32    ;string terminator, acts like '\0'
		   movb #'(',wtrctrldisp
           movb #'A',wtrctrldisp+1
           movb #')',wtrctrldisp+2
           movb #'I',wtrctrldisp+3
           movb #'n',wtrctrldisp+4
           movb #'c',wtrctrldisp+5
           movb #' ',wtrctrldisp+6
           movb #' ',wtrctrldisp+7
           movb #' ',wtrctrldisp+8
           movb #' ',wtrctrldisp+9
           movb #'W',wtrctrldisp+10
           movb #'a',wtrctrldisp+11
           movb #'t',wtrctrldisp+12
           movb #'e',wtrctrldisp+13
           movb #'r',wtrctrldisp+14
           movb #' ',wtrctrldisp+15
           movb #'(',wtrctrldisp+16
           movb #'B',wtrctrldisp+17
           movb #')',wtrctrldisp+18
           movb #'D',wtrctrldisp+19
           movb #'e',wtrctrldisp+20
           movb #'c',wtrctrldisp+21
           movb #' ',wtrctrldisp+22
           movb #' ',wtrctrldisp+23
           movb #' ',wtrctrldisp+24
           movb #' ',wtrctrldisp+25
           movb #' ',wtrctrldisp+26
           movb #' ',wtrctrldisp+27
           movb #' ',wtrctrldisp+28
           movb #'5',wtrctrldisp+29
           movb #'0',wtrctrldisp+30
           movb #'%',wtrctrldisp+31
           movb #0,wtrctrldisp+32    ;string terminator, acts like '\0'
           movb #00,cropstats
           movb #$00,STPcnt
           MOVB #%00011110,p_DDR
           movb #6,fertDC
           movb #30,wtrDC
           movw #1000,drawDL
           movb #%00000000,rtiCtrl
           movb #' ',disp
           movb #' ',disp+1
           movb #' ',disp+2
           movb #' ',disp+3
           movb #' ',disp+4
           movb #' ',disp+5
           movb #' ',disp+6
           movb #' ',disp+7
           movb #' ',disp+8
           movb #' ',disp+9
           movb #' ',disp+10
           movb #' ',disp+11
           movb #' ',disp+12
           movb #' ',disp+13
           movb #' ',disp+14
           movb #' ',disp+15
           movb #' ',disp+16
           movb #' ',disp+17
           movb #' ',disp+18
           movb #' ',disp+19
           movb #' ',disp+20
           movb #' ',disp+21
           movb #' ',disp+22
           movb #' ',disp+23
           movb #' ',disp+24
           movb #' ',disp+25
           movb #' ',disp+26
           movb #' ',disp+27
           movb #' ',disp+28
           movb #' ',disp+29
           movb #' ',disp+30
           movb #' ',disp+31
           movb #0,disp+32    ;string terminator, acts like '\0'
           movw #0000,timer
           movw #0000,seconds
           movb #5,tON
           movb #1,SWstatus
           movb #0,pests
           movb #0,harvests
           movb #0,fertwtr
           movw #0,loc
           movw #0000,timer2
    movb #$00,Counter
    movb #$80,CRGINT
    movb #$10,RTICTL
    movb #$00,gamestate
    bset t_DDR,#%00101000
    bset port_t,#%00100000
    movb #$F0,$26A
    movb #$F0,$26D
    movb #$0F,$26C
    movb #$FF,s_DDR
    movb #00,exitflg
    bclr port_s,#%11111111
 	LDS #__SEG_END_SSTACK
 	jsr init_LCD ;initilizes LCD screen
    ldd #welcome  ;loads the address of the welcome screen display array
    std lastscreen ;stores address again so that we have reference to the last screen displayed
	jsr display_string ;displays welcome screen
	cli                ;enable RTI
	ldx #Arr           ;loads address of music array
	stx loc            ;stores address into current music location
	bset rtiCtrl,#%01000000 ;sets control flag for music playing
	ldaa #5 ;counter for 5 pattern LED display
    ldx #ledpat  ;led patter array loaded
nextpat:
    ldab 1,X+    ;loads next pattern
    stab port_s  ;outputs pattern to LEDs
setup:
    ldy gametime ;checks the gametime variable in RTI to delay 1 secs per loop
    cpy #10000
    blt setup
    movw #00,gametime
    deca
    bne nextpat 
    ;jingle goes here
        
    ;Display Main Menu
    movb #$40,INTCR    ;initilized IRQ
    ldd #mainmenu      ;draws main menu screen
    jsr drawscreen



;this section of code scans the keyboard
;then based on the selection will enter a new menu
start:
     movb #00,menuNum
     jsr Keyboard
     cmpa #10
     bne b1
     jsr fertilize
    b1:
     cmpa #11
     bne b2
     jsr newcrop
    b2:
     cmpa #15
     bne nxt
     jsr statsmen
nxt:
     ldd #mainmenu
     jsr drawscreen
     bra start	
;this is the keyboard scanning subroutine
Keyboard:
rst:    ldx #Kseq
		brset pstdtct,#%00000001,PST ;jumps to seperate area if inside of pest IRQ
		brset port_t,#%00000001,SW ;checks to see if switches are flipped then enters seperate menu
		brset port_t,#%00000010,SW
scan:
    brclr port_p,#%00100000,PB ;checks if pushbutton is pressed
    ldaa exitflg
    bne swcheck   ;checks status of switches 
scanSW:           ;this starts the typical keyboard subroutine
    ldaa 1,X+
    cmpa #$FF
    beq rst
    staa port_u
hold1:                      ;waits for key to be released
    brset keyflg,#$FF,hold1
hold2:
    brclr keyflg,#$FF,hold2
    ldaa port_u
    ldab port_u
    anda #%00001111
    cmpa #$0F
    beq scan
    jsr Search
end:rts        
PB:            ;if the PB is pressed goes to PB subroutine
    jsr pushb
    bra scan
SW:
	ldaa SWstatus  ;if switches are set go to flowctrl subroutine
	beq scan
	jsr flowctrl
	bra scan
PST:             ;if pest detect flag is set go to subroutine
	jsr pestdetect
	bra scan
swcheck:          ;checks to see if switches are still set
	ldaa port_t
	anda #%00000011
	beq exitSW
	bra scanSW
exitSW:
	rts			 
Search:
		ldx #table;loads address of first value of table
		ldaa #0
top:
		cmpb 1,X+  ;checks to see if val is equal to first value in table
		beq match ;if there is a match move to load the index into a
		inca ;checks to see if the table has been cycled through
		bne top ;if it is not equal then return to the start     
match:
        psha	;saves value of a while waiting for key release
hold11:
        brset keyflg,#$FF,hold11
hold21:
        brclr keyflg,#$FF,hold21
        ldaa port_u
        anda #$0F
        cmpa #$0F
        bne hold11
        pula
        rts

;real time interupt control



RTI_ISR:
		ldaa rtiCtrl     ;loads RTI flag variable
        bita #%01000000  ;checks for music flag
        beq Nomusic
        ldd timer2       ;if the flag is set increment timer
        addd #1          ;then jump to speaker subroutine
        std timer2
        jsr speaker
Nomusic:
	    ldaa gamestate    ;checks gamestate to see if setup is finished
        bne setupdone
        ldd gametime    ;if setup is still continuing 
        addd #1         ;increment gametime counter
        std gametime
setupdone:              ;varies keyflag to control keyboard timing
        ldaa keyflg
        eora #$FF
        staa keyflg
STPtst:
        ldaa rtiCtrl   ;reload control flags
        bita #%00011100 ;if plow,planter,harvester flag set go to stepper motor subroutine
        beq DCtst
        jsr STPmtr
DCtst:
        ldaa rtiCtrl    ;check to see if DC motor flag is set
        bita #%00000001
        beq timing
        jsr DCmtr       ;if flags set jump to DC motor routine
timing:
        ldaa rtiCtrl    ;checks to see if screen is being drawn and delays appropriately
        bita #%00000010
        bne drawscreenDL
postDelay:              ;checks to see if crop is planted if not exit rti
        ldaa gamestate
        cmpa #2
        blt endrti
        ldd timer       ;if crop is planted increment game timer
      	addd #1
        std timer        
        cpd #$2710      ;if timer reaches 10000 then increment seconds counter by 1
        bne  endrti
        movw #$0000,timer
        ldd seconds
		addd #1
        std seconds
        jsr growth     ;jump to growth routine to see if crop grows
endrti:
        movb #$80,CRGFLG
        RTI
	
drawscreenDL:        ;handles delay for Drawscreen
        ldx drawDL
        dex
        stx drawDL
        bra postDelay

DCmtr:
		ldaa rtiCtrl     ;checks to see if pest detection is running
		bita #%00100000
		bne pstDC
        jsr dcLED    ;if pest detection is running flash LEDs then go to DC motor service
pstDC:
        ldaa Counter  ;load and increment counter (up to 60)
        inca
        staa Counter
        cmpa tON       ;compare counter to tON value set for DC motor
        ble  s1        ;if it is less than keep motor on
        cmpa #60
        ble s2         ;if it is greater than tON but less than 60 turn motor off
        ldaa #$00
        staa Counter   ;otherwise reset counter and exit
        movb #$80,CRGFLG
        rts
        s1:
           bset port_t,#%00001000
           rts
        s2:
           bclr port_t,#%00001000
           rts
STPmtr:
       ldaa rtiCtrl   ;loads control flags then checks for
       bita #%00001000 ;which stepper routine to run
       bne seeder
       bita #%00010000
       bne harvester
       bra chisel
       
       
       
       
harvester:
       ldd Counter2   ;checks to see if there is a sufficient delay to send next pattern to stepper motor
       addd #1
       std Counter2
       cpd #150
       bne endSTP
       movw #00,Counter2 ;if counter has reached 1.5ms reset counter
       ldab STPcnt     ;loads index of current pattern
       ldx #seq        ;loads sequence
       abx             ;adds index to address to find proper pattern
       ldaa 0,X
       staa port_p     ;sends pattern to motor
       decb            ;decrements index
       bmi rstcnt1     ;if less than zero reset index
       stab STPcnt
       rts
rstcnt1:
       movb #03,STPcnt ;reset index
       rts
       
seeder:                ;similar to above but index counts up instead of down
       ldd Counter2
       addd #1
       std Counter2
       cpd #150
       bne endSTP
       movw #00,Counter2
       ldab STPcnt
       ldx #seq
       abx
       ldaa 0,X
       staa port_p
       incb
       cmpb #04
       beq rstcnt2
       stab STPcnt
       rts
rstcnt2:
       movb #00,STPcnt
       rts

chisel:              ;same as top but delay between patterns is less making motor faster
       ldd Counter2
       addd #1
       std Counter2
       cmpb #50
       bne endSTP
       movw #00,Counter2
       ldab STPcnt
       ldx #seq
       abx
       ldaa 0,X
       staa port_p
       decb
       bmi rstcnt3
       stab STPcnt
       rts
rstcnt3:
       movb #03,STPcnt
       rts

endSTP:
       rts


dcLED:       ;LED pattern control
      ldd timer  ;loads timer and checks if it is a multiple of 1000
      ldx #1000
      idiv
      cpd #00
      beq Pattern   ;if it is then display the next pattern
      rts
Pattern:
      ldaa rtiCtrl     ;checks what kind of LEDs need to be displayed
      bita #%10000000
      bne fert0
      
;water LEDS 
      xgdx          ;places result of counter/1000 in D
      ldx #2  ;divides by two to check if result was even
      idiv
      cpd #00   ;if result was even display first water pattern
      bne wtr1
      ldx #wtrLED
      ldaa 0,X
      staa port_s
      rts
wtr1:            ;if result was odd display second pattern
      ldx #wtrLED
      ldaa 1,X
      staa port_s
      rts

                  ;same as above except using fertilizer LED pattern
fert0:
      xgdx
      ldx #2
      idiv
      cpd #00
      bne fert1
      ldx #fertLED
      ldaa 0,X
      staa port_s
      rts
fert1:
      ldx #fertLED
      ldaa 1,X
      staa port_s
      rts      


 ;if IRQ button is pressed set the pest detection flag
IRQ_ISR:
		movb #1,pstdtct
		rti
     
