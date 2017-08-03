#include <bdn/init.h>
#include <bdn/Window.h>

#include <bdn/LayoutCoordinator.h>
#include <bdn/debug.h>

namespace bdn
{

Window::Window(IUiProvider* pUiProvider)
{
	// windows are invisible by default
	_visible = false;

	_pUiProvider = (pUiProvider!=nullptr) ? pUiProvider : getDefaultUiProvider().getPtr();

	initProperty<String, IWindowCore, &IWindowCore::setTitle, (int)PropertyInfluence_::none>(_title);

	reinitCore();
}


void Window::setContentView(View* pContentView)
{
	MutexLock lock( getHierarchyAndCoreMutex() );

	if(pContentView!=_pContentView)
	{
		if(_pContentView!=nullptr)
			_pContentView->_setParentView(nullptr);

		_pContentView = pContentView;

        if(_pContentView!=nullptr)
			_pContentView->_setParentView(this);

        invalidateSizingInfo( InvalidateReason::childAddedOrRemoved );
	}
}


void Window::requestAutoSize()
{
    P<IWindowCore> pCore = cast<IWindowCore>( getViewCore() );

    // forward the request to the core. Depending on the platform
    // it may be that the UI uses a layout coordinator provided by the system,
    // rather than our own.
    if(pCore!=nullptr)
        pCore->requestAutoSize();	
}

void Window::requestCenter()
{
	// Since autosizing is asynchronous, this must also be done via
	// the layout coordination system. Otherwise we might center with the old size
	// and would then autoSize afterwards.
    // So, also forward this to the core.

    P<IWindowCore> pCore = cast<IWindowCore>( getViewCore() );

    if(pCore!=nullptr)
        pCore->requestCenter();	
}





}


