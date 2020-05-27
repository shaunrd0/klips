" Single-quote is a comment written to be read
" Double-quotes are commented out code and can be removed or added

" General Vim Settings

" Define function in vim to remove whitespace
fun! TrimWhitespace()
  let l:save = winsaveview()
  keeppatterns %s/\s\+$//e
  call winrestview(l:save)
endfun
"Call this on every attempt to save a file of types defined below..
autocmd BufWritePre *.cpp,*.h,*.c,*.php :call TrimWhitespace()
""autocmd BufWritePre *.cpp,*.h,*.c,*.php :%s/\s\+$//ge
" Set terminal title when opening file
"" autocmd BufEnter * let &titlestring = ' ' . expand("%:t")
"" set title

" Set tabwidth=2, adjust Vim shiftwidth to the same
set tabstop=2 shiftwidth=2

" expandtab inserts spaces instead of tabs
set expandtab

" autindent inserts the next line at your current depth
set autoindent

" mouse=a allows for mouse interaction with vim when supported
set mouse=a

set number

" Use Powerline symbols
""let g:airline_powerline_fonts = 1

" Enable Syntax Highlighting in Vim
syntax on
" Use Sourcerer color scheme by Xero
colorscheme sourcerer

" Fix plugin compatibility issues
set nocp
" Allow backspace to remove all types of characters
set backspace=indent,eol,start

" Custom Vim Keybindings

" nnoremap <C-e> <C-w> " Modify and remove leading quotation

" CPP Compile
""autocmd FileType cpp nmap <buffer> <F5> :w<bar>!g++ -o %:r % && ./%:r<CR>

" Set window jump to custom binding
" default Ctrl-W conflict - closes browser tabs
nnoremap <C-e> <C-w>

nnoremap <C-b> :!make -C build/

" Vim Plugin Settings

" set rtp+=/path/to/rtp/that/included/pathogen/vim " if needed
" Enable Pathogen plugin manager
execute pathogen#infect()
filetype plugin indent on

" Set Vim Airline theme
" base16 soda base16_pop laederon  night_owl kalisi* ayu_mirage* raven
let g:airline_theme='kalisi'

" Gitgutter installed for + -  diffs in gutters within repo files

" Ale linter settings
" Hover detail info in preview window
let g:ale_hover_to_preview = 1
" Hover detail info in balloons
""let g:ale_set_balloons = 1
let g:ale_sign_error = ''
let g:ale_sign_warning = ''
highlight ALEWarningSign ctermbg=Yellow
highlight ALEWarningSign ctermfg=Black
highlight ALEWarning ctermbg=DarkYellow
highlight ALEWarning ctermfg=White
highlight ALEErrorSign ctermbg=DarkRed
highlight ALEErrorSign ctermfg=White
highlight ALEError ctermfg=DarkRed
nmap <silent> <C-k> <Plug>(ale_previous_wrap)
nmap <silent> <C-j> <Plug>(ale_next_wrap)

" Syntastic syntax checker settings
"  See :help syntastic
""set statusline+=%#warningmsg#
""set statusline+=%{SyntasticStatuslineFlag()}
""set statusline+=%*
""let g:syntastic_always_populate_loc_list = 1
""let g:syntastic_auto_loc_list = 1
""let g:syntastic_check_on_open = 1
""let g:syntastic_check_on_wq = 0

" Clang_complete settings
let g:clang_library_path='/usr/lib/llvm-8/lib/'

" Understand how the plugin works: :h signify-modus-operandi
" Spare the plugin some work and read: :h g:signify_vcs_list
" Signify plugin settings
" Diff gutter within Vim
"" let g:signify_vcs_list = ['git', 'hg']
"" let g:signify_cursorhold_insert     = 1
"" let g:signify_cursorhold_normal     = 1
"" let g:signify_update_on_bufenter    = 0
"" let g:signify_update_on_focusgained = 1
"
" Colorizer plugin settings
" See :h colorizer in Vim for more info
""let g:colorizer_colornames = 0 " Don't color literal names, like red, green, etc
let g:colorizer_auto_color = 1
""let g:colorizer_skip_comments = 1
""let g:colorizer_auto_filetype ='css,html,vim'
nnoremap <C-c> :ColorToggle<CR>

" Symbols important to vim / terminal layouts

set termencoding=utf-8
set encoding=utf-8

" air-line
let g:airline_powerline_fonts = 1

if !exists('g:airline_symbols')
  let g:airline_symbols = {}
endif

" unicode symbols
let g:airline_left_sep = '»'
let g:airline_left_sep = '▶'
let g:airline_right_sep = '«'
let g:airline_right_sep = '◀'
let g:airline_symbols.linenr = '␊'
let g:airline_symbols.linenr = '␤'
let g:airline_symbols.linenr = '¶'
let g:airline_symbols.branch = '⎇'
let g:airline_symbols.paste = 'ρ'
let g:airline_symbols.paste = 'Þ'
let g:airline_symbols.paste = '∥'
let g:airline_symbols.whitespace = 'Ξ'

" airline symbols
let g:airline_left_sep = ''
let g:airline_left_alt_sep = ''
let g:airline_right_sep = ''
let g:airline_right_alt_sep = ''
let g:airline_symbols.branch = ''
let g:airline_symbols.readonly = ''
let g:airline_symbols.linenr = ''

