#include "AddConnection.h"
#include "../ApplicationManager.h"

AddConnection::AddConnection(ApplicationManager* pApp):Action(pApp)
{
	SrcPin = NULL;
	DstPin = NULL;
	PinNumber = 0;
}

AddConnection::~AddConnection(void)
{
}

void AddConnection::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	if (pManager->GetCompCount() < 2) {
		pOut->PrintMsg("too few components to be wired.");
		return;
	}

	Component* SrcCmpt = NULL;
	Component* DstCmpt = NULL;

	do {
		pOut->PrintMsg("Wire two components: Click on the source pin");
		pIn->GetPointClicked(sCx, sCy);
		SrcCmpt = pManager->GetClickedComponent(sCx, sCy);
	} while (SrcCmpt == NULL);

	SrcPin = SrcCmpt->GetOutputPin();

	
	do {
		pOut->PrintMsg("Wire two components: Click on the destination pin");
		pIn->GetPointClicked(dCx, dCy);
		DstCmpt = pManager->GetClickedComponent(dCx, dCy);
	} while (DstCmpt == NULL);

	PinNumber = DstCmpt->GetPinNumber();
	DstPin = DstCmpt->GetInputPins(PinNumber);
	
	pOut->ClearStatusBar();

}


void AddConnection::Execute()
{
	//Get Center points of source and destination pins
	ReadActionParameters();

	Output* pOut = pManager->GetOutput();
	
	GraphicsInfo GInfo; 

	GInfo.x1 = sCx;
	GInfo.y1 = sCy;
	GInfo.x2 = dCx;
	GInfo.y2 = dCy;


	Connection* pA = new Connection(GInfo, SrcPin, DstPin);
	if (pA->CanConnect())
		pManager->AddComponent(pA);
	else
	{
		delete pA;
		pOut->PrintMsg("Couldn't Connect these two components");
	}
		
}

void AddConnection::Undo()
{
}

void AddConnection::Redo()
{
}
