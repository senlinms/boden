
#include <bdn/AppRunnerBase.h>
#include <bdn/debug.h>

#include <bdn/UnhandledException.h>
#include <bdn/log.h>

namespace bdn
{
    std::thread::id AppRunnerBase::_mainThreadId;

    std::shared_ptr<AppRunnerBase> &_getAppRunnerRef()
    {
        static std::shared_ptr<AppRunnerBase> appRunner;
        return appRunner;
    }

    std::shared_ptr<AppRunnerBase> getAppRunner() { return _getAppRunnerRef(); }

    void _setAppRunner(std::shared_ptr<AppRunnerBase> pAppRunner) { _getAppRunnerRef() = pAppRunner; }

    void AppRunnerBase::prepareLaunch()
    {
        // ensure that the global mutex for safeinit is allocated. It is
        // important that this happens before multiple threads are created.
        //        SafeInitBase::_ensureReady();

        // mark the current thread as the main thread
        // Thread::_setMainId(std::this_thread::get_id());

        _mainThreadId = std::this_thread::get_id();

        // do additional platform-specific initialization (if needed)
        platformSpecificInit();

        // set the app controller as the global one
        std::shared_ptr<AppControllerBase> pAppController = _appControllerCreator();
        AppControllerBase::_set(pAppController);
    }

    void AppRunnerBase::beginLaunch()
    {
        _appControllerBeginLaunchCalled = true;
        AppControllerBase::get()->beginLaunch(_launchInfo);
    }

    void AppRunnerBase::finishLaunch() { AppControllerBase::get()->finishLaunch(_launchInfo); }

    void AppRunnerBase::launch()
    {
        prepareLaunch();

        beginLaunch();
        finishLaunch();
    }

    void AppRunnerBase::terminating()
    {
        if (_appControllerBeginLaunchCalled)
            AppControllerBase::get()->onTerminate();

        // the main dispatcher may still contain some pending items. However,
        // when we return from terminating then the destruction of global
        // variables may begin almost immediately. Since the app runner/ holds a
        // reference to the dispatcher, that means that any objects referenced
        // in pending work items will be destroyed with the app runner if we do
        // nothing. And since the app runner is created first, it will be
        // destroyed last. Which means that if the object's destructors access
        // any global objects then those might already be destroyed and we can
        // get a crash.
        disposeMainDispatcher();

        platformSpecificCleanup();
    }

    bool AppRunnerBase::unhandledException(bool canKeepRunning)
    {
        UnhandledException unhandled(std::current_exception(), canKeepRunning);

        BDN_LOG_AND_IGNORE_EXCEPTION(
            {
                std::shared_ptr<AppControllerBase> appController = AppControllerBase::get();
                if (appController != nullptr)
                    appController->unhandledProblem(unhandled);
            },
            "Exception while notifying app controller of unhandled exception. "
            "Ignoring the additional exception.");

        if (unhandled.shouldKeepRunning())
            return true;

        debugBreak();
        return false;
    }
}
