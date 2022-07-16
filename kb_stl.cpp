#define _USE_MATH_DEFINES
#include <math.h>

#include "kb_stl.h"
#include "kb_mat.h"
#include "kb_normal_vector_on_mesh.h"


int kb::loadAsSTL_ascii(
	const std::string& path1, 
	std::vector< float >& pv,
	std::vector< float >& nv,
	std::vector< int >& indices
	)
{
	std::ifstream ofs(path1);

	{
		char buf[6];
		ofs.read(buf, 5);
		buf[5]=0;
		std::string strIn1=buf;
		std::cout<<buf<<std::endl;
		if( strIn1!="solid"){
			return -1;
		}
	}

	int k=0;
	mist::vector3< double > vecNormal(0,0,0);
	mist::vector3< double > vecVertex[3];
	while(1){
		int state=0;
		{
			std::string strIn1;
			ofs>>strIn1;
			if( strIn1=="facet" ){
				std::string strIn2;
				ofs>>strIn2;
				if( strIn2=="normal" ){
					state=1;
				}else{
					state=-1;
				}
			}else if( strIn1=="outer" ){
				std::string strIn2;
				ofs>>strIn2;
				if( strIn2=="loop" ){
					state=2;
				}else{
					state=-1;
				}
			}else{
				if( ofs.eof()==true )
					break;
				continue;
			}
			if( state<0 )
				return -1;
		}

		//
		if( state==1 ){
			std::string strIn1;
			ofs>>strIn1; vecNormal.x=atof( strIn1.c_str() );
			ofs>>strIn1; vecNormal.y=atof( strIn1.c_str() );
			ofs>>strIn1; vecNormal.z=atof( strIn1.c_str() );
		}else if( state==2 ){
			std::string strIn1;
			//
			ofs>>strIn1; 
			if( strIn1=="vertex" ){
				ofs>>strIn1; vecVertex[0].x=atof( strIn1.c_str() );
				ofs>>strIn1; vecVertex[0].y=atof( strIn1.c_str() );
				ofs>>strIn1; vecVertex[0].z=atof( strIn1.c_str() );
			}else{
				return -1;
			}
			//
			ofs>>strIn1; 
			if( strIn1=="vertex" ){
				ofs>>strIn1; vecVertex[1].x=atof( strIn1.c_str() );
				ofs>>strIn1; vecVertex[1].y=atof( strIn1.c_str() );
				ofs>>strIn1; vecVertex[1].z=atof( strIn1.c_str() );
			}else{
				return -1;
			}
			//
			ofs>>strIn1; 
			if( strIn1=="vertex" ){
				ofs>>strIn1; vecVertex[2].x=atof( strIn1.c_str() );
				ofs>>strIn1; vecVertex[2].y=atof( strIn1.c_str() );
				ofs>>strIn1; vecVertex[2].z=atof( strIn1.c_str() );
			}else{
				return -1;
			}

			pv.push_back(vecVertex[0].x);
			pv.push_back(vecVertex[0].y);
			pv.push_back(vecVertex[0].z);
			pv.push_back(vecVertex[1].x);
			pv.push_back(vecVertex[1].y);
			pv.push_back(vecVertex[1].z);
			pv.push_back(vecVertex[2].x);
			pv.push_back(vecVertex[2].y);
			pv.push_back(vecVertex[2].z);
			nv.push_back(vecNormal.x);
			nv.push_back(vecNormal.y);
			nv.push_back(vecNormal.z);
			nv.push_back(vecNormal.x);
			nv.push_back(vecNormal.y);
			nv.push_back(vecNormal.z);
			nv.push_back(vecNormal.x);
			nv.push_back(vecNormal.y);
			nv.push_back(vecNormal.z);
			indices.push_back(k*3);
			indices.push_back(k*3+1);
			indices.push_back(k*3+2);
			k++;
		}

	}
		

	ofs.close();

	return 0;
}

int kb::loadAsSTL(
	const std::string& path1, 
	std::vector< float >& pv,
	std::vector< float >& nv,
	std::vector< int >& indices
	)
{
	int rtn=kb::loadAsSTL_ascii(path1, pv, nv, indices);
	if( rtn<0 ){
		rtn=kb::loadAsSTL_bin(path1, pv, nv, indices);
	}
	return rtn;
}

