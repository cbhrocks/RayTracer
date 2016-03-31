#include "RayTracer.h"

int main(int argc, char ** argv)
{

  //frame buffer for RESxRES
  Buffer<Vector3> buffer = Buffer<Vector3>(RES, RES);
  Buffer<Color> bufferC = Buffer<Color>(RES, RES);

  //Need at least two arguments (obj input and png output)
  if(argc < 3)
  {
    printf("Usage %s input.obj output.png\n", argv[0]);
    exit(0);
  }

  //load obj from file argv1
  objLoader objData = objLoader();
  objData.load(argv[1]);

  //create scene object
  Scene scene = Scene(objData.sphereCount, objData.faceCount, 0, objData.lightPointCount, 0, objData.materialCount);

  //create camera from objData
  loadCameraInfo(&objData, &scene);

  //create materials from objData
  loadMaterialInfo(&objData, &scene);

  //create primitives from objData
  loadPrimitiveInfo(&objData, &scene);

  loadPointLightInfo(&objData, &scene);

  printf("Making Tree\n");
  scene.createBVHTree();
  printf("Done Making Tree\n");

  //create ray generator
  RayGenerator generator = RayGenerator(scene.getCamera(), RES, RES, 90.0f);

  //Convert vectors to RGB colors for viewing pleasure
  float highestValue = 0.0f;
  for(int y=0; y<RES; y++)
  {
    for(int x=0; x<RES; x++)
    {
      Ray r = generator.getRay(x, y);
      Vector3 c = scene.traceRay(&r);
      float curBiggest = c[c.maxMagnitudeComponent()];
      if (curBiggest > highestValue){
        highestValue = curBiggest;
      }
      buffer.at(x,RES-y-1) = c;
      //printf("finished ray at (%d, %d)\n", x, y);
    }
  }

  //printf("highest value: %f", highestValue);

  for(int y=0; y<RES; y++)
  {
    for(int x=0; x<RES; x++)
    {
      Vector3 oldV;
      if (highestValue > 1){
        oldV  = buffer.at(x,y)*255.0f/highestValue;
      }
      else{
        oldV  = buffer.at(x,y)*255.0f;
      }
      bufferC.at(x,y) = Color(oldV[0], oldV[1], oldV[2]);
      //bufferC.at(x,y) = Color(abs(oldV[0]), abs(oldV[1]), abs(oldV[2]));
    }
  }

  //Write output buffer to file argv2
  simplePNG_write(argv[2], bufferC.getWidth(), bufferC.getHeight(), (unsigned char*)&bufferC.at(0,0));

  printf("done making picture\n");

  return 0;
}

//This might be helpful to convert from obj vectors to GenVectors
Vector3 objToGenVec(obj_vector const * objVec)
{
  Vector3 v;
  v[0] = objVec->e[0];
  v[1] = objVec->e[1];
  v[2] = objVec->e[2];
  return v;
}

void printVector(obj_vector *v)
{
  printf("%.2f,", v->e[0] );
  printf("%.2f,", v->e[1] );
  printf("%.2f  ", v->e[2] );
}

void loadCameraInfo(objLoader* objData, Scene* scene){

  if(objData->camera != NULL)
  {
    printf("Found a camera\n");
    printf(" position: ");
    printVector(objData->vertexList[ objData->camera->camera_pos_index ]);
    printf("\n looking at: ");
    printVector(objData->vertexList[ objData->camera->camera_look_point_index ]);
    printf("\n up normal: ");
    printVector(objData->normalList[ objData->camera->camera_up_norm_index ]);
    printf("\n\n");

  scene->addCamera(
      objToGenVec(objData->vertexList[ objData->camera->camera_pos_index ]),
      objToGenVec(objData->vertexList[ objData->camera->camera_look_point_index ]),
      objToGenVec(objData->normalList[ objData->camera->camera_up_norm_index ]));
  }
}

//void getPrimitiveInfo(objLoader* objData, Scene* scene, Shader* shader){
void loadPrimitiveInfo(objLoader* objData, Scene* scene){
  loadSphereInfo(objData, scene);
  loadTriangleInfo(objData, scene);
}

