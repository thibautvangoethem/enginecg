Engine3D.o: Engine3D.cc Engine3D.h figure3D.h Color.h face3D.h Point2D.h \
 vector3d.h ini_configuration.h Line2D.h
	$(CC) $(CXXFLAGS) -c $< -o $@
