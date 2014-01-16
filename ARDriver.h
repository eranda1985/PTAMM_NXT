// -*- c++ -*-
// Copyright 2009 Isis Innovation Limited
// ARDriver.h
// This file declares the ARDriver class
//
// ARDriver provides basic graphics services for drawing augmented
// graphics. It manages the OpenGL setup and the camera's radial
// distortion so that real and distorted virtual graphics can be
// properly blended.
//
#ifndef __AR_Driver_H
#define __AR_Driver_H
#include <TooN/se3.h>
#include "ATANCamera.h"
#include "GLWindow2.h"
#include "ROSService.h"
#include "OpenGL.h"
#include <cvd/image.h>
#include <cvd/rgb.h>
#include <cvd/byte.h>

#include "MapViewer.h"
#include <AR/gsub.h>
#include <AR/video.h>
#include <AR/param.h>
#include <AR/ar.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <map>
#include <vector>

#ifndef NAN
#include <limits>
#endif 

namespace PTAMM {

using namespace std;
using namespace CVD;

class Map;
class MapViewer;

class ARDriver
{
  public:
    ARDriver(const ATANCamera &cam, ImageRef irFrameSize, GLWindow2 &glw, Map &map, MapViewer& mapviewer, ROSService& _driver);
	void Render(CVD::Image<CVD::Rgb<CVD::byte> > inputVideo, SE3<> se3CamFromWorld, bool bLost);
    void Reset();
    void Init();
    void drawMyMarker(SE3<> pose);
      void argConvGlpara2( TooN::Vector<3> _trans, Matrix<3> rota, double gl_para[16] );

    void HandleClick(int nButton, ImageRef irWin );
    void HandleKeyPress( std::string sKey );
    void AdvanceLogic();
    void LoadGame(std::string sName);
    void DriveRobot(double x, double y, Vector<3> _start,MapViewer* mpViewer);
    void ShowARMarkers(CVD::Image<CVD::Rgb<CVD::byte> > inputVideo);
    void cleanup(void);
    void draw(void);
  
    void SetCurrentMap(Map &map) { mpMap = &map; mnCounter = 0; }
    inline double GetOffSetX(){return offset_x;}
    inline double GetOffSetZ(){return offset_z;}
    inline double GetOffSetY(){return offset_y;};
    int robot_status;
    int markerCount;
    int n_markers;
    int g_markers;
    std::string last_modified_marker;

  protected:
    void DrawFadingGrid();
    void MakeFrameBuffer();
    void DrawFBBackGround();
    void DrawDistortedFB();
    void SetFrustum();
    static void GUICommandCallBack(void* ptr, std::string sCommand, std::string sParams);
    
    bool PosAndDirnInPlane(Vector<2> v2VidCoords, Vector<2> &v2Pos, Vector<2> &v2Dirn);
    void WaitForRobot(ARDriver* ad_, Vector<3> _start);

    
  protected:
    ATANCamera mCamera;
    GLWindow2 &mGLWindow;
    Map *mpMap;
    MapViewer *mapViewer;
    ROSService driver;
    std::vector<std::string> Commands;
  
    // Texture stuff:
    GLuint mnFrameBuffer;
    GLuint mnFrameBufferTex;
    GLuint mnFrameTex;
    
    int mnCounter;
    ImageRef mirFBSize;
    ImageRef mirFrameSize;
    SE3<> mse3CfromW;
    bool mbInitialised;
    double offset_x;
    double offset_z;
    double offset_y;
    int thresh;
    char           *patt_name;
    char           *patt_name2;
    int             patt_id;
    int             patt_id2;
    double          patt_width;
    double          patt_center[2];
    double          patt_trans[3][4];
    double          patt_trans2[3][4];
	struct position {
		std::string type;
		double markerPosition[3];
	};
	std::map <int, position > markerPositions;
	int tempMarkerCount;


	Image<Rgba<CVD::byte> > mLostOverlay;

	cv::Mat bgra;
	cv::Mat abgr;
	cv::Mat rgb;

};

}

#endif