int kb::loadAsSTL_bin(
	const std::string& path1, 
	std::vector< float >& pv,
	std::vector< float >& nv,
	std::vector< int >& indices
	)
{
	std::ifstream fs(path1, std::ios_base::in | std::ios_base::binary);

	unsigned char header[80];
	unsigned int num_patch=0;

	fs.read((char*)header, 80);
	fs.read((char*)(&num_patch), 4);
	if( num_patch<1 )
		return -1;


	struct triangle
	{
		float nv[3];
		float p1[3];
		float p2[3];
		float p3[3];
		short reserved;
	};
	std::cout<<num_patch<<" "<<sizeof(triangle)<<std::endl;



	pv.resize(num_patch*9);
	nv.resize(num_patch*9);
	indices.resize(num_patch*3);
	for(int i=0;i<num_patch;i++){
		triangle tr;
		fs.read((char*)(&tr), 50);

		//if( (i%1000)==0 ){
		//	std::cout<<tr[i].p1[0]<<" "<<tr[i].p1[1]<<" "<<tr[i].p1[2]<<std::endl;
		//}
		int i3 = i * 3;
		int i9 = i * 9;
		pv[i9+0]=tr.p1[0];
		pv[i9+1]=tr.p1[1];
		pv[i9+2]=tr.p1[2];
		pv[i9+3]=tr.p2[0];
		pv[i9+4]=tr.p2[1];
		pv[i9+5]=tr.p2[2];
		pv[i9+6]=tr.p3[0];
		pv[i9+7]=tr.p3[1];
		pv[i9+8]=tr.p3[2];

		nv[i9+0]=tr.nv[0];
		nv[i9+1]=tr.nv[1];
		nv[i9+2]=tr.nv[2];
		nv[i9+3]=tr.nv[0];
		nv[i9+4]=tr.nv[1];
		nv[i9+5]=tr.nv[2];
		nv[i9+6]=tr.nv[0];
		nv[i9+7]=tr.nv[1];
		nv[i9+8]=tr.nv[2];

		indices[i3+0]=i3;
		indices[i3+1]=i3+1;
		indices[i3+2]=i3+2;
	}

	fs.close();
	
	return 0;
}

int kb::saveAsSTL(
	const std::string& path1,
	std::vector< float >& vpos,
	std::vector< int >& indexElements
)
{
	std::vector< float  > vnv_f, vnv;
	kb::normal_vector_on_mesh(vpos, indexElements, vnv, vnv_f);


	int numP = vpos.size()/3;
	int numElements = indexElements.size() / 3;

	
	std::ofstream ofs(path1);
	ofs << "solid kb\n";
	for (size_t k = 0; k < numElements; k++) {

		int idx[3] = {
			indexElements[k * 3 + 0] * 3,
			indexElements[k * 3 + 1] * 3,
			indexElements[k * 3 + 2] * 3
		};

		double v1[9] = {
			vpos[idx[0] + 0], vpos[idx[0] + 1], vpos[idx[0] + 2],
			vpos[idx[1] + 0], vpos[idx[1] + 1], vpos[idx[1] + 2],
			vpos[idx[2] + 0], vpos[idx[2] + 1], vpos[idx[2] + 2]
		};

		double nv[3] = {
			vnv[idx[0] + 0],
			vnv[idx[0] + 1],
			vnv[idx[0] + 2]
		};


		char strV1[512];
		int nn = 512;
		{
			sprintf_s(strV1, nn, "facet normal %.06f %.06f %.06f\n", nv[0], nv[1], nv[2]);	ofs << strV1;
			ofs << "outer loop\n";
			sprintf_s(strV1, nn, "vertex %.06f %.06f %.06f\n", v1[0], v1[1], v1[2]);		ofs << strV1;
			sprintf_s(strV1, nn, "vertex %.06f %.06f %.06f\n", v1[3], v1[4], v1[5]);		ofs << strV1;
			sprintf_s(strV1, nn, "vertex %.06f %.06f %.06f\n", v1[6], v1[7], v1[8]);		ofs << strV1;
			ofs << "endloop\n";
			ofs << "endfacet\n";
		}

	}
	ofs << "endsolid\n";
	ofs.close();


	return 0;
}


