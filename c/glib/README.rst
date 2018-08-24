=====
learn
=====

| This repository is Write Tutorial Gstreamer in C++.
| from: https://gstreamer.freedesktop.org/documentation/tutorials/basic/index.html
| from: https://gstreamer.freedesktop.org/documentation/plugin-development/introduction/preface.html

.. csv-table::
    :header: Name, Overview

    tutorial 1, Hello world!
    tutorial 2, Gstreamer concepts
    tutorial 3, Dynamic pipeline

kind of element
===============
- source element
- sink element
- filter element
- demuxer element

| `source element` has only *src pad*.
| and `sink element` has only *sink pad*.
| but `filter element` has *src and sink pad*.

demuxer has one sink pad, two source pad.

source方向のPadとは、downstreamにデータを出すPadを指す。
