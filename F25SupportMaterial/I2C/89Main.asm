;-----------------------------------------------------------------------------------------------------------------------------------------------
; PROJECT NAME:	TEST I2C CLIENT
;DATE:		11 APRIL 2025
;VERSION:		1
;CREATOR:		JUSTIN BELL
;COMPANY:	IDAHO STATE UNIVERSITY
;DESCRIPTION:	BASIC I2C CLIENT PROGRAM
;-----------------------------------------------------------------------------------------------------------------------------------------------
; PIC16F1788 Configuration Bit Settings
; Assembly source line config statements

#include "p16f1789.inc"
#include"89Setup.inc"
#include "I2C_Peripheral.inc"

; CONFIG1
; __config 0xE9E4
 __CONFIG _CONFIG1, _FOSC_INTOSC & _WDTE_OFF & _PWRTE_OFF & _MCLRE_ON & _CP_OFF & _CPD_OFF & _BOREN_OFF & _CLKOUTEN_OFF & _IESO_OFF & _FCMEN_ON
; CONFIG2
; __config 0xDFFF
 __CONFIG _CONFIG2, _WRT_OFF & _VCAPEN_OFF & _PLLEN_ON & _STVREN_ON & _BORV_LO & _LPBOR_OFF & _LVP_OFF
 
ORG 0x00
    GOTO SETUP
    
SETUP:
    CALL SETUP89
    CALL I2C_SETUP_PERIPHERAL
    BANKSEL SSPADD
    MOVLW 0x05
    MOVWF SSPADD
    GOTO MAIN
    
MAIN:
    ; Wait for a start condition
    BANKSEL PIR1
    BTFSS PIR1, SSP1IF      ; Wait for start condition
    CALL I2C_READ
    BANKSEL PIR1
    BCF PIR1, SSP1IF
    BANKSEL DATA_RX_1
    MOVF DATA_RX_1, W
    BANKSEL PORTD
    MOVWF PORTD
    GOTO MAIN
    END