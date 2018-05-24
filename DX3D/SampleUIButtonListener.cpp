#include "stdafx.h"
#include "SampleUIButtonListener.h"

void SampleUIButtonListener::OnMouseEnter()
{
    cout << "OnMouseEnter()\n";
}

void SampleUIButtonListener::OnMouseExit()
{
    cout << "OnMouseExit()\n";
}

void SampleUIButtonListener::OnMouseDown(const int key)
{
    cout << "OnMouseDown()\n";
}

void SampleUIButtonListener::OnMouseUp(const int key)
{
    cout << "OnMouseUp()\n";
}

void SampleUIButtonListener::OnMouseDrag(const int key)
{
    Debug->AddText("OnMouseDrag()\n");
}
