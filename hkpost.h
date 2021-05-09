#pragma once

#include "stdafx.h"

namespace hkpost {
	inline void hkpostexecute();
}

inline PostRender_t RetPostRender;

//

inline bool World() {

	Basic::gWorld = (UWorld*)(*(uintptr_t*)Basic::UWorld_Offset);
	if (!Basic::gWorld) return false;
	if (!Basic::gWorld->OwningGameInstance) return false;
	if (!Basic::gWorld->OwningGameInstance->LocalPlayers[0]) return false;
	if (!Basic::gWorld->OwningGameInstance->LocalPlayers[0]->PlayerController) return false;

	Basic::LocalPlayer = Basic::gWorld->OwningGameInstance->LocalPlayers[0];
	Basic::LocalController = Basic::gWorld->OwningGameInstance->LocalPlayers[0]->PlayerController;

	if (Basic::LocalController->AcknowledgedPawn) {
		world::bIsValid = true;
	}
	else {
		world::bIsValid = false;
	}
	

	return true;
}



inline void PostRender(UCanvas* pCanvas) {

	static SDK::UFortKismetLibrary* FortKismetLib = NULL;
	static SDK::UGameplayStatics* GameplayStatics = NULL;
	if (!FortKismetLib) FortKismetLib = (SDK::UFortKismetLibrary*)SDK::UFortKismetLibrary::StaticClass();
	if (!GameplayStatics) GameplayStatics = (SDK::UGameplayStatics*)SDK::UGameplayStatics::StaticClass();

	if (!pCanvas) return;
	if (!World()) return; 
	
	name.ComparisonIndex = 547448;
	name.Number = 0;

	ToggleKey.KeyName = name;

	if (!Basic::MathLib) Basic::MathLib = (SDK::UKismetMathLibrary*)SDK::UKismetMathLibrary::StaticClass();
	
	if (Basic::LocalController->WasInputKeyJustPressed(ToggleKey) & 1)
	{
		framework::show_menu = !framework::show_menu;
	}
	framework::render_menu(pCanvas);


	if (options::Aim::drawfov) {
		hkrender::DrawCircle(pCanvas, width / 2, height / 2, options::Aim::fov_range, 30, FLinearColor(255.0f, 255.0f, 255.0f, 255.0f));
	}

	FVector2D wnd_size = FVector2D(width, height);
	

}


inline void hkPostRender(UObject* pObject, UCanvas* pCanvas) {

	if (pCanvas) {

		PostRender(pCanvas);

	}

	return RetPostRender(pObject, pCanvas);
}

inline void hkpost::hkpostexecute() {

// HAHAAHA

}