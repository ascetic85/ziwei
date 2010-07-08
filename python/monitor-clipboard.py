#!/usr/bin/python -tt
#-*- coding:utf-8 -*-
__DOC__="""
monitor your clipboard
"""

import gtk

class MonitorClip(object):

    def __init__(self):
        self.clip = gtk.clipboard_get(gtk.gdk.SELECTION_CLIPBOARD)
        self.clip.connect("owner-change", self._clipboard_changed)


    def _clipboard_changed(self,clipboard, event):
        text = clipboard.wait_for_text()
        print text + '\n'


if __name__ == '__main__':
    s = MonitorClip()
    gtk.main()
