//----------------------------------------------------------------------------
//
//  Copyright (C) 2004-2011 by EMGU. All rights reserved.
//
//----------------------------------------------------------------------------

#include "objdetect_c.h"

void CvHOGDescriptorPeopleDetectorCreate(CvSeq* seq) 
{   
   std::vector<float> v = cv::HOGDescriptor::getDefaultPeopleDetector();  
   cvSeqPushMulti(seq, &v.front(), v.size()); 
}
cv::HOGDescriptor* CvHOGDescriptorCreateDefault() { return new cv::HOGDescriptor; }

cv::HOGDescriptor* CvHOGDescriptorCreate(
   cv::Size* _winSize, 
   cv::Size* _blockSize, 
   cv::Size* _blockStride,
   cv::Size* _cellSize, 
   int _nbins, 
   int _derivAperture, 
   double _winSigma,
   int _histogramNormType, 
   double _L2HysThreshold, 
   bool _gammaCorrection)
{
   return new cv::HOGDescriptor(*_winSize, *_blockSize, *_blockStride, *_cellSize, _nbins, _derivAperture, _winSigma, _histogramNormType, _L2HysThreshold, _gammaCorrection);
}

void CvHOGSetSVMDetector(cv::HOGDescriptor* descriptor, std::vector<float>* vector) 
{ 
   descriptor->setSVMDetector(*vector); 
}

void CvHOGDescriptorRelease(cv::HOGDescriptor* descriptor) { delete descriptor; }

void CvHOGDescriptorDetectMultiScale(
   cv::HOGDescriptor* descriptor, 
   CvArr* img, 
   CvSeq* foundLocations,
   double hitThreshold, 
   CvSize winStride,
   CvSize padding, 
   double scale,
   int groupThreshold)
{
   cvClearSeq(foundLocations);

   std::vector<cv::Rect> rects;
   cv::Mat mat = cv::cvarrToMat(img);
   descriptor->detectMultiScale(mat, rects, hitThreshold, winStride, padding, scale, groupThreshold);
   if (rects.size() > 0)
      cvSeqPushMulti(foundLocations, &rects[0], rects.size());
}

void CvHOGDescriptorCompute(
    cv::HOGDescriptor *descriptor,
    CvArr *img, 
    std::vector<float> *descriptors,
    CvSize winStride,
    CvSize padding,
    CvSeq* locationSeq) 
{
    cv::Mat mat = cv::cvarrToMat(img);
    std::vector<cv::Point> location(0);
    if (locationSeq)
    {
       location.resize(locationSeq->total);
       cvSeqPopMulti(locationSeq, &location[0], locationSeq->total);
    }
    
    descriptor->compute(
       mat, 
       *descriptors,
       winStride,
       padding,
       location); 
}


/*
CVAPI(void) cvHOGDescriptorDetect(
   cv::HOGDescriptor* descriptor, 
   CvArr* img, 
   CvSeq* foundLocations,
   double hitThreshold, 
   CvSize winStride,
   CvSize padding)
{
   cvClearSeq(foundLocations);

   std::vector<cv::Point> hits;
   cv::Mat mat = cv::cvarrToMat(img);
   descriptor->detect(mat, hits, hitThreshold, winStride, padding);
   cvSeqPushMulti(foundLocations, &hits.front(), hits.size());
}*/
