
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
#ifndef __EVE_DIRECTX11_DEVICE_H__
#define __EVE_DIRECTX11_DEVICE_H__

#ifndef __EVE_DIRECTX11_ENUMS_H__
	#include "Enums.h"
#endif

#ifndef __EVE_MESSAGING_INCLUDES_H__
#include "eve/mess/Includes.h"
#endif

namespace eve { namespace dx11 { class Context; } }

namespace eve 
{
	namespace dx11
	{
		/**
		* \class eve::dx11::Device
		*
		* \brief DirectX11 Device
		* Create a DirectX11 Device
		*
		*/
		class Device
		{
			friend class eve::dx11::Context;

			private:	
				void dxRelease();

			protected:
				~Device();

			public: 
				Device();
				void Init();
				EVE_FORCE_INLINE ID3D11Device* GetDevice() { return this->m_p_device; }
				EVE_FORCE_INLINE ID3D11DeviceContext* GetImmediateContext() { return this->m_p_immediateContext; }
				EVE_FORCE_INLINE IDXGIFactory1* GetFactory() { return this->m_p_factory; }

				EVE_FORCE_INLINE eve::dx11::FeatureLevel GetFeatureLevel() { return this->m_featureLevel; }
				EVE_FORCE_INLINE bool IsAtLeastLevel11() { return this->m_featureLevel > eve::dx11::FeatureLevel::f11; }

			private:
				IDXGIFactory1* m_p_factory; //DXGI Factory, required to create swapchain
				ID3D11Device* m_p_device; //Device pointer
				ID3D11DeviceContext* m_p_immediateContext; //Immediate context to submit commands to GPU
				eve::dx11::FeatureLevel m_featureLevel; //Real device feature level
				


		};
	} //namespace dx11

} //namespace eve

#endif // __EVE_DIRECTX11_DEVICE_H__
