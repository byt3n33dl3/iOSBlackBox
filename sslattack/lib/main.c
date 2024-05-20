#include <CoreFoundation/CoreFoundation.h>

#include <objc/runtime.h>
#include <objc/message.h>

// This is a hack. Because we are writing in C, we cannot out and include 
// <UIKit/UIKit.h>, as that uses Objective-C constructs.
// however, neither can we give the full function declaration, like this:
// int UIApplicationMain (int argc, char *argv[], NSString *principalClassName, NSString *delegateClassName);
// So, we rely on the fact that for both the i386 & ARM architectures, 
// the registers for parameters passed in remain the same whether or not 
// you are using VA_ARGS. This is actually the basis of the objective-c 
// runtime (objc_msgSend), so we are probably fine here,  this would be
// the last thing I would expect to break.
extern int UIApplicationMain(int, ...);

// Entry point of the application. If you don't know what this is by now, 
// then you probably shouldn't be reading the rest of this post.
int main(int argc, char *argv[])
{
    // Create an @autoreleasepool, using the old-stye API. 
    // Note that while NSAutoreleasePool IS deprecated, it still exists 
    // in the APIs for a reason, and we leverage that here. In a perfect 
    // world we wouldn't have to worry about this, but, remember, this is C.
    id autoreleasePool = objc_msgSend(objc_msgSend(objc_getClass("NSAutoreleasePool"), sel_registerName("alloc")), sel_registerName("init"));

    UIApplicationMain(argc, argv, nil, CFSTR("AppDelegate"));

    objc_msgSend(autoreleasePool, sel_registerName("drain"));
}
