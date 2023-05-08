#include "FbxLoader.h"

const std::string FbxLoader::baseDirectory = "Engine/Resources/";
const std::string FbxLoader::defaultTextureFileName = "Images/white1x1.png";
const std::string FbxLoader::modelFolder = "3DModels/fbx/";
using namespace DirectX;

FbxLoader* FbxLoader::GetInstance()
{
	static FbxLoader instance;
	return &instance;
}

void FbxLoader::Initialize(ID3D12Device* device) {
	//nullチェック
	assert(fbxManager_ == nullptr);
	//引数からメンバ変数に代入
	device_ = device;
	//FBXマネージャの生成
	fbxManager_ = FbxManager::Create();
	//FBXマネージャの入出力設定
	FbxIOSettings* ios = FbxIOSettings::Create(fbxManager_, IOSROOT);
	fbxManager_->SetIOSettings(ios);
	//FBXインポータの生成
	fbxImporter_ = FbxImporter::Create(fbxManager_, "");
}

void FbxLoader::Finalize() {
	//各種FBXインスタンスの破棄
	fbxImporter_->Destroy();
	fbxManager_->Destroy();
}

FBXModel* FbxLoader::LoadModelFromFile(const string& modelName) {
	//モデルと同じ名前のフォルダから読み込む
	const string directoryPath = baseDirectory + modelFolder + modelName + "/";
	//拡張子
	const string fileName = modelName + ".fbx";
	//連結する
	const string fullPath = directoryPath + fileName;

	//ファイル名を指定してFBXファイルを読み込む
	if (!fbxImporter_->Initialize(fullPath.c_str(), -1, fbxManager_->GetIOSettings())) {
		assert(0);
	}

	//シーン生成
	FbxScene* fbxScene_ = FbxScene::Create(fbxManager_, "fbxScene_");

	//ファイルからロードしたFBXの情報をシーンにインポート
	fbxImporter_->Import(fbxScene_);

	//ポリゴンを三角面化
	FbxGeometryConverter geometryConverter(fbxManager_);
	geometryConverter.Triangulate(fbxScene_, true);
	geometryConverter.RemoveBadPolygonsFromMeshes(fbxScene_);

	//モデル生成
	FBXModel* model = new FBXModel();
	model->name_ = modelName;

	//FBXノードの数を取得
	int32_t nodeCount = fbxScene_->GetNodeCount();

	//あらかじめ必要数分のメモリを確保
	model->nodes_.reserve(nodeCount);

	//ルートノードから順に解析してモデルに流し込む
	ParseNodeRecursive(model, fbxScene_->GetRootNode());

	//FBXシーン解放
	model->fbxScene_ = fbxScene_;

	//バッファ生成
	model->CreateBuffers(device_);

	return model;
}

void FbxLoader::ParseNodeRecursive(FBXModel* model, FbxNode* fbxNode, Node* parent_) {
	//ノード名を取得
	string name_ = fbxNode->GetName();

	//モデルにノードを追加
	model->nodes_.emplace_back();
	Node& node = model->nodes_.back();

	//FBXノードの情報を解析してノードに記録
	node.name_ = fbxNode->GetName();

	//FBXノードのローカル移動情報
	FbxDouble3 rotation_ = fbxNode->LclRotation.Get();
	FbxDouble3 scaling_ = fbxNode->LclScaling.Get();
	FbxDouble3 translation_ = fbxNode->LclTranslation.Get();

	//形式変換して代入
	node.rotation_ = { (float)rotation_[0], (float)rotation_[1], (float)rotation_[2], 0.0f };
	node.scaling_ = { (float)scaling_[0], (float)scaling_[1], (float)scaling_[2], 0.0f };
	node.translation_ = { (float)translation_[0], (float)translation_[1], (float)translation_[2], 1.0f };

	//回転角をDegree(度)からラジアンに変換
	node.rotation_.m128_f32[0] = XMConvertToRadians(node.rotation_.m128_f32[0]);
	node.rotation_.m128_f32[1] = XMConvertToRadians(node.rotation_.m128_f32[1]);
	node.rotation_.m128_f32[2] = XMConvertToRadians(node.rotation_.m128_f32[2]);

	//スケール、回転、平行移動行列の計算
	XMMATRIX matScaling, matRotation, matTranslation;
	matScaling = XMMatrixScalingFromVector(node.scaling_);
	matRotation = XMMatrixRotationRollPitchYawFromVector(node.rotation_);
	matTranslation = XMMatrixTranslationFromVector(node.translation_);

	//ローカル変形行列の計算
	node.transform_ = XMMatrixIdentity();
	node.transform_ *= matScaling;
	node.transform_ *= matRotation;
	node.transform_ *= matTranslation;

	//グローバル変形行列の計算
	node.globalTransform_ = node.transform_;
	if (parent_) {
		node.parent_ = parent_;
		//親の変形を乗算
		node.globalTransform_ *= parent_->globalTransform_;
	}

	//FBXノードのメッシュ情報を解析
	FbxNodeAttribute* fbxNodeAttribute = fbxNode->GetNodeAttribute();

	if (fbxNodeAttribute) {
		if (fbxNodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh) {
			model->meshNode_ = &node;
			ParseMesh(model, fbxNode);
		}
	}

	//子ノードに対して再帰呼び出し
	for (int32_t i = 0; i < fbxNode->GetChildCount(); i++) {
		ParseNodeRecursive(model, fbxNode->GetChild(i), &node);
	}
}

