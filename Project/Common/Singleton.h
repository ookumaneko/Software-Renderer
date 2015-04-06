// This class is based on Scott Bilas' singleton class from
// Game Programming Gems (2000), chapter 1.3, Automatic Single Utility

#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include <cassert>

namespace Common
{

template <typename T> class Singleton
{
	public:

		Singleton( void )
		{
			assert( !m_singleton );
			int offset = (int)(T*)1 - (int)( Singleton <T>* )(T*)1;
			m_singleton = (T*)( (int)this + offset );
		}

	   virtual ~Singleton( void ) {  assert( m_singleton );  m_singleton = 0;  }

		// Accessors
		static T& GetInstance	( void ) {  assert( m_singleton );  return ( *m_singleton );  }

		static T* GetInstancePtr( void ) 
		{  
			assert( m_singleton ); 
			return ( m_singleton );  
		}

	private:
		static T* m_singleton;

};

template <typename T> T* Singleton <T>::m_singleton = 0;

} // end of namespace ish

#endif // end of _SINGLETON_H