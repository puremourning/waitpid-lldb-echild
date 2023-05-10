# Instructions:

1. On macOS, build the bin: `make`
2. in one terminal: `./a.out`
3. note the child pid
3. in another terminal: `lldb -p <pid>`

# Expected

Parent process still running, continues printing ...

# Actual

```
waitpid error: No child processes 
```
