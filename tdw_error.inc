/** ======================================================================== **\
	Error

| Description:

| Version:
	1.0.4

| Dependencies:
	- AMX Assembly (https://github.com/Zeex/amx_assembly) (optional)

| Compatible with the JIT plugin:
	Yes

| License:
	Copyright (c) 2017 Double V

	This software is provided 'as-is', without any express or implied
	warranty. In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	1.	The origin of this software must not be misrepresented; you must not
		claim that you wrote the original software. If you use this software
		in a product, an acknowledgement in the product documentation would be
		appreciated but is not required.
	2.	Altered source versions must be plainly marked as such, and must not be
		misrepresented as being the original software.
	3.	This notice may not be removed or altered from any source distribution.
\** ======================================================================== **/

#if defined _inc_tdw_error
	#undef _inc_tdw_error
#endif

#if defined _TDW_ERROR
	#endinput
#endif

#define _TDW_ERROR

#tryinclude "amx\amx_jit"
#tryinclude "amx\frame_info"
#tryinclude "amx\amx_memory"

#if defined AMX_MEMORY_INC && defined FRAME_INFO_INC && defined AMX_JIT_INC
	#define RaiseError RaiseErrorL
#else
	#define RaiseError RaiseErrorA
#endif

const TDW_ERR_MESSAGE_SIZE = 54;

enum {
	// from amx.h
	AMX_ERR_NONE,
	/* reserve the first 15 error codes for exit codes of the abstract machine */
	AMX_ERR_EXIT,         /* forced exit */
	AMX_ERR_ASSERT,       /* assertion failed */
	AMX_ERR_STACKERR,     /* stack/heap collision */
	AMX_ERR_BOUNDS,       /* index out of bounds */
	AMX_ERR_MEMACCESS,    /* invalid memory access */
	AMX_ERR_INVINSTR,     /* invalid instruction */
	AMX_ERR_STACKLOW,     /* stack underflow */
	AMX_ERR_HEAPLOW,      /* heap underflow */
	AMX_ERR_CALLBACK,     /* no callback, or invalid callback */
	AMX_ERR_NATIVE,       /* native function failed */
	AMX_ERR_DIVIDE,       /* divide by zero */
	AMX_ERR_SLEEP,        /* go into sleepmode - code can be restarted */
	AMX_ERR_INVSTATE,     /* invalid state for this access */

	AMX_ERR_MEMORY = 16,  /* out of memory */
	AMX_ERR_FORMAT,       /* invalid file format */
	AMX_ERR_VERSION,      /* file is for a newer version of the AMX */
	AMX_ERR_NOTFOUND,     /* function not found */
	AMX_ERR_INDEX,        /* invalid index parameter (bad entry point) */
	AMX_ERR_DEBUG,        /* debugger cannot run */
	AMX_ERR_INIT,         /* AMX not initialized (or doubly initialized) */
	AMX_ERR_USERDATA,     /* unable to set user data field (table full) */
	AMX_ERR_INIT_JIT,     /* cannot initialize the JIT */
	AMX_ERR_PARAMS,       /* parameter error */
	AMX_ERR_DOMAIN,       /* domain error, expression result does not fit in range */
	AMX_ERR_GENERAL      /* general error (unknown or unspecific error) */
};

static stock messages[][TDW_ERR_MESSAGE_SIZE char] = {
	// from amxaux.c
	/* AMX_ERR_NONE      */ !"(none)",
	/* AMX_ERR_EXIT      */ !"Forced exit",
	/* AMX_ERR_ASSERT    */ !"Assertion failed",
	/* AMX_ERR_STACKERR  */ !"Stack/heap collision (insufficient stack size)",
	/* AMX_ERR_BOUNDS    */ !"Array index out of bounds",
	/* AMX_ERR_MEMACCESS */ !"Invalid memory access",
	/* AMX_ERR_INVINSTR  */ !"Invalid instruction",
	/* AMX_ERR_STACKLOW  */ !"Stack underflow",
	/* AMX_ERR_HEAPLOW   */ !"Heap underflow",
	/* AMX_ERR_CALLBACK  */ !"No (valid) native function callback",
	/* AMX_ERR_NATIVE    */ !"Native function failed",
	/* AMX_ERR_DIVIDE    */ !"Divide by zero",
	/* AMX_ERR_SLEEP     */ !"(sleep mode)",
	/* 13 */                !"(reserved)",
	/* 14 */                !"(reserved)",
	/* 15 */                !"(reserved)",
	/* AMX_ERR_MEMORY    */ !"Out of memory",
	/* AMX_ERR_FORMAT    */ !"Invalid/unsupported P-code file format",
	/* AMX_ERR_VERSION   */ !"File is for a newer version of the AMX",
	/* AMX_ERR_NOTFOUND  */ !"File or function is not found",
	/* AMX_ERR_INDEX     */ !"Invalid index parameter (bad entry point)",
	/* AMX_ERR_DEBUG     */ !"Debugger cannot run",
	/* AMX_ERR_INIT      */ !"AMX not initialized (or doubly initialized)",
	/* AMX_ERR_USERDATA  */ !"Unable to set user data field (table full)",
	/* AMX_ERR_INIT_JIT  */ !"Cannot initialize the JIT",
	/* AMX_ERR_PARAMS    */ !"Parameter error",
	/* AMX_ERR_DOMAIN    */ !"Domain error, expression result does not fit in range",
	/* AMX_ERR_GENERAL   */ !"General error (unknown or unspecific error)"
};

