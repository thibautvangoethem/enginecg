#include "easy_image.h"
#include "ini_configuration.h"
#include "Color.h"
#include "Point2D.h"
#include "Line2D.h"
#include "Line2D.h"
#include "l_parser.h"
#include "vector3d.h"
#include "figure3D.h"
#include "simpleGenerations.h"
#include "imgUtils.h"
#include "L2DEngine.h"
#include "Engine3D.h"
#include "Light.h"
#include "Color.h"
#include "To2DConverter.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>
#include <list>
#include <utility>

using namespace std;
typedef std::list<Line2D> Lines2D;
/*
 * this methods reads an .ini file and then calls the correct method to creature the right image
 */
img::EasyImage generate_image(const ini::Configuration &configuration)
{
	const std::string typeString= configuration["General"]["type"].as_string_or_die();
	simpleGenerations simple;
	L2DEngine l2dengine;
	Engine3D engine3D;
			if(typeString== "IntroColorRectangle"){
				return simple.generate_ColorRectangle(configuration);
			}else if(typeString== "IntroBlocks"){
				return simple.generate_ColorDambord(configuration);
			}else if(typeString== "IntroLines"){
				std::string lineprop = configuration["LineProperties"]["figure"].as_string_or_die();
				if(lineprop=="QuarterCircle"){
					return simple.generate_QuarterCircle(configuration);
				}else if(lineprop=="Eye"){
					return simple.generate_Eye(configuration);
				}else if(lineprop=="Diamond"){
					return simple.generate_Diamond(configuration);
				}
			}else if(typeString=="2DLSystem"){
				Lines2D lines= l2dengine.L2D_ToLines(configuration);
				return imgUtils::LinesToImg(configuration,lines);
			}else if(typeString=="Wireframe"){
				std::vector<figure3D> figures= engine3D.draw3D(configuration);
				Lines2D lines=To2DConverter::figuresToLines2D(figures);
				return imgUtils::LinesToImg(configuration,lines);
			}else if(typeString=="ZBufferedWireframe"){
				std::vector<figure3D> figures= engine3D.draw3D(configuration);
				Lines2D lines=To2DConverter::figuresToLines2D(figures,true);
				return imgUtils::LinesToImg(configuration,lines,true);
			}else if(typeString=="ZBuffering"){
				std::vector<figure3D> figures= engine3D.draw3D(configuration);
				for(auto &fig:figures){
					fig.triangulate();
				}
				Light *l=new Light(figColor::Color(1,1,1),figColor::Color(0,0,0),figColor::Color(0,0,0));
				std::vector<Light*> lights;
				lights.push_back(l);
				EasyImage img= imgUtils::TrianglesToImg(configuration,figures,true,lights);
				for(auto i:lights){
					delete i;
				}
				return img;
			}else if(typeString=="LightedZBuffering"){
				std::vector<figure3D> figures= engine3D.draw3D(configuration);
				for(auto &fig:figures){
					fig.triangulate();
				}
				std::vector<Light*> lights=Engine3D::readLights(configuration);
				EasyImage img= imgUtils::TrianglesToImg(configuration,figures,true,lights);
//				for(unsigned int i=0;i<lights.size();i++){
//					delete lights[i];
//				}
				return img;

			}


	return img::EasyImage();
}

int main(int argc, char const* argv[])
{
        int retVal = 0;
        try
        {
                for(int i = 1; i < argc; ++i)
                {
                        ini::Configuration conf;
                        try
                        {
                                std::ifstream fin(argv[i]);
                                std::cout<<argv[i]<<std::endl;
                                fin >> conf;
                                fin.close();
                        }
                        catch(ini::ParseException& ex)
                        {
                                std::cerr << "Error parsing file: " << argv[i] << ": " << ex.what() << std::endl;
                                retVal = 1;
                                continue;
                        }

                        img::EasyImage image = generate_image(conf);
                        if(image.get_height() > 0 && image.get_width() > 0)
                        {
                                std::string fileName(argv[i]);
                                std::string::size_type pos = fileName.rfind('.');
                                if(pos == std::string::npos)
                                {
                                        //filename does not contain a '.' --> append a '.bmp' suffix
                                        fileName += ".bmp";
                                }
                                else
                                {
                                        fileName = fileName.substr(0,pos) + ".bmp";
                                }
                                try
                                {
                                        std::ofstream f_out(fileName.c_str(),std::ios::trunc | std::ios::out | std::ios::binary);
                                        f_out << image;

                                }
                                catch(std::exception& ex)
                                {
                                        std::cerr << "Failed to write image to file: " << ex.what() << std::endl;
                                        retVal = 1;
                                }
                        }
                        else
                        {
                                std::cout << "Could not generate image for " << argv[i] << std::endl;
                        }
                }
        }
        catch(const std::bad_alloc &exception)
        {
    		//When you run out of memory this exception is thrown. When this happens the return value of the program MUST be '100'.
    		//Basically this return value tells our automated test scripts to run your engine on a pc with more memory.
    		//(Unless of course you are already consuming the maximum allowed amount of memory)
    		//If your engine does NOT adhere to this requirement you risk losing points because then our scripts will
        	//mark the test as failed while in reality it just needed a bit more memory
                std::cerr << "Error: insufficient memory" << std::endl;
                retVal = 100;
        }
        return retVal;
}
