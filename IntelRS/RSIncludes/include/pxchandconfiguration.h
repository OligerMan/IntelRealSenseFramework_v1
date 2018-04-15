/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2013-2016 Intel Corporation. All Rights Reserved.

*******************************************************************************/
/** @file PXCHandConfiguration.h
    Defines the PXCHandConfiguration interface, which defines the configuration options of the hand module
 */
#pragma once
#include "pxchanddata.h"
#include "RealSense/Hand/HandConfiguration.h"

/**
    @class PXCHandConfiguration
    @brief Handles all the configuration options of the hand module.
    Use this interface to configure the tracking, alerts, gestures and output options.
    @note Updated configuration is applied only when ApplyChanges is called.
*/
typedef Intel::RealSense::Hand::HandConfiguration PXCHandConfiguration;
 