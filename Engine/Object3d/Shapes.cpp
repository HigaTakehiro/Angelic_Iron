#include "Shapes.h"

//std::unique_ptr<Model> Shapes::CreateTriangle(XMFLOAT3 vertices_1, XMFLOAT3 vertices_2, XMFLOAT3 vertices_3)
//{
//    Object3d* newTriangle = new Object3d;
//    if (newTriangle == nullptr) {
//        return nullptr;
//    }
//
//    Model* triangleModel = new Model;
//    triangleModel->InitializeDescriptorHeap();
//
//    Model::VertexPosNormalUv verticesTriangle[] = {
//        vertices_1, {0, 0, 1}, {vertices_1.x, vertices_1.y},
//        vertices_2, {0, 0, 1}, {vertices_2.x, vertices_2.y},
//        vertices_3, {0, 0, 1}, {vertices_3.x, vertices_3.y},
//    };
//
//	return nullptr;
//}

Model* Shapes::CreateSquare(XMFLOAT2 upperLeft, XMFLOAT2 lowerBottom, const std::string& textureName)
{
    Model* squareModel = nullptr;
    Model::VertexPosNormalUv verticesSquare[] = {
        {{upperLeft.x, lowerBottom.y, 0.0f}, {0, 0, 1}, {0, 1}},  //ç∂â∫
        {{upperLeft.x, upperLeft.y, 0.0f}, {0, 0, 1}, {0, 0}},    //ç∂è„
        {{lowerBottom.x, lowerBottom.y, 0.0f}, {0, 0, 1}, {1, 1}},//âEâ∫
        {{lowerBottom.x, upperLeft.y, 0.0f}, {0, 0, 1}, {1, 0}},  //âEè„
    };

    unsigned short indicesSquare[] = {
        0, 1, 2,
        2, 1, 3,
    };

    std::vector<Model::VertexPosNormalUv> vertices;
    for (int i = 0; i < 4; i++) {
        vertices.emplace_back(verticesSquare[i]);
    }

    std::vector<unsigned short> indices;
    for (int i = 0; i < 6; i++) {
        indices.emplace_back(indicesSquare[i]);
    }

    squareModel = Model::CreateShapeModel(vertices, indices, textureName);

    return squareModel;
}
