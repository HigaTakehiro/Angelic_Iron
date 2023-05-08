#pragma once
#include <string>
#include <DirectXMath.h>
#include <vector>
#include <DirectXTex.h>
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <fbxsdk.h>

struct Node
{
	//名前
	std::string name_;
	//ローカルスケール
	DirectX::XMVECTOR scaling_ = { 1, 1, 1, 0 };
	//ローカル回転角
	DirectX::XMVECTOR rotation_ = { 0, 0, 0, 0 };
	//ローカル移動
	DirectX::XMVECTOR translation_ = { 0, 0, 0, 1 };
	//ローカル変形行列
	DirectX::XMMATRIX transform_;
	//グローバル変形行列
	DirectX::XMMATRIX globalTransform_;
	//親ノード
	Node* parent_ = nullptr;
};

class FBXModel
{
private: //エイリアス
	//Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using TexMetaData = DirectX::TexMetadata;
	using ScratchImage = DirectX::ScratchImage;
	//std::を省略
	using string = std::string;
	template <class T> using vector = std::vector<T>;

public:
	//フレンドクラス
	friend class FbxLoader;

public: //定数
	static const int32_t MAX_BONE_INDICES = 4;

public: //サブクラス
	//頂点データ構造体
	struct VertexPosNormalUvSkin
	{
		XMFLOAT3 pos_;    //xyz座標
		XMFLOAT3 normal_; //法線ベクトル
		XMFLOAT2 uv_;     //uv座標
		UINT boneIndex_[MAX_BONE_INDICES];   //ボーン番号
		float boneWeight_[MAX_BONE_INDICES]; //ボーン重み
	};

	struct Bone
	{
		//名前
		std::string name_;
		//初期姿勢の逆行列
		DirectX::XMMATRIX invInitialPose_;
		//クラスター(FBX側のボーン情報)
		FbxCluster* fbxCluster_;
		//コンストラクタ
		Bone(const std::string& name) {
			this->name_ = name;
		}
	};

public: //メンバ関数

	//デストラクタ
	~FBXModel();

	/// <summary>
	/// バッファ生成
	/// </summary>
	/// <param name="device">デバイス</param>
	void CreateBuffers(ID3D12Device* device);

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="cmdList">コマンドリスト</param>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// モデルの変換行列のゲッター
	/// </summary>
	/// <returns>モデルの変換行列</returns>
	const XMMATRIX& GetModelTransform() { return meshNode_->globalTransform_; }

	//ゲッター
	std::vector<Bone>& GetBones() { return bones_; }
	FbxScene* GetFbxScene() { return fbxScene_; }

private: //メンバ変数
	//モデル名
	string name_;
	//ノード配列
	vector<Node> nodes_;
	//メッシュを持つノード
	Node* meshNode_ = nullptr;
	//頂点データ配列
	vector<VertexPosNormalUvSkin> vertices_;
	//頂点インデックス
	vector<unsigned short> indices_;
	//アンビエント係数
	XMFLOAT3 ambient_ = { 1, 1, 1 };
	//ディフューズ係数
	XMFLOAT3 diffuse_ = { 1, 1, 1 };
	//テクスチャメタデータ
	TexMetaData metadata_ = {};
	//スクラッチイメージ
	ScratchImage scratchImg_ = {};
	//頂点バッファ
	ComPtr<ID3D12Resource> vertBuff_;
	//インデックスバッファ
	ComPtr<ID3D12Resource> indexBuff_;
	//テクスチャバッファ
	ComPtr<ID3D12Resource> texBuff_;
	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView_ = {};
	//インデックスバッファビュー
	D3D12_INDEX_BUFFER_VIEW ibView_ = {};
	//SRV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapSRV_;
	//ボーン配列
	std::vector<Bone> bones_;
	//FBXシーン
	FbxScene* fbxScene_ = nullptr;
};