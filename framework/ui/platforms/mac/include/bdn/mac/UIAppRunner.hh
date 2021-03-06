#pragma once

#include <bdn/AppRunnerBase.h>

#import <Cocoa/Cocoa.h>

namespace bdn::mac
{
    class UIAppRunner : public AppRunnerBase
    {
      private:
        AppLaunchInfo _makeLaunchInfo(int argCount, char *args[]);

      public:
        UIAppRunner(std::function<std::shared_ptr<AppControllerBase>()> appControllerCreator, int argCount,
                    char *args[]);

        bool isCommandLineApp() const override;

        int entry();

        void initiateExitIfPossible(int exitCode) override;

        std::shared_ptr<IDispatcher> getMainDispatcher() override { return _mainDispatcher; }

        void disposeMainDispatcher() override;

        void openURL(const String &url) override;

        /** Used internally. Do not call.*/
        void _applicationWillFinishLaunching(NSNotification *notification);

        /** Used internally. Do not call.*/
        void _applicationDidFinishLaunching(NSNotification *notification);

        /** Used internally. Do not call.*/
        void _applicationDidBecomeActive(NSNotification *notification);

        /** Used internally. Do not call.*/
        void _applicationDidResignActive(NSNotification *notification);

        /** Used internally. Do not call.*/
        void _applicationWillTerminate(NSNotification *notification);

      private:
        std::shared_ptr<IDispatcher> _mainDispatcher;
    };
}
