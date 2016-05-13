//Test streaming process
//The method used is map the distribution function location to a real number.
//For example:
//          f(x,y,z,i) -> real( i.xyz )


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double Float;

const unsigned int nx = 5;
const unsigned int ny = 5;
const unsigned int nz = 5;

const int m = 19;

// Get i-th value from cell x,y,z
unsigned int idxi(
        unsigned int x,
        unsigned int y,
        unsigned int z,
        unsigned int i)
{
    return x + ((y + z*ny)*nx) + (nx*ny*nz*i);
}

void stream(Float* f, Float* f_new)
{
    // For each cell
    unsigned int x, y, z;
    for (z=0; z<nz; z++) {
        for (y=0; y<ny; y++) {
            for (x=0; x<nx; x++) {
                
                // Face 0
                f_new[idxi(x,y,z,0)] = fmax(0.0, f[idxi(x, y, z, 0)]);

                // Face 1 (+x): Bounce back
                if (x < nx-1)
                    f_new[idxi(x+1,  y,  z,  1)]
                        = fmax(0.0, f[idxi(x, y, z, 1)]);
                else
                    f_new[idxi(  x,  y,  z,  2)]
                        = fmax(0.0, f[idxi(x, y, z, 1)]);

                // Face 2 (-x): Bounce back
                if (x > 0)
                    f_new[idxi(x-1,  y,  z,  2)]
                        = fmax(0.0, f[idxi(x, y, z, 2)]);
                else
                    f_new[idxi(  x,  y,  z,  1)]
                        = fmax(0.0, f[idxi(x, y, z, 2)]);

                // Face 3 (+y): Bounce back
                if (y < ny-1)
                    f_new[idxi(  x,y+1,  z,  3)]
                        = fmax(0.0, f[idxi(x, y, z, 3)]);
                else
                    f_new[idxi(  x,  y,  z,  4)]
                        = fmax(0.0, f[idxi(x, y, z, 3)]);

                // Face 4 (-y): Bounce back
                if (y > 0)
                    f_new[idxi(  x,y-1,  z,  4)]
                        = fmax(0.0, f[idxi(x, y, z, 4)]);
                else
                    f_new[idxi(  x,  y,  z,  3)]
                        = fmax(0.0, f[idxi(x, y, z, 4)]);

                // Face 5 (+z): Bounce back
                if (z < nz-1)
                    f_new[idxi(  x,  y,z+1,  5)]
                        = fmax(0.0, f[idxi(x, y, z, 5)]);
                else
                    f_new[idxi(  x,  y,  z,  6)]
                        = fmax(0.0, f[idxi(x, y, z, 5)]);

                // Face 6 (-z): Bounce back
                if (z > 0)
                    f_new[idxi(  x,  y,z-1,  6)]
                        = fmax(0.0, f[idxi(x, y, z, 6)]);
                else
                    f_new[idxi(  x,  y,  z,  5)]
                        = fmax(0.0, f[idxi(x, y, z, 6)]);

                
                // Edge 7 (+x,+y): Bounce back
                if (x < nx-1 && y < ny-1)
                    f_new[idxi(x+1,y+1,  z,  7)]
                        = fmax(0.0, f[idxi(x, y, z, 7)]);
                else if (x < nx-1)
                    f_new[idxi(x+1,  y,  z,  9)]
                        = fmax(0.0, f[idxi(x, y, z, 7)]);
                else if (y < ny-1)
                    f_new[idxi(  x,y+1,  z, 10)]
                        = fmax(0.0, f[idxi(x, y, z, 7)]);
                else
                    f_new[idxi(  x,  y,  z,  8)]
                        = fmax(0.0, f[idxi(x, y, z, 7)]);

                // Edge 8 (-x,-y): Bounce back
                if (x > 0 && y > 0)
                    f_new[idxi(x-1,y-1,  z,  8)]
                        = fmax(0.0, f[idxi(x, y, z, 8)]);
                else if (x > 0)
                    f_new[idxi(x-1,  y,  z,  9)]
                        = fmax(0.0, f[idxi(x, y, z, 8)]);
                else if (y > 0)
                    f_new[idxi(  x,y-1,  z, 10)]
                        = fmax(0.0, f[idxi(x, y, z, 8)]);
                else
                    f_new[idxi(  x,  y,  z,  7)]
                        = fmax(0.0, f[idxi(x, y, z, 8)]);

                // Edge 9 (-x,+y): Bounce back
                if (x > 0 && y < ny-1)
                    f_new[idxi(x-1,y+1,  z,  9)]
                        = fmax(0.0, f[idxi(x, y, z, 9)]);
                else if (x > 0)
                    f_new[idxi(x-1,  y,  z,  8)]
                        = fmax(0.0, f[idxi(x, y, z, 9)]);
                else if (y < ny-1)
                    f_new[idxi(  x,y+1,  z,  7)]
                        = fmax(0.0, f[idxi(x, y, z, 9)]);
                else
                    f_new[idxi(  x,  y,  z, 10)]
                        = fmax(0.0, f[idxi(x, y, z, 9)]);

                // Edge 10 (+x,-y): Bounce back
                if (x < nx-1 && y > 0)
                    f_new[idxi(x+1,y-1,  z, 10)]
                        = fmax(0.0, f[idxi(x, y, z, 10)]);
                else if (x < nx-1)
                    f_new[idxi(x+1,  y,  z,  8)]
                        = fmax(0.0, f[idxi(x, y, z, 10)]);
                else if (y > 0)
                    f_new[idxi(  x,y-1,  z,  7)]
                        = fmax(0.0, f[idxi(x, y, z, 10)]);
                else
                    f_new[idxi(  x,  y,  z,  9)]
                        = fmax(0.0, f[idxi(x, y, z, 10)]);

                // Edge 11 (+x,+z): Bounce back
                if (x < nx-1 && z < nz-1)
                    f_new[idxi(x+1,  y,z+1, 11)]
                        = fmax(0.0, f[idxi(x, y, z, 11)]);
                else if (x < nx-1)
                    f_new[idxi(x+1,  y,  z, 16)]
                        = fmax(0.0, f[idxi(x, y, z, 11)]);
                else if (z < nz-1)
                    f_new[idxi(  x,  y,z+1, 15)]
                        = fmax(0.0, f[idxi(x, y, z, 11)]);
                else
                    f_new[idxi(  x,  y,  z, 12)]
                        = fmax(0.0, f[idxi(x, y, z, 11)]);

                // Edge 12 (-x,-z): Bounce back
                if (x > 0 && z > 0)
                    f_new[idxi(x-1,  y,z-1, 12)]
                        = fmax(0.0, f[idxi(x, y, z, 12)]);
                else if (x > 0)
                    f_new[idxi(x-1,  y,  z, 15)]
                        = fmax(0.0, f[idxi(x, y, z, 12)]);
                else if (z > 0)
                    f_new[idxi(  x,  y,z-1, 16)]
                        = fmax(0.0, f[idxi(x, y, z, 12)]);
                else
                    f_new[idxi(  x,  y,  z, 11)]
                        = fmax(0.0, f[idxi(x, y, z, 12)]);

                // Edge 13 (+y,+z): Bounce back
                if (y < ny-1 && z < nz-1)
                    f_new[idxi(  x,y+1,z+1, 13)]
                        = fmax(0.0, f[idxi(x, y, z, 13)]);
                else if (y < ny-1)
                    f_new[idxi(  x,y+1,  z, 18)]
                        = fmax(0.0, f[idxi(x, y, z, 13)]);
                else if (z < nz-1)
                    f_new[idxi(  x,  y,z+1, 17)]
                        = fmax(0.0, f[idxi(x, y, z, 13)]);
                else
                    f_new[idxi(  x,  y,  z, 14)]
                        = fmax(0.0, f[idxi(x, y, z, 13)]);

                // Edge 14 (-y,-z): Bounce back
                if (y > 0 && z > 0)
                    f_new[idxi(  x,y-1,z-1, 14)]
                        = fmax(0.0, f[idxi(x, y, z, 14)]);
                else if (y > 0)
                    f_new[idxi(  x,y-1,  z, 17)]
                        = fmax(0.0, f[idxi(x, y, z, 14)]);
                else if (z > 0)
                    f_new[idxi(  x,  y,z-1, 18)]
                        = fmax(0.0, f[idxi(x, y, z, 14)]);
                else
                    f_new[idxi(  x,  y,  z, 13)]
                        = fmax(0.0, f[idxi(x, y, z, 14)]);

                // Edge 15 (-x,+z): Bounce back
                if (x > 0 && z < nz-1)
                    f_new[idxi(x-1,  y,z+1, 15)]
                        = fmax(0.0, f[idxi(x, y, z, 15)]);
                else if (x > 0)
                    f_new[idxi(x-1,  y,  z, 12)]
                        = fmax(0.0, f[idxi(x, y, z, 15)]);
                else if (z < nz-1)
                    f_new[idxi(  x,  y,z+1, 11)]
                        = fmax(0.0, f[idxi(x, y, z, 15)]);
                else
                    f_new[idxi(  x,  y,  z, 16)]
                        = fmax(0.0, f[idxi(x, y, z, 15)]);

                // Edge 16 (+x,-z)
                if (x < nx-1 && z > 0)
                    f_new[idxi(x+1,  y,z-1, 16)]
                        = fmax(0.0, f[idxi(x, y, z, 16)]);
                else if (x < nx-1)
                    f_new[idxi(x+1,  y,  z, 11)]
                        = fmax(0.0, f[idxi(x, y, z, 16)]);
                else if (z > 0)
                    f_new[idxi(  x,  y,z-1, 12)]
                        = fmax(0.0, f[idxi(x, y, z, 16)]);
                else
                    f_new[idxi(  x,  y,  z, 15)]
                        = fmax(0.0, f[idxi(x, y, z, 16)]);

                // Edge 17 (-y,+z)
                if (y > 0 && z < nz-1)
                    f_new[idxi(  x,y-1,z+1, 17)]
                        = fmax(0.0, f[idxi(x, y, z, 17)]);
                else if (y > 0)
                    f_new[idxi(  x,y-1,  z, 14)]
                        = fmax(0.0, f[idxi(x, y, z, 17)]);
                else if (z < nz-1)
                    f_new[idxi(  x,  y,z+1, 13)]
                        = fmax(0.0, f[idxi(x, y, z, 17)]);
                else
                    f_new[idxi(  x,  y,  z, 18)]
                        = fmax(0.0, f[idxi(x, y, z, 17)]);

                // Edge 18 (+y,-z)
                if (y < ny-1 && z > 0)
                    f_new[idxi(  x,y+1,z-1, 18)]
                        = fmax(0.0, f[idxi(x, y, z, 18)]);
                else if (y < ny-1)
                    f_new[idxi(  x,y+1,  z, 13)]
                        = fmax(0.0, f[idxi(x, y, z, 18)]);
                else if (z > 0)
                    f_new[idxi(  x,  y,z-1, 14)]
                        = fmax(0.0, f[idxi(x, y, z, 18)]);
                else
                    f_new[idxi(  x,  y,  z, 17)]
                        = fmax(0.0, f[idxi(x, y, z, 18)]);
            }
        }
    }
}

