#ifndef HELPER_HEADER
	#define HELPER_HEADER
	#define MACROS_M

	//Global variable g (all available to others)
	extern int global;
	
	//Helper global variable g23 (it should not be exposed to others)
	#ifdef GLOBAL_G23
		extern int global23;
	#endif
#endif	//HELPER_HEADER

