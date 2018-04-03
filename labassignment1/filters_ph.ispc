/*
Anisha Aggarwal
LabAssignment1 
Sources:
    Based off of CIS330 project.
*/

struct image_ISPC {
	uniform int	height;
	uniform int	width;
	uniform unsigned int8 *buffer;
};

export void	parallel_execute(uniform struct image_ISPC& image_in, 
							 uniform struct image_ISPC& image_out) {

	uniform int	height_RGB = image_in.height*3;

	for (int i=0; i<image_in.width; i++) {
		foreach (j=0 ... height_RGB) {
			image_out.buffer[i*height_RGB + j] = 255-image_in.buffer[i*height_RGB+j];
		}
	}
}
 