int main(void)
{
	unsigned int x, y, z, i;
	unsigned int ncells = nx*ny*nz;
    Float* f = malloc(ncells*m*sizeof(Float));
    Float* fnew = malloc(ncells*m*sizeof(Float));

	for (i = 0; i < m; i++){
		for (z = 0; z < nz; z++) {
			for (y = 0; y < ny; y++) {
				for (x = 0; x < nx; x++)
                    f[idxi(x,y,z,i)] = i*1.+ x*.1 + y*.01 + z*.001;
			}
		}
	}

    for (y = 0; y < ny; y++) {
        for (x = 0; x < nx; x++){
            printf("  %1.2f  ", f[idxi(x,y,3,7)]);
        }
        printf("\n");
    }

    stream(f, fnew);



	printf("RESULT: Direction 7-----------------------\n");
	printf("XY PLANE: \n");

	for (y = 0; y < ny; y++) {
		for (x = 0; x < nx; x++){
			printf("  %1.2f  ", fnew[idxi(x,y,3,7)]);
		}
		printf("\n");
	}
    
    printf("RESULT: Direction 18------------------------\n");
    printf("YZ PLANE: \n");
    for (y = 0; y < ny; y++) {
        for (x = 0; x < nx; x++){
            printf("  %1.2f  ", fnew[idxi(x,y,3,18)]);
        }
        printf("\n");
    }
	

    free(f);
	free(fnew);
    return 0;
}
