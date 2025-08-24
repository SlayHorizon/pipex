> [!NOTE]  
> This repo is only public so I can easily share it with schoolmates and access it from anywhere, just for my own use.

## Pipex

Exercice project to learn C.  
The exercice is to imitate in C the use of pipe as the next shell command:  
`< file1 cmd1 | cmd2 > file2`

**Program arguments format:**  
`./pipex infile cmd1 cmd2 outfile`

**Example:**  
`< infile grep Hello | wc -l > outfile` == `./pipex infile "grep Hello" "wc -l" outfile`.
