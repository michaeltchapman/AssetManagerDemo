//


#include "TextureConsumer.h"

ATextureConsumer::ATextureConsumer()
	: Super()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = StaticMeshComponent;
}

void ATextureConsumer::ConsumeAsset_Implementation(UExampleStaticData* DataAsset)
{
}
