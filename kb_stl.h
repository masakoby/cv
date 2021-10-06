#include <string>
#include <vector>
#include <io.h>
#include <fstream>

#include <mist/mist.h>
#include <mist/vector.h>

#pragma once

namespace kb
{
	int loadAsSTL(
		const std::string& path1, 
		std::vector< float >& pv,
		std::vector< float >& nv,
		std::vector< int >& indices
		);
	int loadAsSTL_ascii(
		const std::string& path1, 
		std::vector< float >& pv,
		std::vector< float >& nv,
		std::vector< int >& indices
		);
	int loadAsSTL_bin(
		const std::string& path1, 
		std::vector< float >& pv,
		std::vector< float >& nv,
		std::vector< int >& indices
		);

	//
	int saveAsSTL(
		const std::string& path1,
		std::vector< float >& vpos,
		std::vector< int >& indexElements
	);


	int saveAsObj(
		const std::string& path1, 
		const std::string& header, 
		std::vector< mist::vector3<double> >& oPos
		);
	int saveAsPly(
		const std::string& path1, 
		std::vector< mist::vector3< double > >& pv,
		std::vector< mist::vector3< double > >& nv,
		std::vector< unsigned char >& colors
		);



	int loadVertexAndDirectionalVectors(
		const std::string& path1, 
		std::vector< mist::vector3< double > >& pv,
		std::vector< mist::vector3< double > >& nv
		);

	int saveIndex(
		std::string& path,
		mist::array3<unsigned char>& voxelThinning,		//	ÉâÉxÉãïtÇ≥ÇÍÇΩç◊ê¸âªâÊëú
		int index
		);





	int fillHoleSelectedSTL(
		std::vector< mist::vector3< double > >& pv_stl2,
		std::vector<int>& index_stl2,
		std::vector<int>& stateElements,
		std::vector<int>& stateElementsOut
		);
	int fillHoleLabelingSTL(
		std::vector< mist::vector3< double > >& pv_stl2,
		std::vector<int>& index_stl2,
		std::vector<int>& stateElements,
		std::vector<int>& stateElementsOut
		);
	int fillHoleLabelingSTL2(
		std::vector< mist::vector3< double > >& pv_stl2,
		std::vector<int>& index_stl2,
		std::vector<int>& stateElements,
		std::vector<int>& stateElementsOut
		);
	int getNodeIndices(
		std::vector< mist::vector3< double > >& nodes,
		std::vector<int>& indexNodeInElement,
		std::vector<int>& stateElementsLabel,
		int index,
		std::vector<int>& indexNodes
		);


};
