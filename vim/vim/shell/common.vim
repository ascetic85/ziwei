" Vim global functions for running commands
" Version: 2.1
" Maintainer: WarGrey <juzhenliang@gmail.com>
" Last change: 2009 Jul 10
"*******************************************************************************

if exists("b:load_common") && b:load_common==1
	finish
endif
let b:load_common=1

function g:Trim(str)
	return substitute(a:str,'\(^\s*\)\|\(\s*$\)','','g')
endfunction

function g:FileExists(file)
	return isdirectory(resolve(a:file)) || filereadable(resolve(a:file))
endfunction

" Highlight echo
function g:EchoErrorMsg(msg)
	echohl ErrorMsg
	echo a:msg
	echohl None
endfunction

function g:EchoWarningMsg(msg)
	echohl WarningMsg
	echomsg a:msg
	echohl None
endfunction

function g:EchoMoreMsg(msg)
	echohl MoreMsg
	echomsg a:msg
	echohl None
endfunction
