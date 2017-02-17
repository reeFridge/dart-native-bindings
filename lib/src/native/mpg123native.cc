#include <mpg123.h>
#include "include/dart_api.h"
#include "include/dart_native_api.h"
#include <string.h>

mpg123_handle* mpg = NULL;
unsigned char* buffer = NULL;
int err = MPG123_OK;
size_t buffer_size = 0;
size_t done = 0;

Dart_NativeFunction ResolveName(Dart_Handle name, int argc, bool* auto_setup_scope);

DART_EXPORT Dart_Handle mpg123native_Init(Dart_Handle parent_library) {
  if (Dart_IsError(parent_library)) {
    return parent_library;
  }

  Dart_Handle result_code =
      Dart_SetNativeResolver(parent_library, ResolveName, NULL);
  if (Dart_IsError(result_code)) {
    return result_code;
  }

  return Dart_Null();
}

Dart_Handle HandleError(Dart_Handle handle) {
  if (Dart_IsError(handle)) {
    Dart_PropagateError(handle);
  }
  return handle;
}

void init(Dart_NativeArguments arguments) {
	Dart_Handle result = HandleError(Dart_NewInteger(mpg123_init()));
    Dart_SetReturnValue(arguments, result);
}

void create(Dart_NativeArguments arguments) {
	mpg = mpg123_new(NULL, NULL);
	Dart_Handle result = HandleError(Dart_NewBoolean(
		mpg != NULL
		));
    Dart_SetReturnValue(arguments, result);
}

void cleanup(Dart_NativeArguments arguments) {
	mpg123_close(mpg);
	mpg123_delete(mpg);
	mpg123_exit();
}

Dart_NativeFunction ResolveName(Dart_Handle name, int argc, bool* auto_setup_scope) {
  // If we fail, we return NULL, and Dart throws an exception.
  if (!Dart_IsString(name)) return NULL;
  Dart_NativeFunction result = NULL;
  const char* cname;
  HandleError(Dart_StringToCString(name, &cname));

  if (strcmp("init", cname) == 0) result = init;
  if (strcmp("cleanup", cname) == 0) result = cleanup;
  if (strcmp("create", cname) == 0) result = create;
  return result;
}