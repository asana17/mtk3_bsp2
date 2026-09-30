/*
 *----------------------------------------------------------------------
 *    micro T-Kernel 3.0 BSP 2.0
 *
 *    Copyright (C) 2023-2024 by Ken Sakamura.
 *    This software is distributed under the T-License 2.1.
 *----------------------------------------------------------------------
 *
 *    Released by TRON Forum(http://www.tron.org) at 2024/02.
 *
 *----------------------------------------------------------------------
 */

#include <sys/machine.h>
#ifdef MTKBSP_STM32CUBE

#include <tk/tkernel.h>
#include <kernel.h>

/*
 *	power_save.c (STM32Cube)
 *	Power-Saving Function
 */

/*
 * Switch to power-saving mode
 *	The dispatcher calls this with BASEPRI masking the interrupts, and an interrupt
 *	masked by BASEPRI does not wake WFI. So PRIMASK masks them instead while waiting.
 *	Any interrupt then wakes WFI, and is taken once BASEPRI is cleared.
 */
EXPORT void low_pow( void )
{
	UW	basepri;

	basepri = get_basepri();
	Asm("cpsid i");
	set_basepri(0);
	Asm("dsb");
	Asm("wfi");
	set_basepri(basepri);
	Asm("cpsie i");
}

/*
 * Move to suspend mode
 */
EXPORT void off_pow( void )
{
}


#endif /* MTKBSP_STM32CUBE */
