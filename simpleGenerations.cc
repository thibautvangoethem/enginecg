/*L2DEngine
 * simpleGenerations.cc
 *
 *  Created on: Mar 1, 2018
 *      Author: thibaut
 */
#include "easy_image.h"
#include "ini_configuration.h"
#include "l_parser.h"
#include "Line2D.h"

#include <list>
#include <cmath>

using namespace img;
#include "simpleGenerations.h"
typedef std::list<Line2D> Lines2D;
inline int roundToInt(double d)
{
	return static_cast<int>(round(d));
}
<<<<<<< HEAD
=======
namespace std {
>>>>>>> 26da4b895d9671d3b3bcd107ab97715703238eca


simpleGenerations::simpleGenerations() {
	// TODO Auto-generated constructor stub

}

simpleGenerations::~simpleGenerations() {
	// TODO Auto-generated destructor stub
}
EasyImage simpleGenerations::generate_QuarterCircle(const ini::Configuration &configuration){
	const unsigned int width = configuration["ImageProperties"]["width"].as_int_or_die();
	const unsigned int height = configuration["ImageProperties"]["height"].as_int_or_die();
	std::vector<double> achtergrond=configuration["LineProperties"]["backgroundcolor"].as_double_tuple_or_die();
	std::vector<double> lijn=configuration["LineProperties"]["lineColor"].as_double_tuple_or_die();
	const unsigned int lines=configuration["LineProperties"]["nrLines"].as_int_or_die();
	img::EasyImage image(width,height);
	int w=roundToInt(width/lines);
	int h=roundToInt(height/lines);
	for(unsigned int i = 0; i < width; i++)
					{
					for(unsigned int j = 0; j < height; j++)
						{
						image(i,j).red = roundToInt(achtergrond[0]*255);
						image(i,j).green = roundToInt(achtergrond[1]*255);
						image(i,j).blue = roundToInt(achtergrond[2]*255);
						}
					}
	for(int i=0;i<lines;i++){
		image.draw_line(0,h*i,w*i,height-1,img::Color( roundToInt(lijn[0]*255),roundToInt(lijn[1]*255),roundToInt(lijn[2]*255)));
	}
	return image;


}
EasyImage simpleGenerations::generate_Eye(const ini::Configuration &configuration){
	const unsigned int width = configuration["ImageProperties"]["width"].as_int_or_die();
	const unsigned int height = configuration["ImageProperties"]["height"].as_int_or_die();
	std::vector<double> achtergrond=configuration["LineProperties"]["backgroundcolor"].as_double_tuple_or_die();
	std::vector<double> lijn=configuration["LineProperties"]["lineColor"].as_double_tuple_or_die();
	const unsigned int lines=configuration["LineProperties"]["nrLines"].as_int_or_die();
	img::EasyImage image(width,height);
	int w=roundToInt(width/lines);
	int h=roundToInt(height/lines);
	for(unsigned int i = 0; i < width; i++)
					{
					for(unsigned int j = 0; j < height; j++)
						{
						image(i,j).red = roundToInt(achtergrond[0]*255);
						image(i,j).green = roundToInt(achtergrond[1]*255);
						image(i,j).blue = roundToInt(achtergrond[2]*255);
						}
					}
	image=simpleGenerations::generate_QuarterCircle(configuration);
	for(int i=0;i<lines;i++)
	{			//image.draw_line(0,h*i,w*i,height-1,img::Color( roundToInt(lijn[0]*255),roundToInt(lijn[1]*255),roundToInt(lijn[2]*255)));
		image.draw_line(width-1,(height-1)-h*i,(width-1)-w*i,0,img::Color( roundToInt(lijn[0]*255),roundToInt(lijn[1]*255),roundToInt(lijn[2]*255)));
	}
		return image;
}
EasyImage simpleGenerations::generate_Diamond(const ini::Configuration &configuration){
	const unsigned int width = configuration["ImageProperties"]["width"].as_int_or_die();
	const unsigned int height = configuration["ImageProperties"]["height"].as_int_or_die();
	std::vector<double> achtergrond=configuration["LineProperties"]["backgroundcolor"].as_double_tuple_or_die();
	std::vector<double> lijn=configuration["LineProperties"]["lineColor"].as_double_tuple_or_die();
	const unsigned int lines=configuration["LineProperties"]["nrLines"].as_int_or_die();
	img::EasyImage image(width,height);
	for(unsigned int i = 0; i < width; i++){
		for(unsigned int j = 0; j < height; j++){
			image(i,j).red = roundToInt(achtergrond[0]*255);
			image(i,j).green = roundToInt(achtergrond[1]*255);
			image(i,j).blue = roundToInt(achtergrond[2]*255);
			}
		}
	for(unsigned int i=0;i<lines;i++){
		unsigned int wi=roundToInt(width/lines/2);
		unsigned int he=roundToInt(height/lines/2);
		image.draw_line(roundToInt(width/2),(height-1)-he*i,roundToInt(width/2)-wi*i,roundToInt(height/2),img::Color( roundToInt(lijn[0]*255),roundToInt(lijn[1]*255),roundToInt(lijn[2]*255)));
		image.draw_line(roundToInt(width/2),(height-1)-he*i,roundToInt(width/2)+wi*i,roundToInt(height/2),img::Color( roundToInt(lijn[0]*255),roundToInt(lijn[1]*255),roundToInt(lijn[2]*255)));
		image.draw_line(roundToInt(width/2),he*i,roundToInt(width/2)-wi*i,roundToInt(height/2),img::Color( roundToInt(lijn[0]*255),roundToInt(lijn[1]*255),roundToInt(lijn[2]*255)));
		image.draw_line(roundToInt(width/2),he*i,roundToInt(width/2)+wi*i,roundToInt(height/2),img::Color( roundToInt(lijn[0]*255),roundToInt(lijn[1]*255),roundToInt(lijn[2]*255)));
	}
	return image;

}
EasyImage simpleGenerations::generate_ColorDambord(const ini::Configuration &configuration){
	const unsigned int width = configuration["ImageProperties"]["width"].as_int_or_die();
	const unsigned int height = configuration["ImageProperties"]["height"].as_int_or_die();
	const unsigned int XPixels = configuration["BlockProperties"]["nrXBlocks"].as_int_or_die();
	const unsigned int YPixels = configuration["BlockProperties"]["nrYBlocks"].as_int_or_die();
	std::vector<double> wit = configuration["BlockProperties"]["colorWhite"].as_double_tuple_or_die();
	std::vector<double> zwart = configuration["BlockProperties"]["colorBlack"].as_double_tuple_or_die();
	bool invert = configuration["BlockProperties"]["invertColors"].as_bool_or_default(false);
	img::EasyImage image(width,height);
			for(unsigned int i = 0; i < width; i++)
				{
				for(unsigned int j = 0; j < height; j++)
					{
					int px=i/(width/XPixels);
					int py=j/(height/YPixels);
					if((px+py)%2==0){
						if(!invert){
							image(i,j).red = roundToInt(wit[0]*255);
							image(i,j).green = roundToInt(wit[1]*255);
							image(i,j).blue = roundToInt(wit[2]*255);
						}else{
							image(i,j).red = roundToInt(zwart[0]*255);
							image(i,j).green = roundToInt(zwart[1]*255);
							image(i,j).blue = roundToInt(zwart[2]*255);
						}
					}else{
						if(!invert){
							image(i,j).red = roundToInt(zwart[0]*255);
							image(i,j).green = roundToInt(zwart[1]*255);
							image(i,j).blue = roundToInt(zwart[2]*255);
						}else{
							image(i,j).red = roundToInt(wit[0]*255);
							image(i,j).green = roundToInt(wit[1]*255);
							image(i,j).blue = roundToInt(wit[2]*255);
						}
					}

					}
				}
	return image;
}
EasyImage simpleGenerations::generate_ColorRectangle(const ini::Configuration &configuration){
	const unsigned int width = configuration["ImageProperties"]["width"].as_int_or_die();
	const unsigned int height = configuration["ImageProperties"]["height"].as_int_or_die();
	img::EasyImage image(width,height);
		for(unsigned int i = 0; i < width; i++)
			{
			for(unsigned int j = 0; j < height; j++)
				{
				image(i,j).red = i;
				image(i,j).green = j;
				image(i,j).blue = (i+j)%256;
				}
			}
		return image;
}
<<<<<<< HEAD

=======
} /* namespace std */
>>>>>>> 26da4b895d9671d3b3bcd107ab97715703238eca