//void getSphereInfo(objLoader* objData, Scene* scene, Shader* shader){
void loadSphereInfo(objLoader* objData, Scene* scene){
  printf("Number of spheres: %i\n", objData->sphereCount);
  for(int i=0; i<objData->sphereCount; i++)
  {
    obj_sphere *o = objData->sphereList[i];
    //printf(" sphere: %d\n", i);
    
    //printf(" position: ");
    //printVector(objData->vertexList[ o->pos_index ]);
    //printf("\n up normal: ");
    //printVector(objData->normalList[ o->up_normal_index ]);
    //printf("\n equator normal: ");
    //printVector(objData->normalList[ o->equator_normal_index ]);

    Primitive* sphere;
    if (objData->materialCount > 0){
    sphere = scene->addSphere(
        objToGenVec(objData->vertexList[o->pos_index]), 
        objToGenVec(objData->normalList[o->up_normal_index]), 
        objToGenVec(objData->normalList[o->equator_normal_index]),
        scene->getMaterial( o->material_index )
        );
    }
    else{
    sphere = scene->addSphere(
        objToGenVec(objData->vertexList[o->pos_index]), 
        objToGenVec(objData->normalList[o->up_normal_index]), 
        objToGenVec(objData->normalList[o->equator_normal_index])
        );
    }

    //printf("\n material: ");
    //printf("%s", sphere->getMaterial()->getName());
    //printf("\n");
  }
}

//void getTriangleInfo(objLoader* objData, Scene* scene, Shader* shader){
void loadTriangleInfo(objLoader* objData, Scene* scene){
  printf("Number of faces: %i\n", objData->faceCount);

  for(int i=0; i<objData->faceCount; i++)
  {
    obj_face *o = objData->faceList[i];
    //printf(" face:  ");
    //for(int j=0; j<3; j++)
    //{
      //printVector(objData->vertexList[ o->vertex_index[j] ]);
      ////printf(" - normal: ");
      ////printVector(objData->normalList[ o->normal_index[j] ]);
      //printf("| ");
    //}
    //if (objData->materialCount > 0){
      //printf("material: ");
      //printf("%s", scene->getMaterial( o->material_index)->getName());
    //}
    //printf("\n");

    //printVector( objData->normalList[ o->normal_index[0] ]);
    //printVector( objData->normalList[ o->normal_index[1] ]);
    //printVector( objData->normalList[ o->normal_index[2] ]);
    //printf("\n");

    if (objData->materialCount > 0){
    scene->addTriangle(
        objToGenVec(objData->vertexList[o->vertex_index[0]]),
        objToGenVec(objData->vertexList[o->vertex_index[1]]),
        objToGenVec(objData->vertexList[o->vertex_index[2]]),
        scene->getMaterial( o->material_index )
        );
    }
    else {
    scene->addTriangle(
        objToGenVec(objData->vertexList[o->vertex_index[0]]),
        objToGenVec(objData->vertexList[o->vertex_index[1]]),
        objToGenVec(objData->vertexList[o->vertex_index[2]])
        );
    }
  }

  //printf("\n");
}

void loadPointLightInfo(objLoader* objData, Scene* scene){
  printf("Number of point lights: %i\n", objData->lightPointCount);
  for(int i=0; i<objData->lightPointCount; i++)
  {
    obj_light_point *o = objData->lightPointList[i];
    printf(" plight ");
    printVector(objData->vertexList[ o->pos_index ]);
    printf("\n");

    scene->addPointLight(objToGenVec(objData->vertexList[ o->pos_index ]), scene->getMaterial(o->material_index));
  }

  printf("\n");
}

void loadMaterialInfo(objLoader* objData, Scene* scene){
  printf("Number of materials: %i\n", objData->materialCount);
  for(int i=0; i<objData->materialCount; i++)
  {
    obj_material *mtl = objData->materialList[i];
    printf(" name: %s", mtl->name);
    printf(" amb: %.2f ", mtl->amb[0]);
    printf("%.2f ", mtl->amb[1]);
    printf("%.2f\n", mtl->amb[2]);

    printf(" diff: %.2f ", mtl->diff[0]);
    printf("%.2f ", mtl->diff[1]);
    printf("%.2f\n", mtl->diff[2]);

    printf(" spec: %.2f ", mtl->spec[0]);
    printf("%.2f ", mtl->spec[1]);
    printf("%.2f\n", mtl->spec[2]);

    printf(" reflect: %.2f\n", mtl->reflect);
    printf(" trans: %.2f\n", mtl->trans);
    printf(" glossy: %i\n", (int) mtl->glossy);
    printf(" shiny: %i\n", (int) mtl->shiny);
    printf(" refract: %.2f\n", mtl->refract_index);

    printf(" texture: %s\n", mtl->texture_filename);
    printf("\n");

    scene->addMaterial(
        mtl->name, 
        Vector3(mtl->amb[0], mtl->amb[1], mtl->amb[2]),
        Vector3(mtl->diff[0], mtl->diff[1], mtl->diff[2]),
        Vector3(mtl->spec[0], mtl->spec[1], mtl->spec[2]),
        mtl->reflect,
        mtl->trans,
        (int) mtl->glossy,
        (int) mtl->shiny,
        mtl->refract_index,
        mtl->texture_filename
        );
  }
}
