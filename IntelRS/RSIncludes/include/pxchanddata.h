/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2013-2016 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "pxcimage.h"
#include "RealSense/Hand/HandData.h"

/**
    @class PXCHandData
    @brief This class holds all the output of the hand tracking process.
    
    Each instance of this class holds the information of a specific frame.
*/
typedef Intel::RealSense::Hand::HandData PXCHandData;
