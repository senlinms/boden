#pragma once

#include <bdn/java/JObject.h>

namespace bdn
{
    namespace java
    {

        /** Accessor for Java java.lang.Runnable objects.*/
        class JRunnable : public bdn::java::JObject
        {
          public:
            /** @param javaRef the reference to the Java object.
             *      The JObject instance will copy this reference and keep its
             * type. So if you want the JObject instance to hold a strong
             * reference then you need to call toStrong() on the reference first
             * and pass the result.
             *      */
            explicit JRunnable(const bdn::java::Reference &javaRef) : JObject(javaRef) {}

            /** Returns the JClass object for this class.
             *
             *  Note that the returned class object is not necessarily unique
             * for the whole process. You might get different objects if this
             * function is called from different shared libraries.
             *
             *  If you want to check for type equality then you should compare
             * the type name (see getTypeName() )
             *  */
            static bdn::java::JClass &getStaticClass_()
            {
                static bdn::java::JClass cls("java/lang/Runnable");

                return cls;
            }

            bdn::java::JClass &getClass_() override { return getStaticClass_(); }
        };
    }
}
