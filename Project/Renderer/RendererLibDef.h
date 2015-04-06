#ifndef _RENDERER_LIB_DEF_H_
#define _RENDERER_LIB_DEF_H_

#ifndef RENDER_DECLSPEC

	#ifdef RENDERER_EXPORTS
		#define RENDER_DECLSPEC __declspec(dllexport)  
	#else  
		#define RENDER_DECLSPEC __declspec(dllimport)  
	#endif  //end ofISH

#endif //RENDER_DECLSPEC

#pragma warning(disable:4251)  

#endif