Line2D.o: Line2D.cc Line2D.h Point2D.h Color.h
	$(CC) $(CXXFLAGS) -c $< -o $@
