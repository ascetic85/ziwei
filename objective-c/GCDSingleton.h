//
//  GCDSingleton.h
//  BeOpenGLES
//
//  Created by Apple on 13-1-30.
//  Copyright (c) 2013年 Apple. All rights reserved.
//

#ifndef GCDSingleton_h
#define GCDSingleton_h


//
// come from https://gist.github.com/1057420
// chinese http://cocoa.venj.me/blog/singleton-in-objc/
//
#define DEFINE_SHARED_INSTANCE_USING_BLOCK(block) \
static dispatch_once_t pred = 0; \
__strong static id _sharedObject = nil; \
dispatch_once(&pred, ^{ \
_sharedObject = block(); \
}); \
return _sharedObject; \

//
// another imcomplete
//

/*!
 * @function Singleton GCD Macro
 */
#ifndef SINGLETON_GCD
#define SINGLETON_GCD(classname)                        \
\
+ (classname *)shared##classname {                      \
\
static dispatch_once_t pred;                        \
__strong static classname * shared##classname = nil;\
dispatch_once( &pred, ^{                            \
shared##classname = [[self alloc] init]; });    \
return shared##classname;                           \
}
#endif  // SINGLETON_GCD __END__ 

// Thank you lukeredpath !

#endif // GCDSingleton_h __END__
