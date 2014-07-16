#!/bin/sh
if [ $(ps ax | grep -v grep | grep "LANscapes_OF83.app" | wc -l) -eq 0 ]
then
echo "LANscapes not running. opening…"
open /OpenFrameworks/of_v0.8.3_osx_release/apps/LANscapes/LANscapes_OF83/bin/LANscapes_OF83.app
else
echo "LANscapes running"
fi