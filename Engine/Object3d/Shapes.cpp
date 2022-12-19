#include "Shapes.h"

Object3d* Shapes::CreateTriangle(XMFLOAT3 vertices_1, XMFLOAT3 vertices_2, XMFLOAT3 vertices_3)
{
    Object3d* newTriangle = new Object3d;
    if (newTriangle == nullptr) {
        return nullptr;
    }

    Model* triangleModel = new Model;
    triangleModel->InitializeDescriptorHeap();

    Model::VertexPosNormalUv verticesTriangle[] = {
        vertices_1, {0, 0, 1}, {vertices_1.x, vertices_1.y},
        vertices_2, {0, 0, 1}, {vertices_2.x, vertices_2.y},
        vertices_3, {0, 0, 1}, {vertices_3.x, vertices_3.y},
    };

	return nullptr;
}

Object3d* Shapes::CreateSquare(XMFLOAT2 upperLeft, XMFLOAT2 lowerBottom)
{
    Object3d* newSquare = new Object3d;
    if (newSquare == nullptr) {
        return nullptr;
    }

    Model* squareModel  = new Model;
    squareModel->InitializeDescriptorHeap();
    Model::VertexPosNormalUv verticesSquare[] = {
        {{upperLeft.x, lowerBottom.y, 0.0f}, {0, 0, 1}, {0, 1}},  //ç∂â∫
        {{upperLeft.x, upperLeft.y, 0.0f}, {0, 0, 1}, {0, 0}},    //ç∂è„
        {{lowerBottom.x, lowerBottom.y, 0.0f}, {0, 0, 1}, {1, 1}},//âEâ∫
        {{lowerBottom.x, upperLeft.y, 0.0f}, {0, 0, 1}, {1, 0}},  //âEè„
    };

    return nullptr;
}
