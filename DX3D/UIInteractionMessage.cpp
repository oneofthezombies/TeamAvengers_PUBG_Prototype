#include "stdafx.h"
#include "UIInteractionMessage.h"
#include "UIText.h"
#include "UIImage.h"
#include "UIManager.h"

UIInteractionMessage::UIInteractionMessage()
    : UIObject()
{
}

UIInteractionMessage::~UIInteractionMessage()
{
}

void UIInteractionMessage::Init()
{
    g_pUIManager->RegisterUIObject(*this);

    UIImage* fBox = new UIImage;
    fBox->SetTexture("resources/images/fbox.png");
    AddChild(*fBox);

    UIText* f = new UIText;
    f->SetFont(g_pFontManager->GetFont(Font::kInteractionMessageF));
    f->SetText(TEXT("F"));
    f->SetColor(D3DCOLOR_XRGB(255, 255, 255));
    f->SetSize(fBox->GetSize());
    f->SetPosition(D3DXVECTOR3(0.0f, 10.0f, 0.0f));
    fBox->AddChild(*f);

    UIText* desc = new UIText;
    desc->SetFont(g_pFontManager->GetFont(Font::kInteractionMessageDescription));
    desc->SetText(TEXT("상자 삭제"));
    desc->SetDrawTextFormat(DT_LEFT);
    desc->SetPosition(D3DXVECTOR3(22.0f, 10.0f, 0.0f));
    desc->SetSize(D3DXVECTOR2(100.0f, 20.0f));
    fBox->AddChild(*desc);
}
