/*
 * This file contains software that has been made available under
 * The Mozilla Public License 1.1. Use and distribution hereof are
 * subject to the restrictions set forth therein.
 *
 * Copyright (c) 2003 TADA AB - Taby Sweden
 * All Rights Reserved
 */
#ifndef __pljava_Exception_h
#define __pljava_Exception_h

#include "pljava/PgObject.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Like ereport(ERROR, ...) but this method will raise a Java SQLException and
 * return. It will NOT do a longjmp. Suitable in native code that is called
 * from Java (such code must return to Java in order to have the real exception
 * thrown).
 */
extern void Exception_throw(JNIEnv* env, int errCode, const char* errMessage, ...)
/* This extension allows gcc to check the format string for consistency with
   the supplied arguments. */
__attribute__((format(printf, 3, 4)));

/*
 * Like ereport(ERROR, ...) but this method will raise a Java SQLException and
 * return. It will NOT do a longjmp.
 */
extern void Exception_throwSPI(JNIEnv* env, const char* function);

/*
 * Like ereport(ERROR, ...) but this method will raise a Java SQLException and
 * return. It will NOT do a longjmp. It's intended use is in PLJAVA_CATCH
 * clauses.
 */
extern void Exception_throwSPI_ERROR(JNIEnv* env, const char* function);

/*
 * This method is part of the thread fence mechanism. It will be called when
 * a thread other than main is attempting to enter the PostgreSQL backend code.
 */
extern void Exception_threadException(JNIEnv* env);

/*
 * This method is part of the elog ERROR trap/fence mechanism. It will be called
 * when an attempt is made to enter the PostgreSQL code after an elog(ERROR) has
 * been issued and caught.
 */
extern void Exception_elogErrorException(JNIEnv* env);

/*
 * Checks if a Java exception has been thrown. If so, ereport(ERROR, ...) is
 * called. There's no return from this method if that happens. This method
 * is called at the completion of each call to a function or trigger.
 */
extern void Exception_checkException(JNIEnv* env);

/*
 * Throw an exception indicating that wanted member could not be
 * found. This is an ereport(ERROR...) so theres' no return from
 * this function.
 */
extern void Exception_throwMemberError(const char* memberName, const char* signature, bool isMethod, bool isStatic);

extern Datum Exception_initialize(PG_FUNCTION_ARGS);

#ifdef __cplusplus
}
#endif
#endif
