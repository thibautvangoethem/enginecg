engine.o: engine.cc easy_image.h ini_configuration.h Color.h Point2D.h \
 Line2D.h l_parser.h vector3d.h figure3D.h face3D.h simpleGenerations.h \
 imgUtils.h ZBuffer.h Light.h L2DEngine.h Engine3D.h
	$(CC) $(CXXFLAGS) -c $< -o $@
