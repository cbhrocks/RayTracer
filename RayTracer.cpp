#define RES 100

#include "libs/vector/GenVector.h"
#include "libs/png/simplePNG.h"
#include "libs/objLoad/objLoader.h"
#include "libs/ray/Ray.h"
#include "libs/ray/RayGenerator.h"
#include "Buffer.h"
#include "libs/camera/Camera.h"

#include <math.h> //Math funcitons and some constants

//This might be helpful to convert from obj vectors to GenVectors
Vector3 objToGenVec(obj_vector const * objVec)
{
  Vector3 v;
  v[0] = objVec->e[0];
  v[1] = objVec->e[1];
  v[2] = objVec->e[2];
  return v;
}

int main(int argc, char ** argv)
{

  //frame buffer for RESxRES
  Buffer buffer = Buffer(RES, RES);

  //Need at least two arguments (obj input and png output)
  if(argc < 3)
  {
    printf("Usage %s input.obj output.png\n", argv[0]);
    exit(0);
  }

  //load obj from file argv1
  objLoader objData = objLoader();
  objData.load(argv[1]);

  if(objData.camera != NULL)
  {
    printf("Found a camera\n");
    printf(" position: ");
    printf("%f %f %f\n",
        objData.vertexList[ objData.camera->camera_pos_index ]->e[0],
        objData.vertexList[ objData.camera->camera_pos_index ]->e[1],
        objData.vertexList[ objData.camera->camera_pos_index ]->e[2]
        );
    printf(" looking at: ");
    printf("%f %f %f\n",
        objData.vertexList[ objData.camera->camera_look_point_index ]->e[0],
        objData.vertexList[ objData.camera->camera_look_point_index ]->e[1],
        objData.vertexList[ objData.camera->camera_look_point_index ]->e[2]
        );
    printf(" up normal: ");
    printf("%f %f %f\n",
        objData.normalList[ objData.camera->camera_up_norm_index ]->e[0],
        objData.normalList[ objData.camera->camera_up_norm_index ]->e[1],
        objData.normalList[ objData.camera->camera_up_norm_index ]->e[2]
        );
  }

  //create a camera object
  Camera cam = Camera(
      objToGenVec(objData.vertexList[ objData.camera->camera_pos_index ]),
      objToGenVec(objData.vertexList[ objData.camera->camera_look_point_index ]),
      objToGenVec(objData.normalList[ objData.camera->camera_up_norm_index ]));

  RayGenerator generator = RayGenerator(cam, RES, RES, M_PI*1/2);

  //Convert vectors to RGB colors for testing results
  for(int y=0; y<RES; y++)
  {
    for(int x=0; x<RES; x++)
    {
      Ray r = generator.getRay(x, y);
      Vector3 d = r.getDirection()*255.0f;
      Color c = Color( abs(d[0]), abs(d[1]), abs(d[2]) );
      buffer.at(x,RES-y-1) = c;
    }
  }

  //Write output buffer to file argv2
  simplePNG_write(argv[2], buffer.getWidth(), buffer.getHeight(), (unsigned char*)&buffer.at(0,0));

  return 0;
}