int kb::saveAsPly(
		const std::string& path1, 
		std::vector< mist::vector3< double > >& pv,
		std::vector< mist::vector3< double > >& nv,
		std::vector< unsigned char >& colors
		)
{
	int cnt_vtx=pv.size();
	int cnt_clr=colors.size()/3;
	if( cnt_vtx!=cnt_clr )
		return -1;

	std::ofstream file(path1.c_str());
	file<<"ply"<<std::endl;
	file<<"format ascii 1.0"<<std::endl;
	file<<"element vertex "<<cnt_vtx<<std::endl;
	file<<"property float x"<<std::endl;
	file<<"property float y"<<std::endl;
	file<<"property float z"<<std::endl;
	file<<"property float nx"<<std::endl;
	file<<"property float ny"<<std::endl;
	file<<"property float nz"<<std::endl;
	file<<"property uchar diffuse_red"<<std::endl;
	file<<"property uchar diffuse_green"<<std::endl;
	file<<"property uchar diffuse_blue"<<std::endl;
	file<<"end_header"<<std::endl;

	for(int i=0;i<cnt_vtx;i++){
		file<<pv[i].x<<" "<<pv[i].y<<" "<<pv[i].z<<" "
			<<nv[i].x<<" "<<nv[i].y<<" "<<nv[i].z<<" "
			<<(int)colors[i*3]<<" "<<(int)colors[i*3+1]<<" "<<(int)colors[i*3+2]<<std::endl;
	}
	return 0;
}



int kb::saveAsObj(
	const std::string& path1, 
	const std::string& header, 
	std::vector< mist::vector3<double> >& oPos
	)
{
	std::ofstream file(path1);
	file<<"g "<<header<<std::endl;

	int numNodes=oPos.size();
	for(size_t k=0;k<numNodes;k++){		
		mist::vector3<double> pt=oPos[k];
		file<<"v "<<pt.x<<" "<<pt.y<<" "<<pt.z<<std::endl;
	}

	return 0;
}

int kb::loadVertexAndDirectionalVectors(
		const std::string& path1, 
		std::vector< mist::vector3< double > >& points,
		std::vector< mist::vector3< double > >& normals
		)
{
	std::ifstream file(path1.c_str());

	while(1){
		mist::vector3< double > pt, nv;
		std::string str1;
		file>>str1; pt.x=atof(str1.c_str());
		file>>str1; pt.y=atof(str1.c_str());
		file>>str1; pt.z=atof(str1.c_str());
		file>>str1; nv.x=atof(str1.c_str());
		file>>str1; nv.y=atof(str1.c_str());
		file>>str1; nv.z=atof(str1.c_str());
		if( file.eof()==true )
			break;

		points.push_back(pt);
		normals.push_back(nv);
	}

	return 0;
}





int kb::saveIndex(
	std::string& path,
	mist::array3<unsigned char>& voxelThinning,		//	ラベル付された細線化画像
	int index
	)
{
	int cx=voxelThinning.width();
	int cy=voxelThinning.height();
	int cz=voxelThinning.depth();
	double r1=voxelThinning.reso1();
	double r2=voxelThinning.reso2();
	double r3=voxelThinning.reso3();

	std::ofstream file( path.c_str() );

	std::vector< mist::vector3<float> > points_stl_all, normals_stl_all;
	for(size_t k=0;k<cz;k++){
		for(size_t j=0;j<cy;j++){
			for(size_t i=0;i<cx;i++){
				if( voxelThinning(i,j,k)>0 ){
					if( voxelThinning(i,j,k)==index ){
						file<<i<<" "<<j<<" "<<k<<std::endl;
					}
				}
			}
		}
	}

	return 0;
}









