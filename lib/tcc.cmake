include(ExternalProject)

ExternalProject_Add (tcc
	PREFIX            tcc
	URL               http://download.savannah.gnu.org/releases/tinycc/tcc-0.9.27.tar.bz2
	URL_HASH          SHA1=3bab3acd404ea92ba18e0c261d9d8cb2f366a8a5

	BUILD_ALWAYS      ON
        INSTALL_DIR       ${CMAKE_BINARY_DIR}
	CONFIGURE_COMMAND cd <SOURCE_DIR> && ./configure --prefix=<INSTALL_DIR>
	BUILD_COMMAND     cd <SOURCE_DIR> && make
	INSTALL_COMMAND   cd <SOURCE_DIR> && make install
)
