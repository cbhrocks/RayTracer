#ifndef __RAYTRACER
#define __RAYTRACER

#define RES 500

#include "libs/vector/GenVector.h"
#include "libs/png/simplePNG.h"
#include "libs/objLoad/objLoader.h"
#include "Scene.h"
#include "libs/ray/Ray.h"
#include "libs/ray/RayGenerator.h"
#include "Buffer.h"

#include <math.h> //Math funcitons and some constants
#include <stdio.h>
#include <ctime>

Vector3 objToGenVec(obj_vector const * objVec);

void printVector(obj_vector *v);

void loadCameraInfo(objLoader* objData, Scene* scene);

void loadPrimitiveInfo(objLoader* objData, Scene* scene);

void loadSphereInfo(objLoader* objData, Scene* scene);

void loadTriangleInfo(objLoader* objData, Scene* scene);

void loadPointLightInfo(objLoader* objData, Scene* scene);

void loadMaterialInfo(objLoader* objData, Scene* scene);

#endif
