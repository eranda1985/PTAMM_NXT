# DO NOT DELETE THIS LINE -- make depend depends on it.


#3DS modelling game dependencies
3DSLIB = -l3ds
3DSFILES =	ModelsGame.o\
		ModelBrowser.o\
		ModelControls.o\
		MGButton.o\
		Model3ds.o\
		ModelsGameData.o

EXTRA_CFLAGS:= -DENABLE_MODELS_GAME

# Edit the lines below to point to any needed include and link paths
# Or to change the compiler's optimization flags
CC = g++
COMPILEFLAGS = -I /usr/local/include /usr/include/GL /usr/include -D_LINUX -D_REENTRANT -Wall  -O3 -march=nocona -msse3 -fno-strict-aliasing
LIBS = -lARgsub -lARvideo -lAR -lXi -lX11 -lm -lpthread -lgstreamer-0.10 -lgobject-2.0 -lgmodule-2.0 -lxml2 -lgthread-2.0 -lrt -lglib-2.0 -L/usr/X11R6/lib
LINKFLAGS = $(LIBS) -lGVars3 -lcvd -llapack -lblas -lglut -lGLU -lopencv_core -lopencv_nonfree -lopencv_imgproc -lopencv_highgui -lopencv_objdetect -lopencv_calib3d $(3DSLIB) -L /usr/local/lib

# Edit this line to change video source
VIDEOSOURCE = VideoSource_Linux_V4L.o

OBJECTS=	main.o\
		GLWindow2.o\
		ROSService.o\
		GLWindowMenu.o\
		$(VIDEOSOURCE)\
		System.o \
		ATANCamera.o\
		KeyFrame.o\
		MapPoint.o\
		Map.o\
		SmallBlurryImage.o\
		ShiTomasi.o \
		HomographyInit.o \
		MapMaker.o \
		Bundle.o \
		PatchFinder.o\
		Relocaliser.o\
		MiniPatch.o\
		MapViewer.o\
		ARDriver.o\
		EyeGame.o\
		Tracker.o\
		tinyxml.o\
		tinyxmlerror.o\
		tinyxmlparser.o\
		MapLockManager.o\
		MD5.o\
		MD5Wrapper.o\
		MapSerializer.o\
		Games.o\
		Utils.o\
		ShooterGame.o\
		ShooterGameTarget.o\
		$(3DSFILES)


CALIB_OBJECTS=	GLWindow2.o\
		GLWindowMenu.o\
		$(VIDEOSOURCE)\
		CalibImage.o \
		CalibCornerPatch.o\
		ATANCamera.o \
		CameraCalibrator.o

All: PTAMM CameraCalibrator

PTAMM: $(OBJECTS)
	$(CC) -o PTAMM $(OBJECTS) $(LINKFLAGS)

CameraCalibrator:$(CALIB_OBJECTS)
	$(CC) -o CameraCalibrator $(CALIB_OBJECTS) $(LINKFLAGS)


%.o: %.cc
	$(CC) $< -o $@ -c $(COMPILEFLAGS) $(EXTRA_CFLAGS)

clean:
	rm *.o


depend:
	rm dependecies; touch dependencies
	makedepend -fdependencies $(INCLUDEFLAGS) $(MOREINCS) *.cc *.h


-include dependencies









