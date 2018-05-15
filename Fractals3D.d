Fractals3D.o: Fractals3D.cc Fractals3D.h figure3D.h Color.h face3D.h \
 Point2D.h vector3d.h ini_configuration.h Line2D.h Engine3D.h Light.h \
 ZBuffer.h imgUtils.h easy_image.h L3DEngine.h
	$(CC) $(CXXFLAGS) -c $< -o $@
