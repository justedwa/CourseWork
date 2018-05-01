	XREF Counter,tON,timer,port_t
	XDEF RTI_DC

RTI_DC:
		ldaa timer
		cmpa #100
		beq endDC
		inca
		staa timer
        ldaa Counter
        inca
        staa Counter
        cmpa tON
        ble  s1
        cmpa #15
        ble s2
        ldaa #$00
        staa Counter
        movb #$80,CRGFLG
        RTI
        s1:
           bset port_t,#%00001000
           movb #$80,CRGFLG
           RTI
        s2:
           bclr port_t,#%00001000
           movb #$80,CRGFLG
           RTI
		endDC:
			movb #0,timer
			movb #$80,CRGFLG
			SEI
			RTI