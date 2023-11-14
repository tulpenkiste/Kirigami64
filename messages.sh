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
$XGETTEXT --c++ --kde \
--from-code=UTF-8 \
-c i18n \
-ki18n:1 -ki18nc:1c,2 -ki18np:1,2 -ki18ncp:1c,2,3 -kki18n:1 -kki18nc:1c,2 -kki18np:1,2 -kki18ncp:1c,2,3 \
-kkli18n:1 -kkli18nc:1c,2 -kkli18np:1,2 -kkli18ncp:1c,2,3 \
-kI18N_NOOP:1 -kI18NC_NOOP:1c,2 --copyright-holder="Tulpenkiste" \
--msgid-bugs-address="https://codeberg.org/tulpenkiste/kirigami64" `find . \( -name \*.qml \)` -o $podir/kirigami64.pot