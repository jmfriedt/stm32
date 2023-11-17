#include <stdlib.h>
#include <reent.h>
#include <sys/stat.h>

#include <libopencm3/stm32/usart.h> // USART1

_ssize_t _read(int file, void *ptr, size_t len) {return 0;}

_ssize_t _write(int file, const void *ptr, size_t len)
{
 unsigned int i;
 const char *c;
 c=ptr;
 for (i=0;i<len;i++) usart_send_blocking(USART1, c[i]);
 return len;
}


int _close(  
    int file)
{
	return 0;
}


_off_t _lseek(
    int file, 
    _off_t ptr, 
    int dir)
{
	return (_off_t)0;	/*  Always indicate we are at file beginning.  */
}


int _fstat(
    int file, 
    struct stat *st)
{
	/*  Always set as character device.				*/
	st->st_mode = S_IFCHR;
	/* assigned to strong type with implicit 	*/
	/* signed/unsigned conversion.  Required by 	*/
	/* newlib.					*/

	return 0;
}


int _isatty(int file); // avoid warning 

int _isatty(int file)
{
	return 1;
}


#if 0
static void _exit (int n) {
label:  goto label; /* endless loop */
}
#endif 


/* "malloc clue function" from newlib-lpc/Keil-Demo/"generic" */

/**** Locally used variables. ****/
// mt: "cleaner": extern char* end;
extern char end[];              /*  end is set in the linker command 	*/
				/* file and is the end of statically 	*/
				/* allocated data (thus start of heap).	*/

static char *heap_ptr;		/* Points to current end of the heap.	*/

/************************** _sbrk_r *************************************
 * Support function. Adjusts end of heap to provide more memory to
 * memory allocator. Simple and dumb with no sanity checks.

 *  struct _reent *r -- re-entrancy structure, used by newlib to
 *                      support multiple threads of operation.
 *  ptrdiff_t nbytes -- number of bytes to add.
 *                      Returns pointer to start of new heap area.
 *
 *  Note:  This implementation is not thread safe (despite taking a
 *         _reent structure as a parameter).
 *         Since _s_r is not used in the current implementation, 
 *         the following messages must be suppressed.
 */
void * _sbrk(ptrdiff_t nbytes)
{char  *base;	
 if (!heap_ptr) {heap_ptr = end;} //  Initialize if first time through.  
 base = heap_ptr;	          //  Point to end of heap.  
 heap_ptr += nbytes;  	          //  Increase heap.  

usart_send(USART1,(nbytes&0xf000)>>12+'0');
usart_send(USART1,(nbytes&0x0f00)>> 8+'0');
usart_send(USART1,(nbytes&0x00f0)>> 4+'0');
usart_send(USART1,(nbytes&0x000f)    +'0');
	return base;		/*  Return pointer to start of new heap area.*/
}

