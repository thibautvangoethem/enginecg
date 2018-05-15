simpleGenerations.o: simpleGenerations.cc easy_image.h \
 ini_configuration.h l_parser.h Line2D.h Point2D.h Color.h \
 simpleGenerations.h
	$(CC) $(CXXFLAGS) -c $< -o $@
