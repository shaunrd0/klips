" Single-quote is a comment written to be read
" Double-quotes ("") are commented out code and can be removed or added

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

set nocp
" set rtp+=/path/to/rtp/that/included/pathogen/vim " if needed
" Enable Pathogen plugin manager
execute pathogen#infect()
filetype plugin indent on

" Custom Keybindings
" nnoremap <NEW> <OLD>
"" nnoremap <C-e> <C-w>

" Set window jumping to custom binding
" default Ctrl-W conflict - closes browser tabs
nnoremap <C-e> <C-w>

