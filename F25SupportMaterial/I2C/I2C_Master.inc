    ;Before an I2C_WRITE call Main Code Should:
    ;1. Clear SSP1IF to prevent collision errors 
    ;2. Load ADDRESS_W Registers for Peripheral
    ;3. Load DATA_TX_1 Register with First Byte Data
    ;4. Load DATA_TX_2 Register with Second Byte Data
    ;5. Call I2C_WRITE

ADDRESS_W			EQU	H'040'
DATA_TX_1			EQU	H'041'
DATA_TX_2			EQU	H'042'


I2C_CODE    CODE

I2C_SETUP_SERVER
    BANKSEL APFCON1
    BCF APFCON1, 3
    BCF APFCON1, 4
    BANKSEL TRISC
    BSF TRISC,3
    BSF TRISC,4 		;Set SCL and SDA as inputs
    BANKSEL SSPADD
    MOVLW H'09'
    MOVWF SSPADD		;Set BAUD Generator to 100Khz (4M Occilator)
    BANKSEL SSPCON1
    MOVLW B'00101000'
    MOVWF SSPCON1		;Enable SDA and SLC Pins and Set as I2C Master Mode
    BANKSEL SSPCON2
    MOVLW B'00000000'
    MOVWF SSPCON2		;Disable General Call
    BANKSEL SSP1CON3
    MOVLW B'00001000'	;Min SDA Hold time 300ns
    MOVWF SSP1CON3
    BANKSEL SSPSTAT
    MOVLW B'11000000'
    MOVWF SSPSTAT		;Not in Tx mode, Slew Rate Control Disabled
    RETURN

I2C_WRITE
    CALL I2C_IDLE		;Ensure the I2C BUS is idle
    BANKSEL SSPCON2
    BSF SSPCON2, SEN		;Generate Start Condition
START_WRITE_DONE
    BTFSC SSPCON2, SEN
    GOTO START_WRITE_DONE	;Wait Until Start Condition Completes
    BANKSEL PIR1
    BTFSS PIR1, SSP1IF
    GOTO $-2
    BCF PIR1, SSP1IF
    BANKSEL ADDRESS_W
    MOVFW ADDRESS_W
    BANKSEL SSPBUF
    MOVWF SSPBUF		;Send Peripheral Address (Write)
ADDRESS_SENT_W
    BANKSEL PIR1
    BTFSS PIR1, SSP1IF
    GOTO $-2
    BCF PIR1, SSP1IF
    BANKSEL SSPSTAT
    BTFSC SSPSTAT,0		
    GOTO $-2		;Wait Until Buffer is Clear (Address is Sent)
    CALL I2C_IDLE		;Ensure the I2C BUS is idle
    BANKSEL SSPCON2
    BTFSC SSPCON2, ACKSTAT	;Was an Acknowledge Received?
    GOTO BAD_COND		;Acknowledge Not Received
    BANKSEL DATA_TX_1
    MOVFW DATA_TX_1
    BANKSEL SSPBUF
    MOVWF SSPBUF		;Send First Data Byte
DATA_1_SENT_W
    BANKSEL PIR1
    BTFSS PIR1, SSP1IF
    GOTO $-2
    BCF PIR1, SSP1IF
    BANKSEL SSPSTAT
    BTFSC SSPSTAT,0
    GOTO $-2		;Wait Until Buffer is Clear (Data is Sent)
    CALL I2C_IDLE		;Ensure the I2C BUS is idle
    BANKSEL SSPCON2
    BTFSC SSPCON2,ACKSTAT	;Was an Acknowledge Received?
    GOTO BAD_COND		;Acknowledge Not Received
    BANKSEL DATA_TX_2
    MOVFW DATA_TX_2
    BANKSEL SSPBUF
    MOVWF SSPBUF		;Send Second Data Byte
DATA_2_SENT
    BANKSEL PIR1
    BTFSS PIR1, SSP1IF
    GOTO $-2
    BCF PIR1, SSP1IF
    BANKSEL SSPSTAT		;Note I2C can use as many data bytes as desired, this program is only setup for two
    BTFSC SSPSTAT,0
    GOTO $-2		;Wait Unitl Buffer is Clear (Data is Sent)
    CALL I2C_IDLE
    BANKSEL SSPCON2
    BTFSC SSPCON2,6		;Was an Acknowledge Received?
    GOTO BAD_COND		;Acknowledge not Received
GOOD_STOP
    BANKSEL SSPCON2
    BSF SSPCON2,2		;Generate a Stop Condition
GOOD_STOP_DONE
    BTFSC SSPCON2,2
    GOTO GOOD_STOP_DONE	;Wait Until Stop Condition Completes
    MOVLW H'00'
    RETURN			;Write Complete.  Return With 0x00 in Working Register

BAD_COND
    BANKSEL SSPCON2
    BSF SSPCON2,2		;Generate Stop Condition
BAD_STOP_DONE
    BTFSC SSPCON2,2
    GOTO BAD_STOP_DONE	;Wait Until Stop Condition Completes
    MOVLW H'FF'
    RETURN			;Write Failed.  Return Wif 0xFF in Working Register

I2C_IDLE
    BANKSEL SSPCON2
    MOVLW H'1F'
    ANDWF SSPCON2		;Compare to 0x1F to Test for 5 Busy Conditions
    BANKSEL STATUS
    BTFSS STATUS,2
    GOTO I2C_IDLE		;If any Conditions Still Busy Wait
CHECK_R_W
    BANKSEL SSPSTAT
    BTFSC SSPSTAT,2
    GOTO CHECK_R_W		;Wait Until  a Transmission is Not in Process
    RETURN			;I2C BUS is Idle Exit Routine