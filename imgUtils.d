imgUtils.o: imgUtils.cc easy_image.h Color.h ini_configuration.h \
 Point2D.h Line2D.h l_parser.h vector3d.h figure3D.h face3D.h \
 simpleGenerations.h ZBuffer.h Light.h To2DConverter.h Engine3D.h \
 imgUtils.h
	$(CC) $(CXXFLAGS) -c $< -o $@