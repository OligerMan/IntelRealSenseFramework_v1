/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or non-disclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2013-2016 Intel Corporation. All Rights Reserved.

*******************************************************************************/
/**
Defines the PXCHandModule interface, which gives access the hand module's configuration and output data.
*/
#pragma once
#include "RealSense/SenseManager.h"
#include "RealSense/VideoModuleCommon.h"
#include "RealSense/Hand/HandConfiguration.h"
#include "RealSense/Hand/HandData.h"

namespace Intel {
    namespace RealSense {
        namespace Hand {
            /**
            @Class PXCHandModule
            The main interface to the hand module's classes.\n
            Use this interface to access the hand module's configuration and output data.
            */
            class HandModule : public VideoModuleCommon<HandModule>
            {
            public:

				PXC_CUID_OVERWRITE(PXC_UID('H', 'A', 'N', 'N'));

                /**
                @brief Create a new instance of the hand module's active configuration.
                Multiple configuration instances can be created in order to define different configurations for different stages of the application.
                You can switch between the configurations by calling the ApplyChanges method of the required configuration instance.
                @return A pointer to the configuration instance.
                @see HandConfiguration
                */
                virtual HandConfiguration* PXCAPI CreateActiveConfiguration() = 0;

                /**
                @brief Create a new instance of the hand module's current output data.
                Multiple instances of the output can be created in order to store previous tracking states.
                @return A pointer to the output data instance.
                @see HandData
                */
                virtual HandData* PXCAPI CreateOutput() = 0;
            };
        }
    }
}
