figure3D.o: figure3D.cc figure3D.h Color.h face3D.h Point2D.h vector3d.h
	$(CC) $(CXXFLAGS) -c $< -o $@
