#define STB_IMAGE_IMPLEMENTATION
#include <stdio.h>
#include "stb_image.h"

int main(int argc, char **argv){
	int width, height, channels;

	unsigned char *data = stbi_load("image.png", &width, &height, &channels, 0);
	if(!data){
		printf("Failed to load image\n");
		return 1;
	}	

	printf("Loaded image: %d x %d, %d channels\n", width, height, channels);





	stbi_image_free(data);
	return 0;
}












