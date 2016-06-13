#ifndef BDN_IViewCore_H_
#define BDN_IViewCore_H_

namespace bdn
{

class IViewCore : BDN_IMPLEMENTS IBase
{
public:

	/** Shows/hides the view core.*/
	virtual void	setVisible(const bool& visible)=0;


	/** Called when the outer view's parent has changed.
		
		tryChangeParentView should try to move the core over to the new parent.

		If successful then it should return true, otherwise false.

		If false is returned then this will cause the outer view object to
		automatically re-create the core for the new parent and release the current
		core object.		
		*/
	virtual bool tryChangeParentView(View* pNewParent)=0;
	
};


}

#endif
