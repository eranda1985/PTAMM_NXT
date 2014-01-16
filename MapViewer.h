// -*- c++ -*-
// Copyright 2009 Isis Innovation Limited
//
// MapViewer.h
//
// Defines the MapViewer class
//
// This defines a simple map viewer widget, which can draw the 
// current map and the camera/keyframe poses within it.
//
#ifndef __MAP_VIEWER_H
#define __MAP_VIEWER_H

#include "Map.h"
#include <TooN/TooN.h>
#include <TooN/se3.h>
#include <sstream>
#include "GLWindow2.h"
#include <map>
#include <vector>

namespace PTAMM {

using namespace TooN;

class Map;

class MapViewer
{
  public:
	struct position
	    {
	    std::string type;
		double markerPosition[3];
	    };
	MapViewer(std::vector<Map*> &maps, Map *map, GLWindow2 &glw);
    void DrawMap(SE3<> se3CamFromWorld, double offset_X, double offset_Y,double offset_Z, int count,int n_markercount, int g_markercount,std::string lastmodifiedmarker);
    std::string GetMessageForUser();
    void SwitchMap( Map * map, bool bForce = false );

    void ViewNextMap();
    void ViewPrevMap();
    void ViewCurrentMap();
    Vector<3> GetCurrentXZPosition();
    inline std::vector<Vector<2> > GetPathToARMarker(){ return pathToARMarkerArray; };
    inline double GetYaw() {return yaw;};
    std::map <int, position > markerPositions;
    int markerCount;
    int totalCount;
    int default_NMarkers;
    int default_GMarkers;
    bool Is_N_MarkersIncremented(int count);
    bool Is_G_MarkersIncremented(int count);


  protected:
    std::vector<Map*> & mvpMaps;     // Reference to all of the maps
    Map * mpMap, *mpViewingMap;      // the active tracking map, and the map being viewed
    GLWindow2 &mGLWindow;
    SE3<> currPose;
    Vector<2> pathToARMarker;
    std::vector<Vector<2> > pathToARMarkerArray;
    double yaw;
    
    void DrawGrid(double offset_X, double offset_Y, double offset_Z);
    void DrawMapDots();
    void DrawCamera(SE3<> se3, bool bSmall=false, Map* sourceMap = NULL);
    void SetupFrustum();
    void SetupModelView(SE3<> se3WorldFromCurrent = SE3<>());
    
    Vector<3> mv3MassCenter;
    SE3<> mse3ViewerFromWorld;

    std::ostringstream mMessageForUser;
    bool mbBrowseMode;                            // Map browsing mode enabled?
    SE3<> newPose;
};

}

#endif
