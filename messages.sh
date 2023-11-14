#! /usr/bin/env bash
# SPDX-FileCopyrightText: None
# SPDX-License-Identifier: CC0-1.0

if [ -z $XGETTEXT ]; then
	export XGETTEXT=xgettext
fi

if [ -z $podir ]; then
	export podir=./po
fi

mkdir -p $podir
#$XGETTEXT --c++ --kde `find . \( -name \*.cpp -o -name \*.hpp -o -name \*.qml \)` -o $podir/kirigami64.pot
$XGETTEXT --c++ --kde --copyright-holder="Tulpenkiste" \
--msgid-bugs-address="https://codeberg.org/tulpenkiste/kirigami64" `find . \( -name \*.qml \)` -o $podir/kirigami64.pot