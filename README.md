42 school project

Project to imitate in C the use of pipe in shell commands.

Format:  
`./pipex infile cmd1 cmd2 outfile`

Example:  
`< infile grep Hello | wc -l > outfile` == `./pipex infile "grep Hello" "wc -l" outfile`.