void FbxLoader::ParseMesh(FBXModel* model, FbxNode* fbxNode) {
	//ノードのメッシュを取得
	FbxMesh* fbxMesh = fbxNode->GetMesh();

	//面を構成するデータの読み取り
	ParseMeshFaces(model, fbxMesh);
	//マテリアルの読み取り
	ParseMaterial(model, fbxNode);
	//スキニング情報の読み取り
	ParseSkin(model, fbxMesh);
}

void FbxLoader::ParseMeshFaces(FBXModel* model, FbxMesh* fbxMesh)
{
	auto& vertices_ = model->vertices_;
	auto& indices_ = model->indices_;

	//1ファイルに複数メッシュのモデルは非対応
	assert(indices_.size() == 0);

	//面の数
	const int32_t polygonCount = fbxMesh->GetPolygonCount();

	//UVデータの数
	const int32_t textureUVCount = fbxMesh->GetTextureUVCount();

	//UV名リスト
	FbxStringList uvNames;
	fbxMesh->GetUVSetNames(uvNames);

	//頂点データ配列を確保
	FBXModel::VertexPosNormalUvSkin vert{};
	model->vertices_.resize(polygonCount * 3, vert);

	//FBXメッシュの頂点座標配列を取得
	FbxVector4* pCoord = fbxMesh->GetControlPoints();
	int32_t indexCount = 0;
	controlPoints_.clear();
	controlPoints_.resize(fbxMesh->GetControlPointsCount());

	//面ごとの情報読み取り
	for (int32_t i = 0; i < polygonCount; i++) {
		//面を構成する頂点の数を取得 (3なら三角ポリゴン)
		const int32_t polygonSize = fbxMesh->GetPolygonSize(i);
		assert(polygonSize <= 3);

		//1頂点ずつ処理
		for (int32_t j = 0; j < polygonSize; j++) {
			int32_t index = fbxMesh->GetPolygonVertex(i, j);
			assert(index >= 0);

			controlPoints_[index].push_back(indexCount);

			//頂点法線読み込み
			FBXModel::VertexPosNormalUvSkin& vertex = vertices_[indexCount];
			FbxVector4 normal_;
			if (fbxMesh->GetPolygonVertexNormal(i, j, normal_)) {
				vertex.normal_.x = (float)normal_[0];
				vertex.normal_.y = (float)normal_[1];
				vertex.normal_.z = (float)normal_[2];
			}
			//頂点座標読み込み
			vertex.pos_.x = (float)pCoord[index][0];
			vertex.pos_.y = (float)pCoord[index][1];
			vertex.pos_.z = (float)pCoord[index][2];

			//テクスチャUV読み込み
			if (textureUVCount > 0) {
				FbxVector2 uvs;
				bool lUnmappedUV;
				//0番決め打ちで読み込み
				if (fbxMesh->GetPolygonVertexUV(i, j, uvNames[0], uvs, lUnmappedUV)) {
					vertex.uv_.x = (float)uvs[0];
					vertex.uv_.y = (float)uvs[1] * -1.0f;
				}
			}

			//インデックス配列に頂点インデックス追加
			//3頂点目までなら
			if (j < 3) {
				//1点追加し、他の2点と三角形を構築する
				indices_.push_back(indexCount);
			}
			//4頂点目
			else {
				//3点追加し、
				//四角形の0,1,2,3の内 2,3,0で三角形を構築する
				int32_t index2 = indices_[indices_.size() - 1];
				int32_t index3 = index;
				int32_t index0 = indices_[indices_.size() - 3];
				indices_.push_back(index2);
				indices_.push_back(index3);
				indices_.push_back(index0);
			}
			indexCount++;
		}
	}
}

