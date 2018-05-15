Engine3D.o: Engine3D.cc Engine3D.h figure3D.h Color.h face3D.h Point2D.h \
 vector3d.h ini_configuration.h Light.h ZBuffer.h Line2D.h imgUtils.h \
 easy_image.h L3DEngine.h Fractals3D.h
	$(CC) $(CXXFLAGS) -c $< -o $@