int kb::fillHoleLabelingSTL(
	std::vector< mist::vector3< double > >& nodes,
	std::vector<int>& indexOfNodeInElement,
	std::vector<int>& labelElements,
	std::vector<int>& stateElementsOut
	)
{
	int num_nodes=nodes.size();
	int num_elements=indexOfNodeInElement.size()/3;
	int num_elements2=labelElements.size();

	//	ノードからエレメントを辿るテーブルを作成
	std::vector< std::vector<int> > lutNode2Element;
	lutNode2Element.resize(num_nodes);
	for(int j=0;j<num_elements;j++){
		int i1=indexOfNodeInElement[j*3];
		int i2=indexOfNodeInElement[j*3+1];
		int i3=indexOfNodeInElement[j*3+2];

		lutNode2Element[i1].push_back(j);
		lutNode2Element[i2].push_back(j);
		lutNode2Element[i3].push_back(j);
	}

	//	選択状態のエレメントに属するノードの選択状態を取得
	std::vector<int> labelNodes; labelNodes.resize(num_nodes, 0);
	for(int j=0;j<num_elements;j++){
		if( labelElements[j]>0 ){
			int i1=indexOfNodeInElement[j*3];
			int i2=indexOfNodeInElement[j*3+1];
			int i3=indexOfNodeInElement[j*3+2];
			labelNodes[i1]=labelElements[j];
			labelNodes[i2]=labelElements[j];
			labelNodes[i3]=labelElements[j];
		}
	}

	//	選択状態のエレメントのノードを選択状態だとしたとき、選択状態のノードに囲まれた
	//	非選択エレメントを選択状態にする
	{
		std::vector<int> labels1=labelElements;
		{
			for(int j=0;j<num_elements;j++){
				if( labels1[j]>0 )
					continue;

				//	
				//	エレメントに属するノードを取得
				int cnt_selected=0;
				int idx[3]={ indexOfNodeInElement[j*3], indexOfNodeInElement[j*3+1], indexOfNodeInElement[j*3+2] };
				for( int k=0;k<3;k++){
					if( labelNodes[ idx[k] ]>0 ){
						cnt_selected++;
					}
				}
				if( cnt_selected==3 ){
					if( labelNodes[ idx[0] ]==labelNodes[ idx[1] ] &&
						labelNodes[ idx[0] ]==labelNodes[ idx[2] ] )
					{
						labels1[j]=labelNodes[ idx[0] ];
					}
				}
			}
		}

		stateElementsOut=labels1;
	}

	return 0;
}


int kb::fillHoleLabelingSTL2(
	std::vector< mist::vector3< double > >& nodes,
	std::vector<int>& indexOfNodeInElement,
	std::vector<int>& labelElements,
	std::vector<int>& stateElementsOut
	)
{
	int num_nodes=nodes.size();
	int num_elements=indexOfNodeInElement.size()/3;
	int num_elements2=labelElements.size();

	//	ノードからエレメントを辿るテーブルを作成
	std::vector< std::vector<int> > lutNode2Element;
	lutNode2Element.resize(num_nodes);
	for(int j=0;j<num_elements;j++){
		int i1=indexOfNodeInElement[j*3];
		int i2=indexOfNodeInElement[j*3+1];
		int i3=indexOfNodeInElement[j*3+2];

		lutNode2Element[i1].push_back(j);
		lutNode2Element[i2].push_back(j);
		lutNode2Element[i3].push_back(j);
	}

	//	選択状態のエレメントに属するノードの選択状態を取得
	std::vector<int> labelNodes; labelNodes.resize(num_nodes, 0);
	for(int j=0;j<num_elements;j++){
		if( labelElements[j]>0 ){
			int i1=indexOfNodeInElement[j*3];
			int i2=indexOfNodeInElement[j*3+1];
			int i3=indexOfNodeInElement[j*3+2];
			labelNodes[i1]=labelElements[j];
			labelNodes[i2]=labelElements[j];
			labelNodes[i3]=labelElements[j];
		}
	}

	//	選択状態のエレメントのノードを選択状態だとしたとき、選択状態のノードに囲まれた
	//	非選択エレメントを選択状態にする
	{
		std::vector<int> labels1=labelElements;
		{
			for(int j=0;j<num_elements;j++){
				if( labels1[j]>0 )
					continue;

				//	
				//	エレメントに属するノードを取得
				int cnt_selected=0;
				int idx[3]={ indexOfNodeInElement[j*3], indexOfNodeInElement[j*3+1], indexOfNodeInElement[j*3+2] };
				for( int k=0;k<3;k++){
					if( labelNodes[ idx[k] ]>0 ){
						cnt_selected++;
					}
				}
				if( cnt_selected==3 ){
					if( labelNodes[ idx[0] ]==labelNodes[ idx[1] ] &&
						labelNodes[ idx[0] ]==labelNodes[ idx[2] ] )
					{
						labels1[j]=labelNodes[ idx[0] ];
					}
				}
			}
		}

		stateElementsOut=labels1;
	}

	return 0;
}

