#ifndef __SHADER_H__
#define __SHADER_H__

#include "DirectX.h"
#include "Texture.h"
#include <string>
#include <map>
#include <vector>

// シェーダーの基本クラス
class Shader
{
protected:
	enum Kind
	{
		Vertex,
		Pixel
	};
protected:
	Shader(Kind kind);
public:
	virtual ~Shader();
public:
	HRESULT Load(const char* pFileName);		// シェーダーファイル(*.cso)を読み込む処理
	HRESULT Compile(const char* pCode);			// 文字列からシェーダをコンパイル
	void WriteBuffer(UINT slot, void* pData);	// 定数の書き込み
	void SetTexture(UINT slot, Texture* tex);	// テクスチャの設定
	virtual void Bind(void) = 0;				// シェーダーを描画に使用
private:
	HRESULT Make(void* pData, UINT size);
protected:
	// シェーダーファイルを読み込んだ後、シェーダーの種類別に処理を行う
	virtual HRESULT MakeShader(void* pData, UINT size) = 0;

private:
	Kind m_kind;
protected:
	std::vector<ID3D11Buffer*> m_pBuffers;
};

// 頂点シェーダ
class VertexShader : public Shader
{
public:
	VertexShader();
	~VertexShader();
	void Bind(void);
protected:
	HRESULT MakeShader(void* pData, UINT size);

private:
	ID3D11VertexShader* m_pVS;
	ID3D11InputLayout* m_pInputLayout;
};

// ピクセルシェーダ
class PixelShader : public Shader
{
public:
	PixelShader();
	~PixelShader();
	void Bind(void);
protected:
	HRESULT MakeShader(void* pData, UINT size);
private:
	ID3D11PixelShader* m_pPS;
};

#endif