

#include "X_Com3SetCharacter.h" 

AX_Com3SetCharacter::AX_Com3SetCharacter()
{
	
}

void AX_Com3SetCharacter::SetupInput()
{
	InputComponent->BindAction("SetCharacter", IE_Released, this, &AX_Com3SetCharacter::SelectUnit);
}

void AX_Com3SetCharacter::SelectUnit()
{
	
}