void FbxLoader::ParseMaterial(FBXModel* model, FbxNode* fbxNode)
{
	const int32_t materialCount = fbxNode->GetMaterialCount();
	if (materialCount > 0) {
		//先頭のマテリアルを取得
		FbxSurfaceMaterial* material = fbxNode->GetMaterial(0);
		//テクスチャを読み込んだかどうかを表すフラグ
		bool textureLoaded = false;

		if (material) {
			//FBXSurfaceLambertクラスか判定
			if (material->GetClassId().Is(FbxSurfaceLambert::ClassId)) {
				FbxSurfaceLambert* lambert = static_cast<FbxSurfaceLambert*>(material);

				//環境光係数
				FbxPropertyT<FbxDouble3> ambient_ = lambert->Ambient;
				model->ambient_.x = (float)ambient_.Get()[0];
				model->ambient_.y = (float)ambient_.Get()[1];
				model->ambient_.z = (float)ambient_.Get()[2];

				//拡散反射光係数
				FbxPropertyT<FbxDouble3> diffuse_ = lambert->Diffuse;
				model->diffuse_.x = (float)diffuse_.Get()[0];
				model->diffuse_.y = (float)diffuse_.Get()[1];
				model->diffuse_.z = (float)diffuse_.Get()[2];

				//ディフューズテクスチャを取り出す
				const FbxProperty diffuseProperty = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
				if (diffuseProperty.IsValid()) {
					const FbxFileTexture* texture = diffuseProperty.GetSrcObject<FbxFileTexture>();
					if (texture) {
						const char* filepath = texture->GetFileName();
						//ファイルパスからファイル名抽出
						string path_str(filepath);
						string name_ = ExtractFileName(path_str);
						//テクスチャ読み込み
						LoadTexture(model, baseDirectory + modelFolder + model->name_ + "/" + name_);
						textureLoaded = true;
					}
				}
			}
		}
		//テクスチャがない場合は白テクスチャを張る
		if (!textureLoaded) {
			LoadTexture(model, baseDirectory + defaultTextureFileName);
		}
	}
}

void FbxLoader::LoadTexture(FBXModel* model, const std::string& fullPath)
{
	HRESULT result = S_FALSE;
	//WICテクスチャのロード
	TexMetadata& metadata_ = model->metadata_;
	ScratchImage& scratchImg_ = model->scratchImg_;
	//ユニコード文字列に変換
	wchar_t wfilepath[128];
	MultiByteToWideChar(CP_ACP, 0, fullPath.c_str(), -1, wfilepath, _countof(wfilepath));
	result = LoadFromWICFile(wfilepath, WIC_FLAGS_NONE, &metadata_, scratchImg_);
	if (FAILED(result)) {
		assert(0);
	}
}

std::string FbxLoader::ExtractFileName(const std::string& path) {
	size_t pos1;
	//区切り文字 '\\' が出てくる一番最後の部分を検索
	pos1 = path.rfind('\\');
	if (pos1 != string::npos) {
		return path.substr(pos1 + 1, path.size() - pos1 - 1);
	}

	//区切り文字 '/' が出てくる一番最後の部分を検索
	pos1 = path.rfind('/');
	if (pos1 != string::npos) {
		return path.substr(pos1 + 1, path.size() - pos1 - 1);
	}

	return path;
}

void FbxLoader::ConvertMatrixFromFbx(DirectX::XMMATRIX* dst, const FbxAMatrix& src)
{
	for (int32_t i = 0; i < 4; i++) {
		for (int32_t j = 0; j < 4; j++) {
			dst->r[i].m128_f32[j] = (float)src.Get(i, j);
		}
	}
}

