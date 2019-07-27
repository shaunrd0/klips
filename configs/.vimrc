
" Set tabwidth=2, adjust Vim shiftwidth to the same
set tabstop=2 shiftwidth=2 

" expandtab inserts spaces instead of tabs
set expandtab 

" autindent inserts the next line at your current depth
set autoindent 

" mouse=a allows for mouse interaction with vim when supported
set mouse=a

" Enable Syntax Highlighting in Vim
syntax on

" Enable Pathogen plugin manager
execute pathogen#infect()
filetype plugin indent on

" Enable clang_complete plugin for vim
" https://github.com/xavierd/clang_complete
" Requires clang to be installed
" Path to library may change
let g:clang_library_path='/usr/lib64/libclang.so.8'

