//


#include "ExampleStaticData.h"

UStaticMesh* UExampleStaticData::GetMesh() const
{
	if (MeshPtr.IsValid())
		return MeshPtr.Get();
	return nullptr;
}

UTexture2D* UExampleStaticData::GetTexture() const
{
	if (TexturePtr.IsValid())
		return TexturePtr.Get();
	return nullptr;
}
