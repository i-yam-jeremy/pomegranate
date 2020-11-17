#include "geo.h"

#include "bezier.h"

void geo::convertLsystemToGeo(FbxScene* scene, std::shared_ptr<lsystem::Output> lsystemOut, const char* name) {
	auto mesh = FbxMesh::Create(scene, name);

	geo::instanceBezierCurves(mesh, lsystemOut);

	auto node = FbxNode::Create(scene, name);
	node->SetNodeAttribute(mesh);
	scene->GetRootNode()->AddChild(node);
}