void FbxLoader::ParseSkin(FBXModel* model, FbxMesh* fbxMesh) {
	//スキニング情報
	FbxSkin* fbxSkin = static_cast<FbxSkin*>(fbxMesh->GetDeformer(0, FbxDeformer::eSkin));

	//スキニング情報がなければ終了
	if (fbxSkin == nullptr) {
		//各頂点についての処理
		for (int32_t i = 0; i < model->vertices_.size(); i++) {
			//最初のボーンの影響を100%にすることでボーンなしに対応
			model->vertices_[i].boneIndex_[0] = 0;
			model->vertices_[i].boneWeight_[0] = 1.0f;
		}

		return;
	}

	//ボーン配列の参照
	std::vector<FBXModel::Bone>& bones = model->bones_;

	//ボーンの数
	int32_t clusterCount = fbxSkin->GetClusterCount();
	bones.reserve(clusterCount);

	//全てのボーンについて
	for (int32_t i = 0; i < clusterCount; i++) {
		//FBXボーン情報
		FbxCluster* fbxCluster = fbxSkin->GetCluster(i);

		//ボーン自体のノードの名前を取得
		const char* boneName = fbxCluster->GetLink()->GetName();

		//新しくボーンを追加し、追加したボーンの参照を得る
		bones.emplace_back(FBXModel::Bone(boneName));
		FBXModel::Bone& bone = bones.back();

		//自作ボーンとFBXボーンを紐づける
		bone.fbxCluster_ = fbxCluster;

		//FBXから初期姿勢行列を取得する
		FbxAMatrix fbxMat;
		fbxCluster->GetTransformLinkMatrix(fbxMat);

		//XMMATRIX型に変換する
		XMMATRIX initialPose;
		ConvertMatrixFromFbx(&initialPose, fbxMat);

		//初期姿勢行列の逆行列を得る
		bone.invInitialPose_ = XMMatrixInverse(nullptr, initialPose);
	}

	struct WeightSet {
		UINT index;
		float weight;
	};

	//二次元配列(ジャグ配列)
	//list:頂点が影響を受けるボーンの全リスト
	//vector:それを全頂点分
	std::vector<std::list<WeightSet>>weightLists(controlPoints_.size());

	//全てのボーンについて
	for (int32_t i = 0; i < clusterCount; i++) {
		FbxCluster* fbxCluster_ = fbxSkin->GetCluster(i);
		//このボーンに影響を受ける頂点の数
		int32_t controlPointIndicesCount = fbxCluster_->GetControlPointIndicesCount();
		//このボーンに影響を受ける頂点の配列
		int32_t* controlPointIndices = fbxCluster_->GetControlPointIndices();
		double* controlPointWeights = fbxCluster_->GetControlPointWeights();

		//影響を受ける全頂点について
		for (int32_t j = 0; j < controlPointIndicesCount; j++) {
			//頂点番号
			int32_t vertIndex = controlPointIndices[j];
			//スキンウェイト
			float weight = (float)controlPointWeights[j];
			//その頂点の影響を受けるボーンリストに、ボーンとウェイトのペアを追加
			weightLists[vertIndex].emplace_back(WeightSet{ (UINT)i, weight });
		}
	}

	//頂点配列書き換え用の参照
	auto& vertices_ = model->vertices_;
	//各頂点について処理
	for (int32_t i = 0; i < controlPoints_.size(); i++) {
		//頂点のウェイトから最も大きい4つを選択
		auto& weightList = weightLists[i];
		//大小比較用のラムダ式を指定して降順にソート
		weightList.sort(
			[](auto const& lhs, auto const& rhs) {
				//左の要素の方が大きければtrue そうでなければfalse
				return lhs.weight > rhs.weight;
			});
		if (weightList.size() > 4) {
			weightList.resize(4);
		}

		for (int32_t j = 0; j < controlPoints_[i].size(); j++) {
			int32_t weightArrayIndex = 0;
			//降順ソート済みのウェイトリストから
			for (auto& weightSet : weightList) {
				std::vector<int32_t>& controlPoint = controlPoints_[i];
				int32_t indexCount = controlPoint[j];
				//頂点データに書き込み
				vertices_[indexCount].boneIndex_[weightArrayIndex] = weightSet.index;
				vertices_[indexCount].boneWeight_[weightArrayIndex] = weightSet.weight;
				//4つに達したら終了
				if (++weightArrayIndex >= FBXModel::MAX_BONE_INDICES) {
					float weight = 0.0f;
					//2番目以降のウェイトを合計
					for (int32_t k = 1; k < FBXModel::MAX_BONE_INDICES; k++) {
						weight += vertices_[indexCount].boneWeight_[k];
					}
					//合計で1.0f(100%)になるように調整
					vertices_[indexCount].boneWeight_[0] = 1.0f - weight;
					break;
				}
			}
		}
	}
}