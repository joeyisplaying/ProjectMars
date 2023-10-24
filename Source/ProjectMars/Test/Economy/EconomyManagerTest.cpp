﻿#include "Misc/AutomationTest.h"
#include "ProjectMars/Economy/EconomyManager.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FInitialiseIncomeSourcesTest, "ProjectMars.ProjectMars.Test.Economy.InitialiseIncomeSourcesTest",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FInitialiseIncomeSourcesTest::RunTest(const FString& Parameters)
{
	{
		// given
		const UEconomyManager* EconomyManager = NewObject<UEconomyManager>();
		const TMap<EIncomeType, int32>* IncomeSourcesMap = EconomyManager->GetIncomeSources();
		const TMap<EExpenseType, int32>* ExpenseSources = EconomyManager->GetExpenseSources();
		
		// when

		// then
		TestTrue("Test income sources map correctly initialised", IncomeSourcesMap->Num() == 5);
		TestTrue(TEXT("Test income sources map correctly initialised"),IncomeSourcesMap->Contains(EIncomeType::Tax));
		TestTrue(TEXT("Test income sources map correctly initialised"),IncomeSourcesMap->Contains(EIncomeType::Trade));
		TestTrue(TEXT("Test income sources map correctly initialised"),IncomeSourcesMap->Contains(EIncomeType::Production));
		TestTrue(TEXT("Test income sources map correctly initialised"),IncomeSourcesMap->Contains(EIncomeType::Loot));
		TestTrue(TEXT("Test income sources map correctly initialised"),IncomeSourcesMap->Contains(EIncomeType::Slaves));

		TestTrue("Test income sources map correctly initialised", ExpenseSources->Num() == 4);
		TestTrue(TEXT("Test income sources map correctly initialised"),ExpenseSources->Contains(EExpenseType::Army));
		TestTrue(TEXT("Test income sources map correctly initialised"),ExpenseSources->Contains(EExpenseType::Navy));
		TestTrue(TEXT("Test income sources map correctly initialised"),ExpenseSources->Contains(EExpenseType::Tribute));
		TestTrue(TEXT("Test income sources map correctly initialised"),ExpenseSources->Contains(EExpenseType::Corruption));
	}
	return true;
}
