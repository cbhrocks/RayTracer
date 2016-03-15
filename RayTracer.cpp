#define RES 500

#include "libs/vector/GenVector.h"
#include "libs/png/simplePNG.h"
#include "libs/objLoad/objLoader.h"
#include "libs/ray/Ray.h"
#include "libs/ray/RayGenerator.h"
#include "Buffer.h"
#include "libs/primitive/Camera.h"
#include "libs/primitive/Sphere.h"
#include "libs/primitive/Triangle.h"
#include "Scene.h"

#include <math.h> //Math funcitons and some constants
#include <stdio.h>

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

  Scene scene = Scene(objData.sphereCount, objData.faceCount, 1);

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

  scene.addCamera(
      objToGenVec(objData.vertexList[ objData.camera->camera_pos_index ]),
      objToGenVec(objData.vertexList[ objData.camera->camera_look_point_index ]),
      objToGenVec(objData.normalList[ objData.camera->camera_up_norm_index ]));

  printf("Number of spheres: %i\n", objData.sphereCount);
  for(int i=0; i<objData.sphereCount; i++)
  {
    obj_sphere *o = objData.sphereList[i];
    printf(" sphere: %d\n", i);
    
    printf(" position: ");
    printf("%f %f %f\n", 
        objData.vertexList[ o->pos_index ]->e[0], 
        objData.vertexList[ o->pos_index ]->e[1], 
        objData.vertexList[ o->pos_index ]->e[2]);
    printf(" position: ");
    printf("%f %f %f\n", 
        objData.normalList[ o->up_normal_index ]->e[0], 
        objData.normalList[ o->up_normal_index ]->e[1], 
        objData.normalList[ o->up_normal_index ]->e[2]);
    printf(" position: ");
    printf("%f %f %f\n", 
        objData.normalList[ o->equator_normal_index ]->e[0], 
        objData.normalList[ o->equator_normal_index ]->e[1], 
        objData.normalList[ o->equator_normal_index ]->e[2]);
    printf("\n");

    scene.addSphere(
        objToGenVec(objData.vertexList[o->pos_index]), 
        objToGenVec(objData.normalList[o->up_normal_index]), 
        objToGenVec(objData.normalList[o->equator_normal_index]));
  }

  //print face info found and create triangles
  printf("Number of faces: %i\n", objData.sphereCount);
  for(int i=0; i<objData.faceCount; i++)
  {
    obj_face *o = objData.faceList[i];
    printf(" face ");
    for(int j=0; j<3; j++)
    {
      printf("%f %f %f | ", 
          objData.vertexList[ o->vertex_index[j] ]->e[0],
          objData.vertexList[ o->vertex_index[j] ]->e[1],
          objData.vertexList[ o->vertex_index[j] ]->e[2]);
    }
    printf("\n");

    scene.addTriangle(
        objToGenVec(objData.vertexList[o->vertex_index[0]]),
        objToGenVec(objData.vertexList[o->vertex_index[1]]),
        objToGenVec(objData.vertexList[o->vertex_index[2]]));
  }

  RayGenerator generator = RayGenerator(scene.getCamera(), RES, RES, M_PI*1/2);

  //Convert vectors to RGB colors for testing results
  for(int y=0; y<RES; y++)
  {
    for(int x=0; x<RES; x++)
    {
      Ray r = generator.getRay(x, y);
      HitPoint HP = scene.traceRay(r);
      Color c;
      if (HP.getT() >= 0){
        Vector3 d = HP.getNormal()*255.0f;
        Color c = Color( abs(d[0]), abs(d[1]), abs(d[2]) );
        buffer.at(x,RES-y-1) = c;
      } else {
        Vector3 d = r.getDirection()*255.0f;
        Color c = Color( 0.0f, 0.0f, 0.0f );
        buffer.at(x,RES-y-1) = c;
      }
    }
  }

  //Write output buffer to file argv2
  simplePNG_write(argv[2], buffer.getWidth(), buffer.getHeight(), (unsigned char*)&buffer.at(0,0));

  return 0;
}

