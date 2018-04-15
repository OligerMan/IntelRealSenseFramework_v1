/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or non-disclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2013-2016 Intel Corporation. All Rights Reserved.

*******************************************************************************/
/** @file PXCHandModule.h
    Defines the PXCHandModule interface, which gives access the hand module's configuration and output data.
 */
#pragma once
#include "pxcsensemanager.h"
#include "RealSense/Hand/HandModule.h"

/**
    @Class PXCHandModule 
    The main interface to the hand module's classes.\n
    Use this interface to access the hand module's configuration and output data.
*/
typedef Intel::RealSense::Hand::HandModule PXCHandModule;
typedef Intel::RealSense::Hand::HandConfiguration PXCHandConfiguration;
typedef Intel::RealSense::Hand::HandData PXCHandData;
