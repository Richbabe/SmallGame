//--------------------------------------------------------------------------------------
// File: ShadowSampleMisc.cpp
//
// This sample demonstrates cascaded shadow maps.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "DXUT.h"
#include "ShadowSampleMisc.h"
#include "SDKmisc.h"
#include "D3D10misc.h"


//--------------------------------------------------------------------------------------
// This function wraps the D3DX
//--------------------------------------------------------------------------------------


// This function wraps the D3DX compile function and prints the error message when it fails.
// It also caches shaders. 
HRESULT CompileShaderFromFile( WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, 
                              ID3DBlob** ppBlobOut, D3D_SHADER_MACRO *defines)
{
    HRESULT hr = S_OK;

    // Find the file.
    WCHAR wcFullShaderPath[MAX_PATH];
    V_RETURN( DXUTFindDXSDKMediaFileCch( wcFullShaderPath, MAX_PATH, szFileName ) );
    ID3DBlob* pErrorBlob;
        // Shader cache is unavailable, or shader has changed so compile.
    D3DX11CompileFromFile( wcFullShaderPath, defines, NULL, szEntryPoint, szShaderModel,  
        D3D10_SHADER_ENABLE_STRICTNESS | D3D10_SHADER_OPTIMIZATION_LEVEL0,
        0, NULL, ppBlobOut, &pErrorBlob, &hr );
    
    if( FAILED( hr ) )
    {
        OutputDebugStringA( (char*)pErrorBlob->GetBufferPointer() );
        SAFE_RELEASE( pErrorBlob );
        return hr;
    } 
    else 
    {
        SAFE_RELEASE( pErrorBlob );
        return hr;
    }
}

