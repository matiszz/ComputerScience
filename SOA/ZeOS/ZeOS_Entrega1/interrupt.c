/*
 * interrupt.c -
 */
#include <types.h>
#include <interrupt.h>
#include <segment.h>
#include <hardware.h>
#include <io.h>
#include <zeos_interrupt.h>
#include <system.h>
#include <sched.h>
#include <schedperf.h>

Gate idt[IDT_ENTRIES];
Register idtR;

char char_map[] = {
	'\0','\0','1','2','3','4','5','6',
	'7','8','9','0','\'','\0','\0','\0',
	'q','w','e','r','t','y','u','i',
	'o','p','`','+','\0','\0','a','s',
	'd','f','g','h','j','k','l','\0',
	'\0','\0','\0','\0','z','x','c','v',
	'b','n','m',',','.','-','\0','*',
	'\0','\0','\0','\0','\0','\0','\0','\0',
	'\0','\0','\0','\0','\0','\0','\0','7',
	'8','9','-','4','5','6','+','1',
	'2','3','0','\0','\0','\0','<','\0',
	'\0','\0','\0','\0','\0','\0','\0','\0',
	'\0','\0'
};

void setInterruptHandler(int vector, void (*handler)(), int maxAccessibleFromPL) {

	/***********************************************************************/
	/* THE INTERRUPTION GATE FLAGS:                          R1: pg. 5-11  */
	/* ***************************                                         */
	/* flags = x xx 0x110 000 ?????                                        */
	/*         |  |  |                                                     */
	/*         |  |   \ D = Size of gate: 1 = 32 bits; 0 = 16 bits         */
	/*         |   \ DPL = Num. higher PL from which it is accessible      */
	/*          \ P = Segment Present bit                                  */
	/***********************************************************************/
	Word flags = (Word)(maxAccessibleFromPL << 13);
	flags |= 0x8E00;    /* P = 1, D = 1, Type = 1110 (Interrupt Gate) */

	idt[vector].lowOffset       = lowWord((DWord)handler);
	idt[vector].segmentSelector = __KERNEL_CS;
	idt[vector].flags           = flags;
	idt[vector].highOffset      = highWord((DWord)handler);
}

void setTrapHandler(int vector, void (*handler)(), int maxAccessibleFromPL) {

	/***********************************************************************/
	/* THE TRAP GATE FLAGS:                                  R1: pg. 5-11  */
	/* ********************                                                */
	/* flags = x xx 0x111 000 ?????                                        */
	/*         |  |  |                                                     */
	/*         |  |   \ D = Size of gate: 1 = 32 bits; 0 = 16 bits         */
	/*         |   \ DPL = Num. higher PL from which it is accessible      */
	/*          \ P = Segment Present bit                                  */
	/***********************************************************************/
	Word flags = (Word)(maxAccessibleFromPL << 13);

	//flags |= 0x8F00;    /* P = 1, D = 1, Type = 1111 (Trap Gate) */
	/* Changed to 0x8e00 to convert it to an 'interrupt gate' and so
		the system calls will be thread-safe. */
	flags |= 0x8E00;    /* P = 1, D = 1, Type = 1110 (Interrupt Gate) */

	idt[vector].lowOffset       = lowWord((DWord)handler);
	idt[vector].segmentSelector = __KERNEL_CS;
	idt[vector].flags           = flags;
	idt[vector].highOffset      = highWord((DWord)handler);
}

// Rutina del teclat
void keyboard_routine() {
 	unsigned char key;
 	key = inb(0x60); // Llegeix el port del teclat

			//      Registre 0x60
			//  ________________________
			// |   |                    |
			// |_7_|6__________________0|

  	unsigned char translate = key & 0x7F; // Per saber el codi
  	unsigned char make = key & 0x80;		// Per saber si break o make
	if (make == 0x80) {
    	char c = char_map[translate];
    	if (c == '\0') printc_xy(10, 20, 'C');
      	else printc_xy(10, 20, c);
  	}
}

// Rutina del clock
extern int zeos_ticks; // Extern la llama de fuera.
void clock_routine() {
	zeos_show_clock();
	zeos_ticks++;
	planificador();
}

void keyboard_handler();
void clock_handler();
void system_call_handler();

void setIdt() {
	/* Program interrups/exception service routines */
	idtR.base  = (DWord)idt;
	idtR.limit = IDT_ENTRIES * sizeof(Gate) - 1;

	set_handlers();
	setInterruptHandler(33, keyboard_handler, 0);
	setInterruptHandler(32, clock_handler, 0);
	setTrapHandler(0x80, system_call_handler, 3);

	/* ADD INITIALIZATION CODE FOR INTERRUPT VECTOR */
	set_idt_reg(&idtR);
}
