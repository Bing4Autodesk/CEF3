// Copyright (c) 2014 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//

#include "libcef_dll/cpptoc/resource_bundle_handler_cpptoc.h"


// MEMBER FUNCTIONS - Body may be edited by hand.

int CEF_CALLBACK resource_bundle_handler_get_localized_string(
    struct _cef_resource_bundle_handler_t* self, int message_id,
    cef_string_t* string) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;
  // Verify param: string; type: string_byref
  DCHECK(string);
  if (!string)
    return 0;

  // Translate param: string; type: string_byref
  CefString stringStr(string);

  // Execute
  bool _retval = CefResourceBundleHandlerCppToC::Get(self)->GetLocalizedString(
      message_id,
      stringStr);

  // Return type: bool
  return _retval;
}

int CEF_CALLBACK resource_bundle_handler_get_data_resource(
    struct _cef_resource_bundle_handler_t* self, int resource_id, void** data,
    size_t* data_size) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;
  // Verify param: data; type: simple_byref
  DCHECK(data);
  if (!data)
    return 0;
  // Verify param: data_size; type: simple_byref
  DCHECK(data_size);
  if (!data_size)
    return 0;

  // Translate param: data; type: simple_byref
  void* dataVal = data?*data:NULL;
  // Translate param: data_size; type: simple_byref
  size_t data_sizeVal = data_size?*data_size:0;

  // Execute
  bool _retval = CefResourceBundleHandlerCppToC::Get(self)->GetDataResource(
      resource_id,
      dataVal,
      data_sizeVal);

  // Restore param: data; type: simple_byref
  if (data)
    *data = dataVal;
  // Restore param: data_size; type: simple_byref
  if (data_size)
    *data_size = data_sizeVal;

  // Return type: bool
  return _retval;
}


// CONSTRUCTOR - Do not edit by hand.

CefResourceBundleHandlerCppToC::CefResourceBundleHandlerCppToC(
    CefResourceBundleHandler* cls)
    : CefCppToC<CefResourceBundleHandlerCppToC, CefResourceBundleHandler,
        cef_resource_bundle_handler_t>(cls) {
  struct_.struct_.get_localized_string =
      resource_bundle_handler_get_localized_string;
  struct_.struct_.get_data_resource = resource_bundle_handler_get_data_resource;
}

#ifndef NDEBUG
template<> base::AtomicRefCount CefCppToC<CefResourceBundleHandlerCppToC,
    CefResourceBundleHandler, cef_resource_bundle_handler_t>::DebugObjCt = 0;
#endif

