L3DEngine.o: L3DEngine.cc L3DEngine.h easy_image.h ini_configuration.h \
 Line2D.h Point2D.h Color.h imgUtils.h figure3D.h face3D.h vector3d.h \
 ZBuffer.h Light.h l_parser.h
	$(CC) $(CXXFLAGS) -c $< -o $@
