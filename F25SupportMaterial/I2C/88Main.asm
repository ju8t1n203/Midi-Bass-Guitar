;-----------------------------------------------------------------------------------------------------------------------------------------------
; PROJECT NAME:	TEST I2C SERVER
;DATE:		10 APRIL 2025
;VERSION:		1
;CREATOR:		JUSTIN BELL
;COMPANY:	IDAHO STATE UNIVERSITY
;DESCRIPTION:	BASIC I2C SERVER PROGRAM
;-----------------------------------------------------------------------------------------------------------------------------------------------
; PIC16F1788 Configuration Bit Settings
; Assembly source line config statements

#include "p16f1788.inc"
#include"88Setup.inc"
#include "I2C_Master.inc"

; CONFIG1
; __config 0xE9E4
 __CONFIG _CONFIG1, _FOSC_INTOSC & _WDTE_OFF & _PWRTE_OFF & _MCLRE_ON & _CP_OFF & _CPD_OFF & _BOREN_OFF & _CLKOUTEN_OFF & _IESO_OFF & _FCMEN_ON
; CONFIG2
; __config 0xDFFF
 __CONFIG _CONFIG2, _WRT_OFF & _VCAPEN_OFF & _PLLEN_ON & _STVREN_ON & _BORV_LO & _LPBOR_OFF & _LVP_OFF
 
ORG 0x00
GOTO SETUP
 
SETUP:
    CALL SETUP88		;Typical register configuration
    CALL I2C_SETUP_SERVER	;Addresses relevent I2C registers for I2C master/server
    GOTO MAIN
    
MAIN:
    BANKSEL PORTB		;Toggle a bit to trigger to (on o-scope)
    BSF PORTB,5
    BCF PORTB, 5
    BANKSEL PIR1
    BCF PIR1, SSP1IF
    BANKSEL ADDRESS_W	;Load addreass for desired target
    MOVLW H'002'
    MOVWF ADDRESS_W
    MOVLW 0x1E
    MOVWF DATA_TX_1	;Load first data byte
    MOVLW 0X01
    MOVWF DATA_TX_2	;Load second data byte
    CALL I2C_WRITE
    GOTO MAIN
    END