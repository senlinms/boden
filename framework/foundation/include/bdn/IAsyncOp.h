#pragma once

#include <bdn/AbortedError.h>
#include <bdn/IAsyncNotifier.h>
#include <bdn/OneShotStateNotifier.h>
#include <bdn/UnfinishedError.h>

namespace bdn
{

    template <class ResultType> class IAsyncOp : virtual public Base
    {
      public:
        std::shared_ptr<IAsyncOp<ResultType>> shared_from_this()
        {
            return std::dynamic_pointer_cast<IAsyncOp<ResultType>>(Base::shared_from_this());
        }

        /** Returns the result of the operation, if it is done.
            Throws a UnfinishedError exception if the operation has not finished
           yet.

            If the operation has failed with an exception then getResult()
           throws that exception.

            */
        virtual ResultType getResult() const = 0;

        /** Signals that the operation should be aborted, if that is possible.6
            signalStop() returns immediately - it does not wait for the
           operation to finish.

            Has no effect if the operation has already finished.

            If the operation is aborted then the listeners registered at
           onDone() are notified as normal. getResult() will throw an
           AbortedError.

            Note that if the operation cannot be aborted then the operation may
           still finish normally, even after signalStop was called.
            */
        virtual void signalStop() = 0;

        /** Returns true if the operation has finished.*/
        virtual bool isDone() const = 0;

        /** Returns a reference to a notifier object that can be used to
           register "done" callback functions.

            It is guaranteed that each of the registered functions will be
           called.

            If the operation has already finished when the callback function is
           added then the notification call is scheduled immediately.

            */
        virtual IAsyncNotifier<std::shared_ptr<IAsyncOp>> &onDone() const = 0;
    };
}
