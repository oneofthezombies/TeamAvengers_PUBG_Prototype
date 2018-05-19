#pragma once

#define g_pObjMgr ObjManager::GetInstance()

class BaseObject;
class IDisplayObject;

class ObjManager
{
	SINGLETON(ObjManager)
private:
	set<BaseObject*> m_setObject;
	map<WORD, list<IDisplayObject*>> m_tagList;

public:
	void AddObject(BaseObject* pObj);
	void RemoveObject(BaseObject* pObj);
	void Destroy();

	void AddToTagList(WORD _tag, IDisplayObject* _pObj);
	void RemoveFromTagList(WORD _tag, IDisplayObject* _pObj);
	IDisplayObject* FindObjectByTag(WORD _tag);
	list<IDisplayObject*> FindObjectsByTag(WORD _tag);

};

