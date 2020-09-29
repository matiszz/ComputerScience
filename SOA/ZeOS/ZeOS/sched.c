/*
 * sched.c - initializes struct for task 0 anda task 1
 */

#include <sched.h>
#include <mm.h>
#include <io.h>

/**
 * Container for the Task array and 2 additional pages (the first and the last one)
 * to protect against out of bound accesses.
 */
union task_union protected_tasks[NR_TASKS+2]
  __attribute__((__section__(".data.task")));

union task_union *task = &protected_tasks[1];

extern struct list_head blocked;
struct task_struct * idle_task; 
struct list_head freequeue; 				  // Tiene que ser global
struct list_head readyqueue; 				  // Tiene que ser global
int tiempoCPU = 0;

struct task_struct *list_head_to_task_struct(struct list_head *l) {
	int aux = (int)l&0xfffff000;
	return (struct task_struct*)aux;
}

/* get_DIR - Returns the Page Directory address for task 't' */
page_table_entry * get_DIR (struct task_struct *t) {
	return t->dir_pages_baseAddr;
}

/* get_PT - Returns the Page Table address for task 't' */
page_table_entry * get_PT (struct task_struct *t) {
	return (page_table_entry *)(((unsigned int)(t->dir_pages_baseAddr->bits.pbase_addr))<<12);
}

void inner_task_switch(union task_union *nuevo) {
    // Cambio pila de sistema.
	tss.esp0 = (unsigned long)&(nuevo->stack[KERNEL_STACK_SIZE]);

	// Cambio de Tabla de Páginas
	set_cr3(get_DIR(&nuevo->task));
	
	// Guardamos en ebp el esp de nuevo
	asm volatile("movl %%ebp, %0" /* %0 es el input */
		: "=g" (current()->esp)
	);
	
	// Guardamos el contenido de esp en el esp de mi pila
	asm volatile("movl %0, %%esp"
		: /* No input */
		: "g" (nuevo->task.esp)
	);
	// Salir del modo sistema
	asm volatile("pop %ebp;");
	asm volatile("ret;");
}

void task_switch(union task_union *t) {
	asm("push %esi;");
	asm("push %edi;");
	asm("push %ebx;");
	inner_task_switch(t);
	asm("pop %ebx;");
	asm("pop %edi;");
	asm("pop %esi;");
}

int allocate_DIR(struct task_struct *t) {
	int pos;
	pos = ((int)t-(int)task)/sizeof(union task_union);
	t->dir_pages_baseAddr = (page_table_entry*) &dir_pages[pos]; 
	return 1;
}

void cpu_idle(void) {
	// Para permitir las interrupciones en modo Kernel
	__asm__ __volatile__("sti": : :"memory");
	
	while(1) { ; }
}

void init_idle (void) {
	struct list_head *primer = list_first(&freequeue); // Obtenemos el primer elemento de la freequeue;
	
	struct task_struct *pcb_idle = list_head_to_task_struct(primer); // A partir del list_head sacamos el task_struct
	list_del(primer); 					// Eliminamos este elemento
	allocate_DIR(pcb_idle); 			// Inicializamos el directorio de paginas del proceso task
	
	pcb_idle->PID = 0; 					// Asignamos el PID 0 al proceso
	set_quantum(pcb_idle, QUANTUM_CPU); // Le asignamos el quantum

	// Ponemos todas las estadísticas a 0
	pcb_idle->estadisticas.user_ticks = 0;
	pcb_idle->estadisticas.system_ticks = 0;
	pcb_idle->estadisticas.blocked_ticks = 0;
	pcb_idle->estadisticas.ready_ticks = 0;
	pcb_idle->estadisticas.elapsed_total_ticks = 0;
	pcb_idle->estadisticas.total_trans = 0;
	pcb_idle->estadisticas.remaining_ticks = 0;

	tiempoCPU = pcb_idle->quantum;

	union task_union *uIdle = (union task_union*)pcb_idle;
	uIdle->task = *(pcb_idle);
	uIdle->stack[KERNEL_STACK_SIZE-1] = (unsigned long)&cpu_idle; 	// Asignamos la direccion de la funcion cpu_idle
	uIdle->stack[KERNEL_STACK_SIZE-2] = 0; 							// %ebp = 0
	pcb_idle->esp = (unsigned long)&(uIdle->stack[KERNEL_STACK_SIZE-2]);

	idle_task = pcb_idle;		// Hacemos que la variable global aputne al PCB de idle
}