stock RaiseErrorL(code)
{
	if (GetJITGeneratorVersion())
		RaiseErrorA(code);
	new
		hdr[AMX_HDR],
		ret_addr = GetCurrentFrameReturn();
	GetAmxHeader(hdr);
	ret_addr += hdr[AMX_HDR_COD] - hdr[AMX_HDR_DAT];
	WriteAmxMemory(ret_addr,     _:RelocateOpcode(OP_HALT));
	WriteAmxMemory(ret_addr + 4, code);
	return 1;
}

stock RaiseErrorA(code)
{
	switch (code) {
		case AMX_ERR_NONE: {
			#emit halt AMX_ERR_NONE
		}
		case AMX_ERR_EXIT: {
			#emit halt AMX_ERR_EXIT
		}
		case AMX_ERR_ASSERT: {
			#emit halt AMX_ERR_ASSERT
		}
		case AMX_ERR_STACKERR: {
			#emit halt AMX_ERR_STACKERR
		}
		case AMX_ERR_BOUNDS: {
			#emit halt AMX_ERR_BOUNDS
		}
		case AMX_ERR_MEMACCESS: {
			#emit halt AMX_ERR_MEMACCESS
		}
		case AMX_ERR_INVINSTR: {
			#emit halt AMX_ERR_INVINSTR
		}
		case AMX_ERR_STACKLOW: {
			#emit halt AMX_ERR_STACKLOW
		}
		case AMX_ERR_HEAPLOW: {
			#emit halt AMX_ERR_HEAPLOW
		}
		case AMX_ERR_CALLBACK: {
			#emit halt AMX_ERR_CALLBACK
		}
		case AMX_ERR_NATIVE: {
			#emit halt AMX_ERR_NATIVE
		}
		case AMX_ERR_DIVIDE: {
			#emit halt AMX_ERR_DIVIDE
		}
		case AMX_ERR_SLEEP: {
			#emit halt AMX_ERR_SLEEP
		}
		case AMX_ERR_INVSTATE: {
			#emit halt AMX_ERR_INVSTATE
		}
		case AMX_ERR_MEMORY: {
			#emit halt AMX_ERR_MEMORY
		}
		case AMX_ERR_FORMAT: {
			#emit halt AMX_ERR_FORMAT
		}
		case AMX_ERR_VERSION: {
			#emit halt AMX_ERR_VERSION
		}
		case AMX_ERR_NOTFOUND: {
			#emit halt AMX_ERR_NOTFOUND
		}
		case AMX_ERR_INDEX: {
			#emit halt AMX_ERR_INDEX
		}
		case AMX_ERR_DEBUG: {
			#emit halt AMX_ERR_DEBUG
		}
		case AMX_ERR_INIT: {
			#emit halt AMX_ERR_INIT
		}
		case AMX_ERR_USERDATA: {
			#emit halt AMX_ERR_USERDATA
		}
		case AMX_ERR_INIT_JIT: {
			#emit halt AMX_ERR_INIT_JIT
		}
		case AMX_ERR_PARAMS: {
			#emit halt AMX_ERR_PARAMS
		}
		case AMX_ERR_DOMAIN: {
			#emit halt AMX_ERR_DOMAIN
		}
		case AMX_ERR_GENERAL: {
			#emit halt AMX_ERR_GENERAL
		}
	}
	return 1;
}

stock StrError(dest[], errnum, bool:packed = false, size = sizeof dest)
{
	dest[0] = '\0';
	if (errnum < 0 || errnum >= sizeof messages)
		return strcat(dest, !"(unknown)", size);
	if (_:packed == 0)
		return strunpack(dest, messages[errnum], size);
	return strcat(dest, messages[errnum], size);
}
