// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "StandaloneRendererPrivate.h"
#include "OpenGL/SlateOpenGLRenderer.h"
#include "MacWindow.h"
#include "MacTextInputMethodSystem.h"
#include "CocoaTextView.h"
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>

@interface FSlateOpenGLLayer : NSOpenGLLayer
@property (assign) NSOpenGLContext* Context;
@property (assign) NSOpenGLPixelFormat* PixelFormat;
@end

@interface FSlateCocoaView : FCocoaTextView
{
@public
	GLuint Framebuffer;
	GLuint Renderbuffer;
	FSlateRect ViewportRect;
}
@property (assign) NSOpenGLContext* Context;
@property (assign) NSOpenGLPixelFormat* PixelFormat;
@end
