#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "DirectX.h"

// �e�N�X�`��
class Texture
{
public:
	Texture();
	virtual ~Texture();
	HRESULT Create(const char* fileName);
	HRESULT Create(DXGI_FORMAT format, UINT width, UINT height, const void* pData = nullptr);

	UINT GetWidth() const;
	UINT GetHeight() const;
	ID3D11ShaderResourceView* GetResource() const;

protected:
	D3D11_TEXTURE2D_DESC MakeTexDesc(DXGI_FORMAT format, UINT width, UINT height);
	virtual HRESULT CreateResource(D3D11_TEXTURE2D_DESC &desc, const void* pData);

protected:
	UINT m_width;	// ����
	UINT m_height;	// �c��
	ID3D11ShaderResourceView *m_pSRV;
	ID3D11Texture2D* m_pTex;
};

// �����_�[�^�[�Q�b�g
class RenderTarget : public Texture
{
public:
	RenderTarget();
	~RenderTarget();
	HRESULT Create(DXGI_FORMAT format, UINT width, UINT height);
	HRESULT CreateFromScreen();
	ID3D11RenderTargetView* GetView() const;

protected:
	virtual HRESULT CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData = nullptr);

private:
	ID3D11RenderTargetView* m_pRTV;
};

// �[�x�e�N�X�`��
class DepthStencil : public Texture
{
public:
	DepthStencil();
	~DepthStencil();
	HRESULT Create(UINT width, UINT height, bool useStencil);
	ID3D11DepthStencilView* GetView() const;

protected:
	virtual HRESULT CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData = nullptr);

private:
	ID3D11DepthStencilView* m_pDSV;
};

#endif // __TEXTURE_H__