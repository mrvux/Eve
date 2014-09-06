
/*
 Copyright (c) 2014, The Eve Project
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 * Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 
 * Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 
 * Neither the name of the {organization} nor the names of its
 contributors may be used to endorse or promote products derived from
 this software without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once
#ifndef __EVE_MEMORY_POINTER_H__
#define __EVE_MEMORY_POINTER_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "core/Includes.h"
#endif


namespace eve
{
	namespace memory
	{

		/** 
		 * @class memory::Pointer
		 * Abstract base pointer class
		 */
		class Pointer
		{

			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY( Pointer )

		protected:
			/** Class constructor. */
			Pointer(void);
			/** Class destructor. */
			EVE_PROTECT_DESTRUCTOR(Pointer)


		protected:
			/** Alloc and init class members. (pure virtual) */
			virtual void init(void) = 0;
			/** Release and delete class members. (pure virtual) */
			virtual void release(void) = 0;


		public:
			/** Create and initialize new pointer. */
			template<class T>
			static T * create_ptr(void);

			/** Release and delete target pointer. */
			template<class T>
			static void release_ptr(T * p_pPtr);

		}; // class Pointer

	} // namespace memory

} // namespace eve


//=================================================================================================
template<class T>
T * eve::memory::Pointer::create_ptr(void)
{
	T * ptr = new T();
	ptr->init();
	return ptr;
}
// Convenience MACRO.
#define EVE_CREATE_PTR( T )	\
	eve::memory::Pointer::create_ptr<T>();


//=================================================================================================
template<class T>
void eve::memory::Pointer::release_ptr(T * p_pPtr)
{
#ifndef NDEBUG
	assert(p_pPtr);
#endif

	p_pPtr->release();
	delete p_pPtr;
}
// Convenience MACRO.
#define EVE_RELEASE_PTR( PTR )	\
	eve::memory::Pointer::release_ptr(PTR);	\
	PTR = nullptr;

#endif //__EVE_MEMORY_POINTER_H__