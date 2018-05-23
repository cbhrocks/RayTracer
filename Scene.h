#ifndef __SCENE
#define __SCENE

#include "Buffer.h"
#include "libs/vector/GenVector.h"
#include "libs/png/simplePNG.h"
#include "libs/objLoad/objLoader.h"
#include "libs/ray/Ray.h"
#include "libs/ray/RayGenerator.h"
#include "libs/shading/Material.h"
#include "libs/shading/Shader.h"
#include "libs/primitive/Camera.h"
#include "libs/primitive/BVHNode.h"
#include "libs/primitive/Primitive.h"
#include "libs/primitive/Sphere.h"
#include "libs/primitive/Triangle.h"
#include "libs/shading/Light.h"
#include "libs/shading/DirectionalLight.h"
#include "libs/shading/PointLight.h"

#include <math.h>

class Scene{
  public:
    Scene(int sphereNum, 
        int triangleNum, 
        int directionalLightNum, 
        int pointLightNum, 
        int shaderNum, 
        int materialNum){
      this->primNum = sphereNum + triangleNum;
      this->lightNum = directionalLightNum + pointLightNum;

      this->primPointerList = new Primitive*[this->primNum];
      this->lightPointerList = new Light*[this->lightNum];

      this->sphereList = new Sphere[sphereNum];
      this->triangleList = new Triangle[triangleNum];
      this->shaderList = new Shader[shaderNum];
      this->materialList = new Material[materialNum];
      this->directionalLightList = new DirectionalLight[directionalLightNum];
      this->pointLightList = new PointLight[pointLightNum];

      this->sphereLoc = 0;
      this->triangleLoc = 0;
      this->lightLoc = 0;
      this->materialLoc = 0;
      this->shaderLoc = 0;
      this->directionalLightLoc = 0;
      this->pointLightLoc = 0;
      this->primLoc = 0;

      this->camera = Camera();
      this->defaultMaterial = Material();
      this->defaultShader = Shader();
      this->defaultLight = DirectionalLight(&this->defaultMaterial);

      if (lightNum == 0){
        this->directionalLightList = new DirectionalLight[1];
        this->lightPointerList = new Light*[1];
        this->directionalLightList[directionalLightNum] = this->defaultLight;
        this->lightPointerList[lightNum++] = &this->directionalLightList[directionalLightNum++];
      }
    }

    Primitive* addSphere(
        Vector3 location, 
        Vector3 up, 
        Vector3 direction, 
        Material *material = 0,
        Shader *shader = 0
        ){
      if (shader == 0){
        shader = &this->defaultShader;
      }
      if (material == 0){
        material = &this->defaultMaterial;
      }
      this->sphereList[this->sphereLoc] = Sphere(location, up, direction, shader, material);
      this->sphereList[this->sphereLoc].getMin().print();
      this->sphereList[this->sphereLoc].getMax().print();
      return this->primPointerList[this->primLoc++] = &this->sphereList[sphereLoc++];
    }

    void addTriangle(
        Vector3 v1, 
        Vector3 v2, 
        Vector3 v3, 
        Material *material = 0,
        Shader *shader = 0
        ){
      if (shader == 0){
        shader = &this->defaultShader;
      }
      if (material == 0){
        material = &this->defaultMaterial;
      }
      this->triangleList[this->triangleLoc] = Triangle(v1, v2, v3, shader, material);
      this->primPointerList[this->primLoc++] = &this->triangleList[triangleLoc++];
    }

    void addCamera(Vector3 location, Vector3 look, Vector3 up){
      this->camera = Camera(location, (look - location), up);
    }

    void addDirectionalLight(
        Vector3 direction,
        Material* material = 0
        ){
      if (material == 0){
        material = &this->defaultMaterial;
      }
      this->directionalLightList[directionalLightLoc] = 
        DirectionalLight(direction, material);
      this->lightPointerList[this->lightLoc++] = 
        &this->directionalLightList[directionalLightLoc++];
    }

    void addPointLight(
        Vector3 location,
        Material* material = 0
        ){
      if (material == 0){
        material = &this->defaultMaterial;
      }
      this->pointLightList[pointLightLoc] = 
        PointLight(location, material);
      this->lightPointerList[this->lightLoc++] = 
        &this->pointLightList[pointLightLoc++];
    }

    Shader* addShader(){
      this->shaderList[shaderLoc] = Shader();
      return &this->shaderList[shaderLoc++];
    }

    Material* addMaterial(
        char* name,
        Vector3 ambientCoefficient,
        Vector3 diffuseCoefficient, 
        Vector3 specularCoefficient, 
        float reflect,
        float translucent,
        int glossy,
        int shine,
        float refract,
        char* texture
        ){
      this->materialList[this->materialLoc] = Material(
          name,
          ambientCoefficient,
          diffuseCoefficient, 
          specularCoefficient, 
          reflect,
          translucent,
          glossy,
          shine,
          refract,
          texture
          );
      return &this->materialList[materialLoc++];
    }

    Material* getMaterial(int index){
      return &this->materialList[index];
    }

    Camera* getCamera(){
      return &this->camera;
    }

    Vector3 traceRay(Ray* ray){
      HitPoint hp = this->tree.getHitPoint(ray);
      if (hp.getT() > 0){
        return hp.getShader()->calculateColor(
            &hp,
            this->lightPointerList, 
            &this->tree,
            this->lightNum,
            this->primNum
            );
        return(hp.getRay()->getDirection() * Vector3(255.0f, 255.0f, 255.0f));
      }
      else{
        return Vector3(0,0,0);
      }
      //return this->tree.getBoxNormal(ray, 2) * 255.0f;
    }

    void createBVHTree(){
      this->tree = BVHNode(this->primPointerList, this->primNum);
    }

  private:
    BVHNode tree;

    Material defaultMaterial;
    Shader defaultShader;
    DirectionalLight defaultLight;

    int sphereLoc;
    int triangleLoc;
    int shaderLoc;
    int primLoc;
    int lightLoc;
    int directionalLightLoc;
    int pointLightLoc;
    int materialLoc;

    int primNum;
    int lightNum;

    Camera camera;
    Triangle *triangleList;
    Sphere *sphereList;
    Shader *shaderList;
    Material *materialList;
    Primitive **primPointerList;
    DirectionalLight *directionalLightList;
    PointLight *pointLightList;
    Light **lightPointerList;
};

#endif
