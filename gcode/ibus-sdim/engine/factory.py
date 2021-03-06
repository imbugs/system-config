# -*- coding: utf-8 -*-
# vim:et sw=4 sts=4 sw=4
#
# ibus-sdim - The Tables engine for IBus
#
# Copyright (c) 2008-2009 Yu Yuwei <acevery@gmail.com>
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
#
# $Id: $
#

import ibus
from ibus.exception import *
import table
import os
import dbus
from re import compile as re_compile
import sys
import traceback

path_patt = re_compile(r'[^a-zA-Z0-9_/]')

from gettext import dgettext
_  = lambda a : dgettext ("ibus-sdim", a)
N_ = lambda a : a

engine_base_path = "/com/redhat/IBus/engines/sdim/%s/engine/"


class EngineFactory (ibus.EngineFactoryBase):
    """Sdim IM Engine Factory"""
    def __init__ (self, bus, icon=""):

        # init factory
        self.bus = bus
        super(EngineFactory,self).__init__ (bus)
        self.engine_id=0
    
    def create_engine(self, engine_name):
        # because we need db to be past to Engine
        # the type (engine_name) == dbus.String
        print 'hello world, engine is', engine_name
        name = engine_name.encode ('utf8')
        self.engine_path = engine_base_path % path_patt.sub ('_', name)
        try:
            engine = table.tabengine(self.bus, 
                                     self.engine_path + str(self.engine_id))
            self.engine_id += 1
            #return engine.get_dbus_object()
            return engine
        except:
            print "fail to create engine %s" % engine_name
            import traceback
            traceback.print_exc ()
            raise IBusException("Can not create engine %s" % engine_name)

    def do_destroy (self):
        '''Destructor, which finish some task for IME'''
        super(EngineFactory,self).do_destroy()


