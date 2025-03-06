# encoding: utf-8
# sdl3.py -- sdl3 waf plugin
# Copyright (C) 2018 a1batross
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

import os

def options(opt):
	grp = opt.add_option_group('SDL3 options')
	grp.add_option('-s', '--sdl3', action='store', dest = 'SDL3_PATH', default = None,
		help = 'path to precompiled SDL3 library(required for Windows)')

	grp.add_option('--skip-sdl3-sanity-check', action='store_false', default = True, dest='SDL3_SANITY_CHECK',
		help = 'skip checking SDL3 sanity')

def my_dirname(path):
	# really dumb, will not work with /path/framework//, but still enough
	if path[-1] == '/':
		path = path[:-1]
	return os.path.dirname(path)

def sdl3_configure_path(conf, path):
	conf.env.HAVE_SDL3 = 1
	if conf.env.DEST_OS == 'darwin':
		conf.env.INCLUDES_SDL3 = [
			os.path.abspath(os.path.join(path, 'Headers'))
		]
		conf.env.FRAMEWORKPATH_SDL3 = [my_dirname(path)]
		conf.env.FRAMEWORK_SDL3 = ['SDL3']
	else:
		conf.env.INCLUDES_SDL3 = [
			os.path.abspath(os.path.join(path, 'include')),
			os.path.abspath(os.path.join(path, 'include/SDL3'))
		]
		libpath = 'lib'
		if conf.env.COMPILER_CC == 'msvc':
			if conf.env.DEST_CPU in ['x86_64', 'amd64']:
				libpath = 'lib/x64'
			else:
				libpath = 'lib/' + conf.env.DEST_CPU
		conf.env.LIBPATH_SDL3 = [os.path.abspath(os.path.join(path, libpath))]
		conf.env.LIB_SDL3 = ['SDL3']

def configure(conf):
	if conf.options.SDL3_PATH:
		conf.start_msg('Configuring SDL3 by provided path')
		sdl3_configure_path(conf, conf.options.SDL3_PATH)
		conf.end_msg('yes: {0}, {1}, {2}'.format(conf.env.LIB_SDL3, conf.env.LIBPATH_SDL3, conf.env.INCLUDES_SDL3))
	else:
		try:
			conf.check_cfg(
				path='sdl3-config',
				args='--cflags --libs',
				package='',
				msg='Checking for library SDL3',
				uselib_store='SDL3')
		except conf.errors.ConfigurationError:
			conf.env.HAVE_SDL3 = 0
	
	if not conf.env.HAVE_SDL3 and conf.env.CONAN:
		if not conf.env.SDL3_VERSION:
			version = '2.0.10' # TODO SDL3: Replace to a new number!
		else:
			version = conf.env.SDL3_VERSION
		
		conf.load('conan')
		conf.add_conan_remote('bincrafters', 'https://api.bintray.com/conan/bincrafters/public-conan')
		conf.add_dependency('sdl3/%s@bincrafters/stable' % version, options = { 'shared': 'True' } )

	if conf.env.HAVE_SDL3 and conf.options.SDL3_SANITY_CHECK:
		try:
			conf.check_cc(
				fragment='''
				#define SDL_MAIN_HANDLED
				#include <SDL.h>
				int main( void )
				{
					SDL_Init( SDL_INIT_EVERYTHING );
					return 0;
				}''',
				msg	= 'Checking for library SDL3 sanity',
				use = 'SDL3',
				execute = False)
		except conf.errors.ConfigurationError:
			conf.env.HAVE_SDL3 = 0
