#include "PreCompiledHeader.h"
#include "DecoObject.h"

DecoObject::DecoObject()
{
	// 이것이 끝이다. 데코니까 소트오더를 좀 뒤로 해줍시다 ..!
	AddSpriteRenderer()->SetSortOrder(7);
}

DecoObject::~DecoObject()
{

}