void init_task1(void) {
	struct list_head *primer = list_first(&freequeue); // Obtenemos el primer elemento de la freequeue;
	
	struct task_struct *pcb_init = list_head_to_task_struct(primer); // A partir del list_head sacamos el task_struct
	list_del(primer);					// Lo eliminamos
	allocate_DIR(pcb_init);			 	// Inicializamos el directorio de paginas del proceso task1
	set_user_pages(pcb_init);

	pcb_init->PID = 1; 					// Asignamos el PID 1 al proceso 
	pcb_init->estado_actual = ST_RUN; // Le asignamos el estado actual
	set_quantum(pcb_init, QUANTUM_CPU); // Le asignamsos el quantum
	
	// Ponemos todas las estadísticas a 0
	pcb_init->estadisticas.user_ticks = 0;
	pcb_init->estadisticas.system_ticks = 0;
	pcb_init->estadisticas.blocked_ticks = 0;
	pcb_init->estadisticas.ready_ticks = 0;
	pcb_init->estadisticas.elapsed_total_ticks = 0;
	pcb_init->estadisticas.total_trans = 0;
	pcb_init->estadisticas.remaining_ticks = 0;
	
	tiempoCPU = pcb_init->quantum;
	
	union task_union *uInit = (union task_union*)pcb_init;
	uInit->task = *(pcb_init);
	tss.esp0 = (DWord)&(uInit->stack[KERNEL_STACK_SIZE]);

	set_cr3(pcb_init->dir_pages_baseAddr);	// Hacemos que cr3 apunte a su directorio
}

void init_sched() {

	/// FREE QUEUE
	INIT_LIST_HEAD(&freequeue); 	// La inicializamos
	for (int i = 0; i < NR_TASKS; ++i)
		list_add_tail(&(task[i].task.list), &freequeue); // Añadimos las tareas al principio

	// READY QUEUE
	INIT_LIST_HEAD(&readyqueue); 	// La inicializamos
}

struct task_struct* current() {
  int ret_value;
  
  __asm__ __volatile__(
  	"movl %%esp, %0"
	: "=g" (ret_value)
  );

  return (struct task_struct*)(ret_value&0xfffff000);
}

void actualizar_estadisticas(unsigned long *stat, struct task_struct *current) {
	unsigned long ticks = get_ticks();
	*stat += ticks - current->estadisticas.elapsed_total_ticks;
	current->estadisticas.elapsed_total_ticks = ticks;
}

// ################## Planificador ##################
struct task_struct *idle_task=NULL;

int get_quantum (struct task_struct *t) {
	return t->quantum;
}

void set_quantum (struct task_struct *t, int new_quantum) {
	t->quantum = new_quantum;
}

// Actualiza nº ticks que el proceso ha ejecutado desde que se asigno a la CPU
void update_sched_data_rr() {
	tiempoCPU--;
}

// Devuelve 1 si es necesario cambiar el estado del proceso current() y 0 en caso contrario
int needs_sched_rr() {
	if (tiempoCPU == 0 && !list_empty(&readyqueue)) return 1;
	if (tiempoCPU == 0) tiempoCPU = get_quantum(current());
	return 0;
}

// Elige el siguiente proceso a ejecutar, lo saca de la ready queue y llama a un task_switch.
void sched_next_rr() {
	struct task_struct *pcb_siguiente;

	if (list_empty(&readyqueue)) pcb_siguiente = idle_task;
	else {
		struct list_head *primero = list_first(&readyqueue);
		pcb_siguiente = list_head_to_task_struct(primero);
		list_del(primero);
	}
	pcb_siguiente->estado_actual = ST_RUN;
	tiempoCPU = get_quantum(pcb_siguiente);
	
	// Actualizamos system ticks, ready ticks, y transiciones
	actualizar_estadisticas(&(current()->estadisticas.system_ticks), current());
	actualizar_estadisticas(&(pcb_siguiente->estadisticas.ready_ticks), pcb_siguiente);
	pcb_siguiente->estadisticas.total_trans++;
	
	union task_union *uSiguiente = (union task_union *)pcb_siguiente;
	task_switch(uSiguiente);
}

// Actualiza el estado de un proceso.
void update_process_state_rr(struct task_struct *t, struct list_head *dest) {
	// Si voy a cambiar algo, la saco de su lista
	if (t->estado_actual != ST_RUN) list_del(&(t->list));

	// Si el destino es NULL significa que va a entrar en CPU
	if (dest == NULL) t->estado_actual = ST_RUN;
	else {
		if (dest == &readyqueue) t->estado_actual = ST_READY;
		else {
			t->estado_actual = ST_BLOCKED;
			actualizar_estadisticas(&(t->estadisticas.system_ticks), t);
		}
		list_add_tail(&(t->list), dest);
	}

	sched_next_rr();
}

void planificador() {
	update_sched_data_rr();

	if (needs_sched_rr() == 1) 
		update_process_state_rr(current(), &readyqueue);
}