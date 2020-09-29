# 1 "entry.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "entry.S"




# 1 "include/asm.h" 1
# 6 "entry.S" 2
# 1 "include/segment.h" 1
# 7 "entry.S" 2
# 1 "include/errno.h" 1
# 8 "entry.S" 2
# 72 "entry.S"
.globl clock_handler; .type clock_handler, @function; .align 0; clock_handler:
      pushl %gs; pushl %fs; pushl %es; pushl %ds; pushl %eax; pushl %ebp; pushl %edi; pushl %esi; pushl %edx; pushl %ecx; pushl %ebx; movl $0x18, %edx; movl %edx, %ds; movl %edx, %es
      pushl %eax;
      call user_to_system;
      popl %eax;
      movb $0x20, %al; outb %al, $0x20;
      call clock_routine;
      pushl %eax;
      call system_to_user;
      popl %eax;
      popl %ebx; popl %ecx; popl %edx; popl %esi; popl %edi; popl %ebp; popl %eax; popl %ds; popl %es; popl %fs; popl %gs;
      iret;

.globl keyboard_handler; .type keyboard_handler, @function; .align 0; keyboard_handler:
      pushl %gs; pushl %fs; pushl %es; pushl %ds; pushl %eax; pushl %ebp; pushl %edi; pushl %esi; pushl %edx; pushl %ecx; pushl %ebx; movl $0x18, %edx; movl %edx, %ds; movl %edx, %es
      pushl %eax;
      call user_to_system;
      popl %eax;
      movb $0x20, %al; outb %al, $0x20;
      call keyboard_routine;
      pushl %eax;
      call system_to_user;
      popl %eax;
      popl %ebx; popl %ecx; popl %edx; popl %esi; popl %edi; popl %ebp; popl %eax; popl %ds; popl %es; popl %fs; popl %gs;
      iret;

.globl system_call_handler; .type system_call_handler, @function; .align 0; system_call_handler:
      pushl %gs; pushl %fs; pushl %es; pushl %ds; pushl %eax; pushl %ebp; pushl %edi; pushl %esi; pushl %edx; pushl %ecx; pushl %ebx; movl $0x18, %edx; movl %edx, %ds; movl %edx, %es
      pushl %eax;
      call user_to_system;
      popl %eax;
      cmpl $0, %eax;
      jl err;
      cmpl $MAX_SYSCALL, %eax;
      jg err;
      call *sys_call_table(, %eax, 0x4);
      jmp fin;
err:
      movl $-38, %eax;
fin:
      movl %eax, 0x18(%esp);
      pushl %eax;
      call system_to_user;
      popl %eax;
      popl %ebx; popl %ecx; popl %edx; popl %esi; popl %edi; popl %ebp; popl %eax; popl %ds; popl %es; popl %fs; popl %gs;
      iret;
