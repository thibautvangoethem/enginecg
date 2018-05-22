Light.o: Light.cc Light.h Color.h vector3d.h ZBuffer.h figure3D.h \
 face3D.h Point2D.h Line2D.h To2DConverter.h
	$(CC) $(CXXFLAGS) -c $< -o $@
