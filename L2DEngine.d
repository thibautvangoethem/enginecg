L2DEngine.o: L2DEngine.cc L2DEngine.h easy_image.h ini_configuration.h \
 Line2D.h Point2D.h Color.h l_parser.h imgUtils.h
	$(CC) $(CXXFLAGS) -c $< -o $@
