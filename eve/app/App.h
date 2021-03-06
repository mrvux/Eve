
/*
 Copyright (c) 2014, The eve Project
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
#ifndef __EVE_APPLICATION_APP_H__
#define __EVE_APPLICATION_APP_H__

#ifndef __EVE_EVT_INCLUDES_H__
#include "eve/evt/Includes.h"
#endif

#ifndef __EVE_SYSTEM_CURSOR_H__
#include "eve/sys/win32/Cursor.h"
#endif

#ifndef __EVE_SYSTEM_KEYBOARD_H__
#include "eve/sys/win32/Keyboard.h"
#endif

#ifndef __EVE_SYSTEM_MOUSE_H__
#include "eve/sys/shared/Mouse.h"
#endif

#ifndef __EVE_SYSTEM_NOTIFICATION_H__
#include "eve/sys/win32/Notification.h"
#endif

#ifndef __EVE_SYSTEM_VIEW_H__
#include "eve/sys/shared/View.h"
#endif

#ifndef __EVE_THREADING_SPIN_LOCK_H__
#include "eve/thr/SpinLock.h"
#endif 

#ifndef __EVE_TIME_TIMER_H__
#include "eve/time/Timer.h"
#endif


namespace eve
{
	namespace app
	{
		/** 
		* \class eve::app::App
		*
		* \brief Main application class using single or multiple window.
		*
		* \note extends eve::mem::Pointer
		*/
		class App final
			: public eve::mem::Pointer
		{

			friend class eve::mem::Pointer;

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		private:
			static eve::app::App *				m_p_instance;		//!< Class unique instance.
			static eve::time::Timer *			m_p_timer;			//!< Application timer, launched at startup.

		private:
			bool								m_bRunning;			//!< Application main loop running state.

		private:
			std::vector<eve::sys::View*> *		m_pVecViews;		//!< Application view(s) container.
			eve::thr::SpinLock *				m_pFence;			//!< Application view(s) container protection fence.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(App);
			EVE_PROTECT_DESTRUCTOR(App);

			
		public:
			/** \brief Create unique instance. */
			static eve::app::App * create_instance(void);
			/** \brief Get unique instance. */
			static eve::app::App * get_instance(void);
			/** \brief Release unique instance */
			static void release_instance(void);


		private:
			/** \brief Class constructor. */
			explicit App(void);


		private:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void) override;


		public:
			/** \brief Launch application main loop. */
			void runApp(void);


		public:
			/** 
			* \brief Add view to application.
			* View is created and returned as a TView pointer.
			* App takes ownership of newly created view.
			* Template class TView must inherit eve::sys::View.
			* Inheritance is tested in DEBUG mode, not in RELEASE mode.
			*/
			template<class TView>
			TView * addView(void);
			/** 
			* \brief Release ownership of target view.
			* Return true if target view was contained.
			*/
			bool removeView(eve::sys::View * p_pView);
			/**
			* \brief Remove and release target view.
			* Return true if target view was contained.
			*/
			bool releaseView(eve::sys::View * p_pView);


		public:
			/** \brief Application exit event handler. */
			void cb_evtApplicationExit(eve::evt::EventArgs & p_arg);


			///////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \brief Get elapsed time since application startup in milliseconds. */
			static int64_t get_elapsed_time(void);

		}; // class App

	} // namespace app

} // namespace eve

/** 
* \def EveApp 
* \brief Convenience macro to access application instance. 
*/
#define EveApp	eve::app::App::get_instance()


//=================================================================================================
template<class TView>
TView * eve::app::App::addView(void)
{
	EVE_ASSERT( (std::is_base_of<eve::sys::View, TView>::value) );

	TView * view = EVE_CREATE_PTR(TView);

	m_pFence->lock();
	m_pVecViews->push_back(view);
	m_pFence->unlock();

	view->start();

	return view;
}



//=================================================================================================
inline int64_t eve::app::App::get_elapsed_time(void) { EVE_ASSERT(m_p_timer); return m_p_timer->getElapsedTime(); }
/**
* \def EveAppElapsedTime
* \brief Convenience macro to access time since application startup in milliseconds.
*/
#define EveAppElapsedTime	eve::app::App::get_elapsed_time()


#if defined(EVE_OS_WIN)
/** 
* \def EVE_APPLICATION 
* \brief Convenience macro to create application entry point and launch application. 
*/
#define EVE_APPLICATION( VIEW )																			\
	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 	\
	{																									\
		eve::app::App *	pApp = eve::app::App::create_instance();										\
		pApp->addView<VIEW>();																			\
		pApp->runApp();																					\
		eve::app::App::release_instance();																\
		return 0;																						\
	}

#elif defined(EVE_OS_DARWIN)
/** 
* \def EVE_APPLICATION 
* \brief Convenience macro to create application entry point and launch application. 
*/
#define EVE_APPLICATION( VIEW )												\
	int main(int argc, char * const argv[]) 								\
	{																		\
		eve::app::App *	pApp = eve::app::App::create_instance();			\
		pApp->addView<VIEW>();												\
		pApp->runApp();														\
		eve::app::App::release_instance();									\
		return 0;															\
	}

#endif


#endif // __EVE_APPLICATION_APP_H__
