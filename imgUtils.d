imgUtils.o: imgUtils.cc easy_image.h ini_configuration.h Color.h \
 Point2D.h Line2D.h l_parser.h vector3d.h figure3D.h face3D.h \
 simpleGenerations.h imgUtils.h
	$(CC) $(CXXFLAGS) -c $< -o $@