int kb::getNodeIndices(
	std::vector< mist::vector3< double > >& nodes,
	std::vector<int>& indexOfNodeInElement,
	std::vector<int>& labelOfEachElement,
	int indexN,
	std::vector<int>& indexNodes
	)
{
	int num_nodes=nodes.size();
	int num_elements=indexOfNodeInElement.size()/3;
	int num_elements2=labelOfEachElement.size();

	//	ノードからエレメントを辿るテーブルを作成
	std::vector< std::vector<int> > lutNode2Element;
	lutNode2Element.resize(num_nodes);
	for(int j=0;j<num_elements;j++){
		int i1=indexOfNodeInElement[j*3];
		int i2=indexOfNodeInElement[j*3+1];
		int i3=indexOfNodeInElement[j*3+2];

		lutNode2Element[i1].push_back(j);
		lutNode2Element[i2].push_back(j);
		lutNode2Element[i3].push_back(j);
	}


	int num=lutNode2Element[indexN].size();
	for(int i=0;i<num;i++){
		int j1=lutNode2Element[indexN][i];

	}


	return 0;
}


int kb::fillHoleSelectedSTL(
	std::vector< mist::vector3< double > >& pv_stl2,
	std::vector<int>& index_stl2,
	std::vector<int>& stateElements,
	std::vector<int>& stateElementsOut
	)
{
	int num_nodes=pv_stl2.size();
	int num_elements=index_stl2.size()/3;
	int num_elements2=stateElements.size();

	//	ノードからエレメントを辿るテーブルを作成
	std::vector< std::vector<int> > lutNode2Element;
	lutNode2Element.resize(num_nodes);
	for(int j=0;j<num_elements;j++){
		int i1=index_stl2[j*3];
		int i2=index_stl2[j*3+1];
		int i3=index_stl2[j*3+2];

		lutNode2Element[i1].push_back(j);
		lutNode2Element[i2].push_back(j);
		lutNode2Element[i3].push_back(j);


	}

	//	選択状態のエレメントに属するノードの選択状態を取得
	std::vector<int> stateNodes; stateNodes.resize(num_nodes, 0);
	for(int j=0;j<num_elements;j++){
		if( stateElements[j]>0 ){
			int i1=index_stl2[j*3];
			int i2=index_stl2[j*3+1];
			int i3=index_stl2[j*3+2];
			stateNodes[i1]=1;
			stateNodes[i2]=1;
			stateNodes[i3]=1;
		}
	}

	//	選択状態のエレメントのノードを選択状態だとしたとき、選択状態のノードに囲まれた
	//	非選択エレメントを選択状態にする
	{
		std::vector<int> stateE1=stateElements;
		{
			for(int j=0;j<num_elements;j++){
				if( stateE1[j]==1 )
					continue;

				//	
				//	エレメントに属するノードを取得
				int cnt_selected=0;
				int idx[3]={ index_stl2[j*3], index_stl2[j*3+1], index_stl2[j*3+2] };
				for( int k=0;k<3;k++){
					if( stateNodes[ idx[k] ]==1 ){
						cnt_selected++;
					}
				}
				if( cnt_selected==3 ){
					stateE1[j]=1;
				}
			}
		}

		stateElementsOut=stateE1;
	}

	return 0;
}

