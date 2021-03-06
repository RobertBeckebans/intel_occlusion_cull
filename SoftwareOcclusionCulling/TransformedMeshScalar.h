//--------------------------------------------------------------------------------------
// Copyright 2011 Intel Corporation
// All Rights Reserved
//
// Permission is granted to use, copy, distribute and prepare derivative works of this
// software for any purpose and without fee, provided, that the above copyright notice
// and this statement appear in all copies.  Intel makes no representations about the
// suitability of this software for any purpose.  THIS SOFTWARE IS PROVIDED "AS IS."
// INTEL SPECIFICALLY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, AND ALL LIABILITY,
// INCLUDING CONSEQUENTIAL AND OTHER INDIRECT DAMAGES, FOR THE USE OF THIS SOFTWARE,
// INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PROPRIETARY RIGHTS, AND INCLUDING THE
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  Intel does not
// assume any responsibility for any errors which may appear in this software nor any
// responsibility to update it.
//
//--------------------------------------------------------------------------------------

#ifndef TRANSFORMEDMESHSCALAR_H
#define TRANSFORMEDMESHSCALAR_H

#include "CPUT_DX11.h"
#include "Constants.h"
#include "HelperScalar.h"

class TransformedMeshScalar : public HelperScalar
{
	public:
		TransformedMeshScalar();
		~TransformedMeshScalar();
		void Initialize(CPUTMeshDX11 *pMesh);
		void TransformVertices(const float4x4& cumulativeMatrix, 
							   UINT start, 
							   UINT end);

		void BinTransformedTrianglesST(UINT taskId,
									   UINT modelId,
									   UINT meshId,
									   UINT start,
									   UINT end,
									   UINT* pBin,
									   USHORT* pBinModel,
									   USHORT* pBinMesh,
									   USHORT* pNumTrisInBin);

		void BinTransformedTrianglesMT(UINT taskId,
									   UINT modelId,
									   UINT meshId,
									   UINT start,
									   UINT end,
									   UINT* pBin,
									   USHORT* pBinModel,
									   USHORT* pBinMesh,
									   USHORT* pNumTrisInBin);

		void GetOneTriangleData(float* xformedPos, UINT triId, UINT lane);

		inline UINT GetNumTriangles() {return mNumTriangles;}
		inline UINT GetNumVertices() {return mNumVertices;}
		inline void SetXformedPos(float4 *pXformedPos){mpXformedPos = pXformedPos;}
		inline void SetVertexStart(UINT vertexStart){mVertexStart = vertexStart;}

	private:
		UINT mNumVertices;
		UINT mNumIndices;
		UINT mNumTriangles;
		Vertex *mpVertices;
		UINT *mpIndices;
		float4 *mpXformedPos; 
		UINT mVertexStart;

		void Gather(float4 pOut[3], UINT triId);
};


#endif