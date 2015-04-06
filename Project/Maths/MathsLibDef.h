#ifndef _MATHS_LIB_DEF_H_
#define _MATHS_LIB_DEF_H_

#ifndef DECLSPEC

	#ifdef MATHS_EXPORTS
		#define DECLSPEC __declspec(dllexport)  
	#else  
		#define DECLSPEC __declspec(dllimport)  
	#endif  //end ofISH

#endif //DECLSPEC

#pragma warning(disable:4251)  

#endif