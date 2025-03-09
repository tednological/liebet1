.equ F_CPU = 1000000
.include "m328pdef.inc"      
.org 0x0000
 rjmp RESET                 ; Reset vector
.org 0x0002
 rjmp INT0_vect             ; External Interrupt 0 vector


    

RESET:
    ; Set up the stack pointer
    ldi   r16, low(RAMEND)
    out   SPL, r16
    ldi   r16, high(RAMEND)
    out   SPH, r16

    ; DDRC =Port C as input 
    ldi   r16, 0x00
    out   DDRC, r16
    ; DDRB = Port B as output
    ldi   r16, 0xFF
    out   DDRB, r16
    ; DDRD = Port D as input (for INT0)
    ldi   r16, 0x00
    out   DDRD, r16

	; rising edge trigger
    ldi   r16, 0x03
    sts   EICRA, r16

    ; Enable INT0 
    ldi   r16, 0x01
    out   EIMSK, r16

    ; Clear any pending INT0 flag
    ldi   r16, 0x01
    out   EIFR, r16

    ; Enable global interrupts
    sei

MainLoop:
    ; Check if (PINC & 0x01) == 0, then set PORTB = 0xFF
    in    r16, PINC
    sbrs  r16, 0             ; Skip next instruction if bit 0 is set
    ldi   r16, 0xFF
    out   PORTB, r16

    ; Delay for 1.5 seconds by calling delay150 10 times
    ldi   r18, 10            ; r18 = loop counter for main delay
    ldi r19, 0
DelayLoopMain:
    rcall delay150
    dec   r18
    brne  DelayLoopMain
    out PORTB, r19  ; turn off the LED 
    rjmp  MainLoop           ; Repeat forever

; delays for 3.0 seconds (delay150 subroutine called 20 times)
INT0_vect:
    push  r16                ; Preserve registers used in ISR
    push  r17
    push  r18
    push  r21
    push  r22
    in    r16, PIND ; take input from pind
    sbrc  r16, 0             ; If bit 0 is cleared, skip the block
    rjmp  ISR_Block          ; Otherwise, branch to ISR_Block
    rjmp  ISR_End            ; Skip the block if condition not met

ISR_Block:
    ldi   r16, 0xFF
    out   PORTB, r16
    ; Delay for 3.0 seconds by calling delay150 20 times
    ldi   r18, 20            ; r18 = loop counter for ISR delay
    ldi r19, 0 ; create a zero
DelayLoopISR:
    rcall delay150
    dec   r18
    brne  DelayLoopISR
    out PORTB, r19 ; turn off the LED 
ISR_End:
    pop   r22                ; Restore registers
    pop   r21
    pop   r18
    pop   r17
    pop   r16
    reti                     ; Return from interrupt

; 0.15 seconds delay at 1 MHz
delay150:
    push  r21               ; Save registers
    push  r22
    ldi   r22, 194          ; Outer loop 
OuterLoop:
    ldi   r21, 194          ; Inner loop 
InnerLoop:
    dec   r21
    brne  InnerLoop
    dec   r22
    brne  OuterLoop
    pop   r22               ;restore registers
    pop   r21
    ret
