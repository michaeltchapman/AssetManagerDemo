//


#include "MeshConsumer.h"
#include  "ExampleStaticData.h"


// Sets default values
AMeshConsumer::AMeshConsumer()
	: Super()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = StaticMeshComponent;
}

void AMeshConsumer::ConsumeAsset_Implementation(UExampleStaticData* DataAsset)
{
	if (DataAsset && StaticMeshComponent)
	{
		StaticMeshComponent->SetStaticMesh(DataAsset->GetMesh());
	}
}

// Called when the game starts or when spawned
void AMeshConsumer::BeginPlay()
{
	Super::BeginPlay();

}

