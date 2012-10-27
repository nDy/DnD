/*
 * ImageHandler.h
 *
 *  Created on: Oct 27, 2012
 *      Author: ndy
 */

#ifndef IMAGEHANDLER_H_
#define IMAGEHANDLER_H_

#include <SFML/Graphics/Image.hpp>

class ImageHandler {
public:
	virtual ~ImageHandler();
	virtual sf::Image LoadImage(char* filename) {
		sf::Image image;

		if (!image.LoadFromFile(filename)) {
			//return NULL;
		}

		return image;
	}
};

#endif /* IMAGEHANDLER_H_ */
