ACLOCAL_AMFLAGS=-I m4
AUTOMAKE_OPTIONS = foreign
AM_DISTCHECK_CONFIGURE_FLAGS = --enable-test-cpp \
			       --enable-test-perf \
			       --enable-test-vald \
			       --with-testdir

#@with_platform@ works alone in subdir but not as part of a path???
SUBDIRS = @platform_with_platform@ \
	  helper \
	  test \
	  helper/test \
	  doc \
	  example \
	  scripts

@DX_RULES@

EXTRA_DIST = bootstrap $(DX_CONFIG) CHANGELOG config/README .scmversion
