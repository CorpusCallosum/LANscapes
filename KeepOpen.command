#!/bin/sh
if [ $(ps ax | grep -v grep | grep "LANscapesDebug.app" | wc -l) -eq 0 ]
then
       echo "landscapes not running. opening…"
       open /Users/gabriellalevine/Documents/of_v0.8.0_osx_release/apps/EphemeralArchitecture/lanscapesC_kinect/bin/LANscapesDebug.app
else
    echo "LANscapes running"
fi