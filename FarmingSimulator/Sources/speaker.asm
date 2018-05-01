	XDEF speaker
	XREF loc,SendsChr,rtiCtrl,PlayTone,timer2
	
speaker:
    	ldd timer2    ;timer to control speed of song
    	cpd #600
    	bne Leave
    	movw #0000,timer2
    	ldy #3000
		ldx		loc
		ldaa	0,x	;a has value of sound
		cmpa	#255	;any rest value
		beq		Rest
		cmpa	#00	;end of array
		beq		Reset
		pshx
		psha
		jsr		SendsChr	;send character
		pula
		bra Note
NextNote:
		pulx
		inx		;increment the array counter
		stx		loc	;store next location
Leave:	
		rts
Reset:	
		bclr	rtiCtrl,#%01000000
		rts
Note:
		jsr	PlayTone	;send tone to speaker
		dbne y,Note	;delay
		bra NextNote
Rest:
		dbne	y,Rest	;delay until rest is over
		inx	;increment array counter
		stx	loc	;store next location
		bra Leave