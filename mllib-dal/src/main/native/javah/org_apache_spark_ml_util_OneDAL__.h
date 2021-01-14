/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_apache_spark_ml_util_OneDAL__ */

#ifndef _Included_org_apache_spark_ml_util_OneDAL__
#define _Included_org_apache_spark_ml_util_OneDAL__
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_apache_spark_ml_util_OneDAL__
 * Method:    setNumericTableValue
 * Signature: (JIID)V
 */
JNIEXPORT void JNICALL Java_org_apache_spark_ml_util_OneDAL_00024_setNumericTableValue
  (JNIEnv *, jobject, jlong, jint, jint, jdouble);

/*
 * Class:     org_apache_spark_ml_util_OneDAL__
 * Method:    cAddNumericTable
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_org_apache_spark_ml_util_OneDAL_00024_cAddNumericTable
  (JNIEnv *, jobject, jlong, jlong);

/*
 * Class:     org_apache_spark_ml_util_OneDAL__
 * Method:    cSetDoubleBatch
 * Signature: (JI[DII)V
 */
JNIEXPORT void JNICALL Java_org_apache_spark_ml_util_OneDAL_00024_cSetDoubleBatch
  (JNIEnv *, jobject, jlong, jint, jdoubleArray, jint, jint);

/*
 * Class:     org_apache_spark_ml_util_OneDAL__
 * Method:    cFreeDataMemory
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_apache_spark_ml_util_OneDAL_00024_cFreeDataMemory
  (JNIEnv *, jobject, jlong);

/*
 * Class:     org_apache_spark_ml_util_OneDAL__
 * Method:    cCheckPlatformCompatibility
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_apache_spark_ml_util_OneDAL_00024_cCheckPlatformCompatibility
  (JNIEnv *, jobject);

/*
 * Class:     org_apache_spark_ml_util_OneDAL__
 * Method:    cNewCSRNumericTable
 * Signature: ([F[J[JJJ)J
 */
JNIEXPORT jlong JNICALL Java_org_apache_spark_ml_util_OneDAL_00024_cNewCSRNumericTable
  (JNIEnv *, jobject, jfloatArray, jlongArray, jlongArray, jlong, jlong);

#ifdef __cplusplus
}
#endif
#endif
