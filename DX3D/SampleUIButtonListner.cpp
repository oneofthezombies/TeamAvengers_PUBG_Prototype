#include "stdafx.h"
#include "SampleUIButtonListner.h"

void SampleUIButtonListner::OnMouseEnter()
{
    cout << "OnMouseEnter()\n";
}

void SampleUIButtonListner::OnMouseExit()
{
    cout << "OnMouseExit()\n";
}

void SampleUIButtonListner::OnMouseDown(const int key)
{
    cout << "OnMouseDown()\n";
}

void SampleUIButtonListner::OnMouseUp(const int key)
{
    cout << "OnMouseUp()\n";
}

void SampleUIButtonListner::OnMouseDrag(const int key)
{
    Debug->AddText("OnMouseDrag()\n");
}
