# Makefile for Wazuh APIs
# Copyright (C) 2015, Wazuh Inc.
# May 3, 2017
#
# Syntax: make [ all | install | service ]

WAZUH_USER        = wazuh-server
WAZUH_GROUP       = wazuh-server
WAZUH_SERVER      = wazuh-server
SHARE_INSTALLDIR  ?= /usr/share/${WAZUH_SERVER}
ETC_INSTALLDIR    ?= /etc/${WAZUH_SERVER}
BIN_INSTALLDIR    ?= ${SHARE_INSTALLDIR}/bin

MV_FILE        = mv -f
INSTALL_DIR    = install -o ${WAZUH_USER} -g ${WAZUH_GROUP} -m 0750 -d
INSTALL_EXEC   = install -o ${WAZUH_USER} -g ${WAZUH_GROUP} -m 0750
INSTALL_FILE   = install -o ${WAZUH_USER} -g ${WAZUH_GROUP} -m 0640


.PHONY: all install

all: install

install:

	$(INSTALL_DIR) $(SHARE_INSTALLDIR)/apis/scripts
	$(INSTALL_EXEC) scripts/wazuh_comms_apid.py ${SHARE_INSTALLDIR}/apis/scripts/wazuh-comms-apid.py

    # Install scripts/%.py on $(INSTALLDIR)/bin/%
	$(foreach script,$(wildcard scripts/*.py),$(INSTALL_EXEC) wrappers/generic_wrapper.sh $(patsubst scripts/%.py,${BIN_INSTALLDIR}/%,$(script));)

	$(MV_FILE) ${BIN_INSTALLDIR}/wazuh_comms_apid ${BIN_INSTALLDIR}/wazuh-comms-apid
