dnl Process this file with autoconf 2.52+ to produce a configure script.
dnl
dnl Copyright (C) 2001 Philipp Rumpf
dnl Copyright (C) 2004 Henrique de Moraes Holschuh <hmh@debian.org>
dnl
dnl This program is free software; you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation; either version 2 of the License, or
dnl (at your option) any later version.
dnl
dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with this program; if not, write to the Free Software
dnl Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

dnl Version is copied into SCSI 4-byte field, therefore, version must
dnl ALWAYS be exactly four bytes in length.

AC_INIT(itd, 0.01, [Jeff Garzik <jgarzik@pobox.com>])


AC_PREREQ(2.52)
AC_CONFIG_SRCDIR([main.c])
AM_INIT_AUTOMAKE([gnu])
AC_CONFIG_HEADERS([itd-config.h])

dnl Make sure anyone changing configure.ac/Makefile.am has a clue
AM_MAINTAINER_MODE

dnl Checks for programs
AC_PROG_CC
AC_PROG_RANLIB
AC_PROG_GCC_TRADITIONAL

dnl Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS(arpa/inet.h ctype.h errno.h fcntl.h inttypes.h)
AC_CHECK_HEADERS(netdb.h netinet/in.h netinet/tcp.h poll.h)
AC_CHECK_HEADERS(pwd.h signal.h stdarg.h stdint.h stdlib.h strings.h)
AC_CHECK_HEADERS(string.h syslog.h)
AC_CHECK_HEADERS(sys/mman.h sys/select.h sys/stat.h sys/time.h sys/uio.h)
AC_CHECK_HEADERS(sys/vfs.h unistd.h utime.h)

dnl Checks for typedefs, structures, and compiler characteristics.
dnl AC_TYPE_SIZE_T
dnl AC_TYPE_PID_T
AC_CHECK_TYPES(socklen_t)

dnl -----------------------------
dnl Checks for required libraries
dnl -----------------------------
AC_CHECK_LIB(crypto, MD5_Init, CRYPTO_LIBS=-lcrypto)
AC_CHECK_LIB(event, event_base_new, EVENT_LIBS=-levent,
  [AC_MSG_ERROR([Missing required libevent])])

dnl -------------------------------------
dnl Checks for optional library functions
dnl -------------------------------------
AC_CHECK_FUNCS(strlcpy syslog)

dnl -----------------
dnl Configure options
dnl -----------------

dnl --------------------------
dnl autoconf output generation
dnl --------------------------

AM_PATH_GLIB_2_0(2.0.0)
PKG_CHECK_MODULES(HAIL, libhail)

AC_SUBST(CRYPTO_LIBS)
AC_SUBST(EVENT_LIBS)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
