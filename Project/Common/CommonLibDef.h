#ifndef _COMMON_LIB_DEF_H_
#define _COMMON_LIB_DEF_H_

#ifndef DECLSPEC

	#ifdef COMMON_EXPORTS
		#define DECLSPEC __declspec(dllexport)  
	#else  
		#define DECLSPEC __declspec(dllimport)  
	#endif  //end of #ifndef COMMON_EXPORTS

#endif // end of #ifndef DECLSPEC

#pragma warning(disable:4251)  

#endif