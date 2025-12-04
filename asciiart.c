#define STB_IMAGE_IMPLEMENTATION
#include <stdio.h>
#include "stb_image.h"

const char *ramp = "@%#*+=:.";
const int ramp_len = 8;


int main(int argc, char **argv){
	int width, height, channels;

	unsigned char *img = stbi_load("image.png", &width, &height, &channels, 0);
	if(!img){
		printf("Failed to load image\n");
		return 1;
	}	

	printf("Loaded image: %d x %d, %d channels\n", width, height, channels);

	// the amount of chars printed in a row (w), column (h) 
	const int out_h = 32;
	const int out_w = out_h*2*width/height;

	// the amount of pixels considered for an ascii output
	float block_w = width/out_w;
	float block_h = height/out_h;

	for(int by = 0; by < out_h; by++){
		for(int bx = 0; bx < out_w; bx++){
			float sum = 0;
			int count = 0;
			int transparent_count = 0;

			int x_start = bx*block_w;
			int x_end = (1+bx)*block_w;
			int y_start = by*block_h;
			int y_end = (1+by)*block_h;

			if(x_end >= width) x_end = width - 1;
			if(y_end >= height) y_end = height - 1;

			for(int y = y_start; y < y_end; y++){
				for(int x = x_start; x < x_end; x++){
					int idx = (y*width  + x) * channels;

					unsigned char r = img[idx];
					unsigned char g = img[idx+1];
					unsigned char b = img[idx+2];
					unsigned char a = img[idx+3];
					
					if(a < 128){
						transparent_count++;
					}
					float gray = 0.299f*r+0.587f*g+0.114f*b;

					sum += gray;
					count++;
				}
			}
			if(transparent_count > count*0.8){
				printf(" ");
				continue;
			}
			if(count == 0){
				printf(" ");
				continue;
			}

			float avg_gray = sum/count;
			int index = (avg_gray/255.0f)*(ramp_len -1);
			if(index < 0) index = 0;
			if(index >= ramp_len) index = ramp_len -1;

			printf("%c", ramp[index]);
		}
		printf("\n");
	}


	stbi_image_free(img);
	return 0;
}












