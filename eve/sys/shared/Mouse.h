
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
#ifndef __EVE_SYSTEM_MOUSE_H__
#define __EVE_SYSTEM_MOUSE_H__


namespace eve
{
	namespace sys
	{

		/** \brief Mouse button enumeration. */
		enum MouseButton
		{
			btn_Unused,
			/// Unknown mouse button
			btn_Unknown,
			/// Left mouse button
			btn_Left,
			/// Middle mouse button
			btn_Middle,
			/// Right mouse button
			btn_Right,
			/// Mouse wheel up
			btn_WheelUp,
			/// Mouse wheel down
			btn_WheelDown,
			/// Scroll left
			btn_ScrollLeft,
			/// Scroll right
			btn_ScrollRight,
			/// X UIButton
			btn_X

		}; // enum MouseButton


		/** \brief Mouse button state enumeration. */
		enum MouseButtonState
		{
			btnState_Unused,
			/// Unknown state
			btnState_Unknown,
			/// Down state
			btnState_Down,
			/// Up state
			btnState_Up,
			/// Double Click state
			btnState_DbleClick

		}; // enum MouseButtonState

	} // namespace sys

} // namespace eve

#endif // __EVE_SYSTEM_MOUSE_H__
