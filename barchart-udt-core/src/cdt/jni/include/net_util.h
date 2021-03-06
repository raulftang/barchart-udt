/*
 * @(#)net_util.h	1.46 05/11/17
 *
 * Copyright 2006 Sun Microsystems, Inc. All rights reserved.
 * SUN PROPRIETARY/CONFIDENTIAL. Use is subject to license terms.
 */

#ifndef NET_UTILS_H
#define NET_UTILS_H

#include "jvm.h"
#include "jni_util.h"
#include "net_util_md.h"

/************************************************************************
 * Macros and misc constants
 */

#define MAX_PACKET_LEN 65536

#define IPv4 1
#define IPv6 2

#define NET_ERROR(env, ex, msg) \
{ if (!(*env)->ExceptionOccurred(env)) JNU_ThrowByName(env, ex, msg) }

#define CHECK_NULL(x) if ((x) == NULL) return;
#define CHECK_NULL_RETURN(x, y) if ((x) == NULL) return y;

/************************************************************************
 * Cached field IDs
 *
 * The naming convention for field IDs is
 *      <class abbrv>_<fieldName>ID
 * i.e. psi_timeoutID is PlainSocketImpl's timeout field's ID.
 */
extern jclass ia_class;
extern jfieldID ia_addressID;
extern jfieldID ia_familyID;
extern jfieldID ia_preferIPv6AddressID;

extern jclass ia4_class;
extern jmethodID ia4_ctrID;

extern jclass ia6_class;
extern jfieldID ia6_ipaddressID;
extern jfieldID ia6_scopeidID;
extern jfieldID ia6_scopeidsetID;
extern jmethodID ia6_ctrID;

/* NetworkInterface fields */
extern jclass ni_class;
extern jfieldID ni_nameID;
extern jfieldID ni_indexID;
extern jfieldID ni_addrsID;
extern jfieldID ni_descID;
extern jmethodID ni_ctrID;

/* PlainSocketImpl fields */
extern jfieldID psi_timeoutID;
extern jfieldID psi_fdID;
extern jfieldID psi_addressID;
extern jfieldID psi_portID;
extern jfieldID psi_localportID;

/* DatagramPacket fields */
extern jfieldID dp_addressID;
extern jfieldID dp_portID;
extern jfieldID dp_bufID;
extern jfieldID dp_offsetID;
extern jfieldID dp_lengthID;
extern jfieldID dp_bufLengthID;

/* Inet6Address fields */
extern jclass ia6_class;
extern jfieldID ia6_ipaddressID;
extern jfieldID ia6_scopeidID;
extern jfieldID ia6_scopeidsetID;
extern jfieldID ia6_scopeifnameID;
extern jfieldID ia6_scopeifnamesetID;
extern jmethodID ia6_ctrID;

/************************************************************************
 *  Utilities
 */
JNIEXPORT void JNICALL Java_java_net_InetAddress_init(JNIEnv *env, jclass cls);
JNIEXPORT void JNICALL Java_java_net_Inet4Address_init(JNIEnv *env, jclass cls);
JNIEXPORT void JNICALL Java_java_net_Inet6Address_init(JNIEnv *env, jclass cls);
JNIEXPORT void JNICALL Java_java_net_NetworkInterface_init(JNIEnv *env, jclass cls);

JNIEXPORT void JNICALL NET_ThrowNew(JNIEnv *env, int errorNum, char *msg);
int NET_GetError();

void NET_ThrowCurrent(JNIEnv *env, char *msg);

jfieldID NET_GetFileDescriptorID(JNIEnv *env);

JNIEXPORT jint JNICALL ipv6_available() ;

void 
NET_AllocSockaddr(struct sockaddr **him, int *len);

JNIEXPORT int JNICALL
NET_InetAddressToSockaddr(JNIEnv *env, jobject iaObj, int port, struct sockaddr *him, int *len, jboolean isLocalAddr);

jobject
NET_SockaddrToInetAddress(JNIEnv *env, struct sockaddr *him, int *port);

void initLocalAddrTable ();

void
NET_SetTrafficClass(struct sockaddr *him, int trafficClass);

jint
NET_GetPortFromSockaddr(struct sockaddr *him);

jint
NET_SockaddrEqualsInetAddress(JNIEnv *env,struct sockaddr *him, jobject iaObj);

int 
NET_IsIPv4Mapped(jbyte* caddr);

int
NET_IPv4MappedToIPv4(jbyte* caddr);

int 
NET_IsEqual(jbyte* caddr1, jbyte* caddr2);

/* Socket operations 
 *
 * These work just like the JVM_* procedures, except that they may do some 
 * platform-specific pre/post processing of the arguments and/or results.
 */

JNIEXPORT int JNICALL
NET_GetSockOpt(int fd, int level, int opt, void *result, int *len);

JNIEXPORT int JNICALL
NET_SetSockOpt(int fd, int level, int opt, const void *arg, int len);

JNIEXPORT int JNICALL
NET_Bind(int fd, struct sockaddr *him, int len);

JNIEXPORT int JNICALL
NET_MapSocketOption(jint cmd, int *level, int *optname);

JNIEXPORT int JNICALL
NET_MapSocketOptionV6(jint cmd, int *level, int *optname);

int getScopeID (struct sockaddr *);

int cmpScopeID (unsigned int, struct sockaddr *);

unsigned short in_cksum(unsigned short *addr, int len);
#endif /* NET_UTILS_H */
