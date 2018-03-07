face3D.o: face3D.cc face3D.h Point2D.h
	$(CC) $(CXXFLAGS) -c $< -o $@
