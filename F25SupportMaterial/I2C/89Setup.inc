;-----------------------------------------------------------------------------------------------------------------------------------------------
; PROJECT NAME:	SETUP FOR 1788
;DATE:		10 APRIL 2025
;VERSION:		1
;CREATOR:		JUSTIN BELL
;COMPANY:	IDAHO STATE UNIVERSITY
;DESCRIPTION:	SETUP INCLUDE FILE FOR THE 1788
;		ADDRESSES ALL PORTS AND OTHER REGISTERS
;-----------------------------------------------------------------------------------------------------------------------------------------------

EIGHTY_NINE_SETUP CODE

SETUP89
 ;--------------------------------------------------------OSCILLATOR---------------------------------------------------------------------
    BANKSEL OSCSTAT
    BTFSC OSCSTAT,PLLR	    ;WAIT FOR PLL TO BE UP AND RUNNING
    GOTO $-2
    BANKSEL OSCCON
    MOVLW B'11101011'
    MOVWF OSCCON
    BANKSEL OSCSTAT
    BTFSC OSCSTAT,OSTS	    ;WAIT FOR OSSCILATOR TO BE READY
    GOTO $-1
 
;--------------------------------------------------------PORT A------------------------------------------------------------------------------
    BANKSEL ADCON1
    MOVLW B'00000000'
    MOVWF ADCON1
    BANKSEL ANSELA
    MOVLW B'00000000'
    MOVWF ANSELA
    BANKSEL TRISA
    MOVLW	B'00000000'
    MOVWF	TRISA
    BANKSEL IOCAP
    MOVLW	B'00000000'
    MOVWF	IOCAP
    BANKSEL IOCAN
    MOVLW	B'00000000'
    MOVWF	IOCAN
    BANKSEL INLVLA
    MOVLW	B'00000000'
    MOVWF	INLVLA
    BANKSEL SLRCONA
    MOVLW	B'00000000'
    MOVWF	SLRCONA
    BANKSEL PORTA
    CLRF PORTA
    
;--------------------------------------------------------PORT B------------------------------------------------------------------------------
    BANKSEL TRISB
    MOVLW	B'00000000'
    MOVWF	TRISB
    BANKSEL ANSELB
    MOVLW	B'00000000'
    MOVWF	ANSELB
    BANKSEL WPUB
    MOVLW	B'00000000'
    MOVWF	WPUB
    BANKSEL ODCONB
    MOVLW	B'00000000'
    MOVWF	ODCONB
    BANKSEL SLRCONB
    MOVLW	B'00000000'
    MOVWF	SLRCONB
    BANKSEL IOCBP
    MOVLW	B'00000000'
    MOVWF	IOCBP
    BANKSEL IOCBN
    MOVLW	B'00000000'
    MOVWF	IOCBN
    BANKSEL IOCBF
    MOVLW	B'00000000'
    MOVWF	IOCBF
    BANKSEL PORTB
    CLRF PORTB
		
;--------------------------------------------------------PORT C------------------------------------------------------------------------------
    BANKSEL LATC
    MOVLW	B'00000000'
    MOVWF	LATC
    BANKSEL TRISC
    MOVLW	B'00011000'
    MOVWF	TRISC
    BANKSEL WPUC
    MOVLW	B'00000000'
    MOVWF	WPUC
    BANKSEL ODCONC
    MOVLW B'00011000'
    MOVWF ODCONC
    BANKSEL SLRCONC
    MOVLW B'00000000'
    MOVWF SLRCONC
    BANKSEL INLVLC
    CLRF INLVLC
    BANKSEL PORTC
    CLRF    PORTC
		
;--------------------------------------------------------PORT E------------------------------------------------------------------------------
    BANKSEL IOCEP
    MOVLW	B'00000000'
    MOVWF	IOCEP
    BANKSEL IOCEN
    MOVLW	B'00000000'
    MOVWF	IOCEN
    
;--------------------------------------------------------OPTION REGISTER---------------------------------------------------------------
    BANKSEL OPTION_REG
    MOVLW	B'00000000'
    MOVWF	OPTION_REG
    
;--------------------------------------------------------INTERRUPT CONTROL-----------------------------------------------------------
    BANKSEL INTCON
    MOVLW	B'00000000'
    MOVWF	INTCON
    
;--------------------------------------------------------PERIPHERAL ONE-----------------------------------------------------------------
    BANKSEL PIE1
    MOVLW	B'00000000'
    MOVWF	PIE1
    
;--------------------------------------------------------PERIPHERAL TWO----------------------------------------------------------------
    BANKSEL PIE2
    MOVLW	B'00000000'
    MOVWF	PIE2
    
;--------------------------------------------------------I2C_ADDRESS---------------------------------------------------------------------
    BANKSEL SSPADD
    MOVLW H'05'
    MOVWF SSPADD		;Peripheral Address
    
;--------------------------------------------------------CCP1 CONTROL--------------------------------------------------------------------
;    BANKSEL CCP1CON
;    MOVLW	B'00000000'
;    MOVWF	CCP1CON
;    BANKSEL CCP2CON
;    MOVLW	B'00000000'
;    MOVWF	CCP2CON
;    BANKSEL CM2CON1
;    MOVLW	B'00000000'
;    MOVWF	CM2CON1

;--------------------------------------------------------TIMER ONE------------------------------------------------------------------------
;    BANKSEL T1CON
;    MOVLW	B'00000000'
;    MOVWF	T1CON

;--------------------------------------------------------TIMER TWO-----------------------------------------------------------------------
;    BANKSEL T2CON
;    MOVLW	B'00000000'
;    MOVWF	T2CON
;    BANKSEL PR2
;    MOVLW	B'00000000'
;    MOVWF	PR2
    
;--------------------------------------------------------EUART------------------------------------------------------------------------------
;    BANKSEL BAUD1CON
;    MOVLW	B'00000000'
;    MOVWF	BAUD1CON
;    BANKSEL SP1BRGL
;    MOVLW	B'00001111'
;    MOVWF	SP1BRGL
;    BANKSEL SPBRGH
;    CLRF SPBRGH
;    BANKSEL TXSTA
;    CLRF TXSTA
;    BANKSEL RCREG
;    CLRF RCREG
;    BANKSEL RCSTA
;    CLRF RCSTA
;    MOVLW	B'10110000'
;    MOVWF RCSTA
;    BANKSEL PIE1
;    BSF PIE1,RCIE	    ; ENABLE RECIEVE INTERRUPT FOR UART
    
    RETURN